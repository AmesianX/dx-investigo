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
#include "Investigo.h"
#include "HistoryBuffer.h"
#include "jsonstream.h"

using std::stringstream;

HistoryBuffer::HistoryBuffer(Investigo::VariableType _type) :
    curOffset(0),
    type(_type)
{
    values.reserve(VariableManager::Instance()->GetHistoryBufferSize());
}


HistoryBuffer::~HistoryBuffer()
{
}

//
// Format the history of the variable as a JSON string.
//
void HistoryBuffer::FormatAsJSON(jsonstream& output) const
{
    output << jsonstream::openObject
        << "start_frame" << (values.size() > 0 ? values[curOffset].frameNumber : 1) 
        << "history" << jsonstream::openArray;

    if ((int)values.size() > curOffset)
    {
        FormatRangeAsJSON(curOffset, values.size(), output);

        if (curOffset > 0)
        {
            FormatRangeAsJSON(0, curOffset, output);
        }
    }

    output  << jsonstream::closeArray
            << jsonstream::closeObject;
}

//
// Clear the history.
//
void HistoryBuffer::Clear()
{
    curOffset = 0;
    values.clear();
}

//
// Format a range of the history as JSON.
//
void HistoryBuffer::FormatRangeAsJSON(int start, int last, jsonstream& output) const
{
    for (int i = start; i < last; ++i)
    {
        const VariableValue& value = values[i];

        output  << jsonstream::openArray
                <<  value.frameNumber;

        if (type == Investigo::VariableType_Int || type == Investigo::VariableType_Memory)
        {
            output << value.intValue;
        }
        else if (type == Investigo::VariableType_Double || type == Investigo::VariableType_Milliseconds)
        {
            output << value.doubleValue;
        }
        else
        {
            assert(false);
        }

        output << jsonstream::closeArray;
    }
}

//
// Add to the history.
//
void HistoryBuffer::Append(const VariableValue &value)
{
    if ((int)values.size() < VariableManager::Instance()->GetHistoryBufferSize())
    {
        values.push_back(value);
    }
    else
    {
        values[curOffset] = value;
        ++curOffset;
        if (curOffset >= (int)values.size())
        {
            curOffset = 0;
        }
    }
}
