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

#include "PerformanceLog.h"
#include "Variable.h"
#include "VariableValue.h"
#include "VariableGroup.h"
#include "VariableManager.h"
#include "Investigo.h"

#include <stdlib.h>
#include <assert.h>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>

using std::string;
namespace fs = boost::filesystem;

//
// Singleton instance.
//
PerformanceLog* PerformanceLog::instance = NULL;

//
// Singleton instance.
//
PerformanceLog* PerformanceLog::Instance()
{
    assert(instance != NULL);

    return instance;
}

//
// Init the singleton instance.
//
void PerformanceLog::Init()
{
    assert(instance == NULL);

    instance = new PerformanceLog();
}

//
// Deinit the singleton instance.
//
void PerformanceLog::Deinit()
{
    assert(instance != NULL);

    delete instance;
    instance = NULL;
}

PerformanceLog::PerformanceLog() :
    isEnabled(false)
{
}


PerformanceLog::~PerformanceLog()
{
    BOOST_FOREACH(auto frameDataIt, frameDataMap)
    {
        delete frameDataIt.second;
    }
}

//
// Start performance logging.
//
void PerformanceLog::Start()
{
    assert(!isEnabled);

    isEnabled = true;
}

//
// Stop performance logging, flush log to disk.
// This function acquires the 'variable lock' to ensure that the history thread is not 
// updating the output files as they are flushed and closed.
//
void PerformanceLog::Stop()
{
    //
    // Acquire the variable lock.
    //
    boost::unique_lock<boost::mutex> lock(VariableManager::Instance()->GetVariableMutex());

    assert(isEnabled);

    isEnabled = false;


    Flush();
    CloseOutputFiles();
}

//
// Generate the file path for the specified group.
//
static std::string GenerateOutputFilePath(VariableGroup* group) 
{
    const string outputFileName = string("Investigo_") + group->GetTitle() + ".log";
    const fs::path outputFilePath = fs::path(InvestigoSingleton::Instance()->GetOutputDirectory()) / outputFileName;
    return outputFilePath.string();
}

//
// Update the performance log for a particular variable.
// The 'variable lock' (VariableManager::Instance()->GetVariableLock()) must be acquired to call this function.
//
void PerformanceLog::Update(Variable* variable, const VariableValue& value)
{
    assert(isEnabled);

    FrameData* frameData = NULL;
    FrameDataMap::iterator foundFrameData = frameDataMap.find(value.frameNumber);
    if (foundFrameData != frameDataMap.end())
    {
        frameData = foundFrameData->second;
    }
    else
    {
        frameData = new FrameData(); //todo: recycle.
        frameData->frameNumber = value.frameNumber;
        frameDataMap[value.frameNumber] = frameData;
    }

    VariableGroup* group = variable->GetGroup();
    GroupData* groupData = NULL;
    const int groupId = group->GetId();
    GroupDataMap::iterator foundGroupData = frameData->groupDataMap.find(groupId);
    if (foundGroupData != frameData->groupDataMap.end())
    {
        groupData = foundGroupData->second;
    }
    else
    {
        groupData = new GroupData(); //todo: recycle.
        frameData->groupDataMap[groupId] = groupData;
    }

    groupData->variableDataMap[variable->GetId()] = value;
}

//
// Update the performance log generally, flush out old frames of data.
// Any data generated in this or previous frames can be flushed to disk.
// The 'variable lock' (VariableManager::Instance()->GetVariableLock()) must be acquired to call this function.
//
void PerformanceLog::Update()
{
    assert(isEnabled);

    //
    // Debug check.
    //
    int curFrameNumber = InvestigoSingleton::Instance()->GetFrameNumber();

    BOOST_FOREACH(auto frameDataIt, frameDataMap)
    {
        const int frame = frameDataIt.first;
        assert(frame <= curFrameNumber);
    }

    Flush();
}

//
// Flush out all pending performance data.
// The 'variable lock' (VariableManager::Instance()->GetVariableLock()) must be acquired to call this function.
//
void PerformanceLog::Flush()
{
    while (frameDataMap.size() > 0)
    {
        FrameData* frameData = RemoveMinFrame();
        if (frameData != NULL)
        {
            Flush(frameData);

            delete frameData; //todo: recycle.
        }
    }
}

