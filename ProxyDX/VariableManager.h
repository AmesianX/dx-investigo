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
#pragma once

#include "VariableValue.h"

#include <string>
#include <boost/thread.hpp>
#include <concurrent_queue.h>

class VariableFrame;
class VariablePage;
class Variable;
class VariableGroup;

//
// Manages pages of variables.
//
class VariableManager
{
public:

    //
    // Get the singleton instance of the variable manager.
    //
    static VariableManager* Instance();

    //
    // Allocate and init singleton variable manager.
    //
    static void Init();

    //
    // Deinit and deallocate singleton variable manager.
    //
    static void Deinit();

    //
    // Get the root variable page.
    //
    VariablePage* GetRootPage() const { return rootPage; }

	//
	// Format the list of sub-pages as JSON.
	//
	std::string FormatPagesAsJSON();

	//
	// Retrieve a variable by its ID.
	// Returns NULL when no such variable exists.
	//
	Variable* FindVariableByID(int variableId) const;

	//
	// Register a variable with the manager so that it can be retrieved by id.
    // Returns the ID of the variable.
	//
	int RegisterVariable(Variable* variable);

    //
	// Unregister a variable.
	//
	void UnregisterVariable(Variable* variable);

    //
    // Retrieve a page by its ID.
    // Returns NULL when no such page exists.
    //
    VariablePage* FindPageByID(int pageId) const;

    //
    // Register a page with the manager so that it can be retrieved by id.
    // Returns the ID of the page.
    //
    int RegisterPage(VariablePage* page);

    //
    // Unregister a page.
    //
    void UnregisterPage(VariablePage* page);

    //
    // Retreive a group by name.
    // Creates the group if it doesn't already exist.
    //
    VariableGroup* GetGroup(const std::string& groupName);

    //
    // Retrieve a group by its ID.
    // Returns NULL when no such group exists.
    //
    VariableGroup* FindGroupByID(int groupId) const;

    //
    // Register a group with the manager so that it can be retrieved by id.
    // Returns the ID of the gropu.
    //
    int RegisterGroup(VariableGroup* group);

    //
    // Unregister a group.
    //
    void UnregisterGroup(VariableGroup* group);

    //
	// Notify the variable manager that a frame has ended.
	//
	void NotifyFrameEnd(int curFrameNumber);

	//
	// Get the mutex used to lock access to pages and variables.
	//
	boost::mutex& GetVariableMutex() { return variableLock; }

	//
	// Get a variable by its id.
	//
	Variable* GetVariable(int variableID);

    //
    // Get the size of the history buffer.
    //
    int GetHistoryBufferSize() const { return historyBufferSize; }

    //
    // Set the size of this history buffer, this must be called before
    // variables are created to have any effect.
    //
    void SetHistoryBufferSize(int _historyBufferSize) { historyBufferSize = _historyBufferSize; }

private:

    // Private constructor/destructor.
    // VariableManager is a singleton.
    VariableManager();
    ~VariableManager();
    
    typedef std::map<int, Variable*> VariableMap;
    typedef std::map<std::string, VariableGroup*> GroupNameMap;
    typedef std::map<int, VariableGroup*> GroupIdMap;
    typedef std::map<int, VariablePage*> PageMap;

    //
    // The singleton instance of the variable manager.
    //
    static VariableManager* instance;

	//
	// The thread that runs the output queue.
	//
	void HistoryThread();

    //
    // The root variable page.
    //
    VariablePage* rootPage;

	//
	// A map of all variables by ID.
	//
	VariableMap variables;

    //
    // A map of all pages by ID.
    //
    PageMap pages;

    //
    // A map of all groups by name.
    //
    GroupNameMap groupsByName;

    //
    // A map of all groups by ID.
    //
    GroupIdMap groupsById;

	//
	// References all the values that are being updated this frame.
	//
	VariableFrame* curVariableFrame;

    struct HistoryQueueEntry
    {
        Variable* variable;
        VariableValue value;
    };

    //
    // Queue of variable values to be placed in the history buffer.
    // Items are enqueued in the main thread, and dequeue by the history thread.
    //
    Concurrency::concurrent_queue<HistoryQueueEntry> historyQueue;

	//
	// Runs the history thread.
	//
	boost::thread historyThread;

    //
    // Set to true when the history thread has already started.
    //
    bool historyThreadStarted;

	//
	// Set to true to stop the history thread.
	//
	bool stopHistoryThread;

	//
	// Used to wake up the history thread when there is work to be done.
	//
	boost::condition_variable historyThreadWork;

	//
	// Mutex used to lock access to pages and variables.
	//
	boost::mutex variableLock;

    //
    // ID for the next variable registered.
    //
    int nextVariableId;

    //
    // ID for the next page registered.
    //
    int nextPageId;

    //
    // ID for the next group registered.
    //
    int nextGroupId;

    //
    // Records the last frame when history was updated.
    //
    int lastFrameHistoryUpdated;

    //
    // The size of the history buffer.
    //
    int historyBufferSize;
};
