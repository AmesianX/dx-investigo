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

#include "InvestigoApplicationInterface.h"
#include "VariableValue.h"


#include <sstream>
#include <string>
#include <vector>

class jsonstream;

//
// Contains a circular buffer of a variables history.
//
class HistoryBuffer
{
public:

    HistoryBuffer(Investigo::VariableType _type);
    ~HistoryBuffer();

    //
    // Add to the history.
    //
    void Append(const VariableValue &value);

    //
    // Format the history of the variable as a JSON string.
    //
    void FormatAsJSON(jsonstream& output) const;

    //
    // Clear the history.
    //
    void Clear();

private:

    typedef std::vector<VariableValue> ValueVector;

    //
    // The history of the variable values.
    // This is only modified from the history thread and it can be read
    // from the HTTP server thread.
    //
    ValueVector values;

    //
    // Current offset in the history to insert the next value.
    //
    int curOffset;

    //
    // The type of the variable.
    //
    Investigo::VariableType type;

    //
    // Format a range of the history as JSON.
    //
    void FormatRangeAsJSON(int start, int last, jsonstream& output) const;

};