//
// Flush a particular frame.
// The 'variable lock' (VariableManager::Instance()->GetVariableLock()) must be acquired to call this function.
//
void PerformanceLog::Flush(FrameData* frameData)
{
    //
    // Output each group for the frame to the performance log.
    //
    BOOST_FOREACH(auto groupDataIt, frameData->groupDataMap)
    {
        const int groupId = groupDataIt.first;
        GroupData* groupData = groupDataIt.second;

        VariableGroup* group = VariableManager::Instance()->FindGroupByID(groupId);
        assert(group != NULL);

        GroupFileMap::iterator foundGroupFile = groupFileMap.find(groupId);
        FILE* output = NULL;
        if (foundGroupFile == groupFileMap.end())
        {
            //
            // Generate temporary output file.
            // Initially performance data is written to the tmp file, and it is copied
            // to the real file later.  This is so that we can insert the first CSV line,
            // the column names, later when we know what they all are.
            //
            string outputFilePath = GenerateOutputFilePath(group) + ".tmp";
            output = fopen(outputFilePath.c_str(), "wt");
            assert(output != NULL);
            if (!output)
            {
                //todo: log an error via the insestigo 'error manager'.
            }
            groupFileMap[groupId] = output;
        }
        else
        {
            output = foundGroupFile->second;
        }

        fprintf(output, "%d, ", frameData->frameNumber);

        //
        // Output variable values in-order to the group's performance log.
        //
        const IntVector& variableOrder = group->GetVariableOrder();
        BOOST_FOREACH(auto variableId, variableOrder)
        {
            Variable* variable = VariableManager::Instance()->FindVariableByID(variableId);
            assert(variable != NULL);
            
            VariableDataMap::iterator foundVariableData = groupData->variableDataMap.find(variableId);
            if (foundVariableData != groupData->variableDataMap.end())
            {
                const VariableValue& variableValue = foundVariableData->second;
            
                //
                // Output the value to the performance log for the group.
                //
                switch (variable->GetType())
                {
                    case Investigo::VariableType_Int:
                    case Investigo::VariableType_Memory:
                        fprintf(output, "%d, ", variableValue.intValue);
                        break;

                    case Investigo::VariableType_Double:
                    case Investigo::VariableType_Milliseconds:
                        fprintf(output, "%f, ", variableValue.doubleValue);
                        break;

                    default:
                       assert(false);
                }
            }
            else
            {
                // No value for the variable in the current frame.
                fprintf(output, "-, ");
            }
        }

        fprintf(output, "\n");
    }
}

//
// Find and remove the minimum frame number from the frame data.
// The 'variable lock' (VariableManager::Instance()->GetVariableLock()) must be acquired to call this function.
//
PerformanceLog::FrameData* PerformanceLog::RemoveMinFrame()
{
    int minFrame = INT_MAX;

    BOOST_FOREACH(auto frameDataIt, frameDataMap)
    {
        const int frame = frameDataIt.first;
        if (frame < minFrame)
        {
            minFrame = frame;
        }
    }

    if (minFrame == INT_MAX)
    {
        return NULL;
    }

    FrameDataMap::iterator toRemove = frameDataMap.find(minFrame);
    FrameData* frameData = toRemove->second;
    frameDataMap.erase(toRemove);
    return frameData;
}

//
// Insert csv headers and close output files.
// The 'variable lock' (VariableManager::Instance()->GetVariableLock()) must be acquired to call this function.
//
void PerformanceLog::CloseOutputFiles()
{
    BOOST_FOREACH(auto groupFileIt, groupFileMap)
    {
        const int groupId = groupFileIt.first;
        FILE* tmpOutput = groupFileIt.second;

        VariableGroup* group = VariableManager::Instance()->FindGroupByID(groupId);
        assert(group != NULL);

        //
        // Convert the temporary output file into the real output file by inserting 
        // the CSV column names at the start of the file.
        // Inserting column names must be done at the end, because at the start
        // we don't necessarily know what they all will be.
        //

        //
        // Close the temporary file.
        //
        fclose(tmpOutput);

        //
        // Reopen temporary file for reading.
        //
        string realOutputFilePath = GenerateOutputFilePath(group);
        string tmpOutputFilePath = realOutputFilePath + ".tmp";
        tmpOutput = fopen(tmpOutputFilePath.c_str(), "rt");
        assert(tmpOutput); //todo: error checking and reporting.

        //
        // Open real file for writing.
        //
        FILE* realOutput = fopen(realOutputFilePath.c_str(), "wt");
        assert(realOutput); //todo: error checking and reporting.

        //
        // Write CSV column headers to real output file.
        //
        fprintf(realOutput, "Frame No, ");

        const IntVector& variableOrder = group->GetVariableOrder();
        BOOST_FOREACH(auto variableId, variableOrder)
        {
            Variable* variable = VariableManager::Instance()->FindVariableByID(variableId);
            assert(variable != NULL);

            const string& variableName = variable->GetName();
           
            fprintf(realOutput, "%s (%s), ", variableName.c_str(), VariableTypeToString(variable->GetType())); //todo: should use io streams.
        }

        fprintf(realOutput, "\n");

        //
        // Copy tmp file to real file.
        //
        char buf[1024*10];
        for (;;)
        {
            const int bytesRead = fread(buf, 1, sizeof(buf), tmpOutput);
            if (bytesRead == 0)
            {
                break; // All done.
            }

            fwrite(buf, 1, bytesRead, realOutput);
        }

        //
        // Close both files.
        //
        fclose(realOutput);
        fclose(tmpOutput);

        //
        // Delete tmp file.
        //
        fs::remove(tmpOutputFilePath);
    }

    groupFileMap.clear();
}

PerformanceLog::FrameData::~FrameData()
{
    BOOST_FOREACH(auto groupDataIt, groupDataMap)
    {
        delete groupDataIt.second;
    }
}

