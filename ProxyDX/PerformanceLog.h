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

#include <map>
#include <vector>
#include <string>

class Variable;
struct VariableValue;

//
// Manages logging of performance data to disk.
//
class PerformanceLog
{
public:

    //
    // Singleton instance.
    //
    static PerformanceLog* Instance();

    //
    // Init the singleton instance.
    //
    static void Init();

    //
    // Deinit the singleton instance.
    //
    static void Deinit();

    //
    // Returns true when performance logging is enabled.
    //
    bool IsEnabled() const { return isEnabled; }

    //
    // Start performance logging.
    //
    void Start();

    //
    // Stop performance logging, flush log to disk.
    //
    void Stop();

    //
    // Update the performance log for a particular variable.
    //
    void Update(Variable* variable, const VariableValue& value);

    //
    // Update the performance log generally, flush out old frames of data.
    //
    void Update();

    //
    // Flush out all pending performance data.
    //
    void Flush();

private:

    typedef std::map<int, FILE*> GroupFileMap;
    typedef std::map<int, VariableValue> VariableDataMap;

    //
    // Performance data for a group.
    //
    struct GroupData
    {
        //
        // Maps from variable id to variable data.
        //
        VariableDataMap variableDataMap;
    };

    typedef std::map<int, GroupData*> GroupDataMap;

    //
    // Performance data stored for a frame.
    //
    struct FrameData
    {
        ~FrameData();

        //
        // The number of the frame.
        //
        int frameNumber;

        //
        // Maps from group id to group data.
        //
        GroupDataMap groupDataMap;
    };

    typedef std::map<int, FrameData*> FrameDataMap;

    //
    // Singleton instance.
    //
    static PerformanceLog* instance;

    //
    // Set to true when peformance logging is currently enabled.
    //
    bool isEnabled;

    //
    // Maps frame number to frame data.
    //
    FrameDataMap frameDataMap;

    //
    // Maps group id to output log file.
    //
    GroupFileMap groupFileMap;

    PerformanceLog();
    ~PerformanceLog();

    //
    // Find and remove the minimum frame number from the frame data.
    //
    FrameData* RemoveMinFrame();

    //
    // Flush a particular frame.
    //
    void Flush(FrameData* frameData);


    //
    // Insert csv headers and close output files.
    //
    void CloseOutputFiles();
};

