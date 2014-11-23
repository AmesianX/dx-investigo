//Copyright (C) 2012 Ashley Davis
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
//documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
//and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
//WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
//HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#include "VariableManager.h"
#include "Variable.h"
#include "VariablePage.h"
#include "VariableGroup.h"
#include "PerformanceLog.h"

#include <assert.h>
#include <boost/foreach.hpp>

using std::string;

const int FRAME_INTERVAL = 1;      // Specifies frames to skip. todo: should move this to config file.

//
// The singleton instance of the variable manager.
//
VariableManager* VariableManager::instance = NULL;

//
// Get the singleton instance of the variable manager.
//
VariableManager* VariableManager::Instance()
{
    assert(instance != NULL);

    return instance;
}

void VariableManager::Init()
{
    assert(instance == NULL);

    instance = new VariableManager();

    // Initialize root page after initalizing singleton.
    // Because the page will register itself with the VariableManager singleton.
    instance->rootPage = new VariablePage("Root", NULL); 
}

void VariableManager::Deinit()
{
    assert(instance != NULL);

    delete instance;
    instance = NULL;
}

VariableManager::VariableManager() :
    rootPage(NULL),
    historyThreadStarted(false),
	stopHistoryThread(false),
    nextVariableId(1),
    nextPageId(1),
    nextGroupId(1),
    lastFrameHistoryUpdated(0),
    historyBufferSize(1000)
{
    historyThread = boost::thread(boost::bind(&VariableManager::HistoryThread, this));
}

VariableManager::~VariableManager()
{
    stopHistoryThread = true;

    if (historyThreadStarted)
    {
        historyThreadWork.notify_one(); // Wake up history thread so we can abort it.
        historyThread.join(); // Wait for history thread to finish.
    }

    VariableMap variablesCopy = variables;

    BOOST_FOREACH(auto variable, variablesCopy)
    {
        delete variable.second;
    }

    variables.clear();

    delete rootPage;
}

//
// Format the list of sub-pages as JSON.
//
std::string VariableManager::FormatPagesAsJSON()
{
	return rootPage->FormatPagesAsJSON(0);
}

//
// Retrieve a variable by its ID.
// Returns NULL when no such variable exists.
//
Variable* VariableManager::FindVariableByID(int variableId) const
{
	VariableMap::const_iterator found = variables.find(variableId);
	if (found != variables.end())
	{
		return found->second;
	}

	return NULL;
}

//
// Register a variable with the manager so that it can be retrieved by id.
// Returns the ID of the variable.
//
int VariableManager::RegisterVariable(Variable* variable)
{
	variables[nextVariableId] = variable;
    return nextVariableId++;
}

//
// Unregister a variable.
//
void VariableManager::UnregisterVariable(Variable* variable)
{
	assert(FindVariableByID(variable->GetId()) != NULL);

	variables.erase(variables.find(variable->GetId()));
}

//
// Retrieve a page by its ID.
// Returns NULL when no such page exists.
//
VariablePage* VariableManager::FindPageByID(int pageId) const
{
    PageMap::const_iterator found = pages.find(pageId);
    if (found != pages.end())
    {
        return found->second;
    }

    return NULL;
}

//
// Register a page with the manager so that it can be retrieved by id.
// Returns the ID of the page.
//
int VariableManager::RegisterPage(VariablePage* page)
{
    pages[nextPageId] = page;
    return nextPageId++;
}

//
// Unregister a page.
//
void VariableManager::UnregisterPage(VariablePage* page)
{
    assert(FindPageByID(page->GetId()) != NULL);

    pages.erase(pages.find(page->GetId()));
}

//
// Retreive a group by name.
// Creates the group if it doesn't already exist.
//
VariableGroup* VariableManager::GetGroup(const std::string& groupName)
{
    GroupNameMap::const_iterator found = groupsByName.find(groupName);
    if (found != groupsByName.end())
    {
        return found->second;
    }

    VariableGroup* group = new VariableGroup(groupName);
    groupsByName[groupName] = group;
    return group;
}

//
// Retrieve a group by its ID.
// Returns NULL when no such group exists.
//
VariableGroup* VariableManager::FindGroupByID(int groupId) const
{
    GroupIdMap::const_iterator found = groupsById.find(groupId);
    if (found != groupsById.end())
    {
        return found->second;
    }

    return NULL;
}

//
// Register a group with the manager so that it can be retrieved by id.
// Returns the ID of the gropu.
//
int VariableManager::RegisterGroup(VariableGroup* group)
{
    groupsById[nextGroupId] = group;
    return nextGroupId++;
}

//
// Unregister a group.
//
void VariableManager::UnregisterGroup(VariableGroup* group)
{
    assert(FindGroupByID(group->GetId()) != NULL);

    groupsById.erase(groupsById.find(group->GetId()));
}

//
// Notify the variable manager that a frame has ended.
//
void VariableManager::NotifyFrameEnd(int curFrameNumber)
{
    if ((curFrameNumber - lastFrameHistoryUpdated) < FRAME_INTERVAL)
    {
        // No need to update history yet.
        return;
    }

    lastFrameHistoryUpdated = curFrameNumber;

    // Notify all variables that frame has ended.
    // This copies the value of each variable to the 'history queue'.
    BOOST_FOREACH(auto variableIt, variables)
    {
        Variable* variable = variableIt.second;
        HistoryQueueEntry entry = 
        {
            variable,
            variable->GetValue()
        };

        historyQueue.push(entry); //todo: is this expensive?  should 'entry' be pool allocated?

        variable->NotifyFrameEnd(curFrameNumber);
    }

	// Notify 'history thread' that work is available.
    // For each variable the history thread moves values from the 'history queue' to the actual history.
	historyThreadWork.notify_one();
}

//
// The thread that runs the output queue.
//
void VariableManager::HistoryThread()
{
    historyThreadStarted = true;

	while (!stopHistoryThread)
	{
		{
			//
			// Get a lock, then traverse all variables and update their history.
			//
			boost::unique_lock<boost::mutex> lock(variableLock);

			//
			// Block until there is work to do.
            // This unlocks 'lock', waits for 'historyThreadWork' to be signalled, then relocks 'lock'.
			//
			historyThreadWork.wait(lock);

            PerformanceLog* performanceLog = PerformanceLog::Instance();
            bool performanceLoggingEnabled = performanceLog->IsEnabled();

            //
            // Read from the history queue, and copy to variable history.
            //
            HistoryQueueEntry entry;
            while (historyQueue.try_pop(entry))
            {
                if (performanceLoggingEnabled)
                {
                    // Copy value to performance log.
                    performanceLog->Update(entry.variable, entry.value);
                }

                // Copy value to variable history.
                entry.variable->AppendHistory(entry.value);
            }

            if (PerformanceLog::Instance()->IsEnabled())
            {
                //
                // Write performance data to the performance log.
                //
                PerformanceLog::Instance()->Update();
            }
		}
	}

    historyThreadStarted = false;
}

//
// Get a variable by its id.
//
Variable* VariableManager::GetVariable(int variableID)
{
	VariableMap::iterator found = variables.find(variableID);
	if (found == variables.end())
	{
		return NULL;
	}

	return found->second;
}
