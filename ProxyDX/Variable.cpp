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
#include "Variable.h"
#include "VariableGroup.h"
#include "VariableManager.h"
#include "PerformanceLog.h"

#include <boost/format.hpp>
#include <sstream>

using std::stringstream;
using std::string;

//
// Converts a variable type enum value to a string representation.
//
const char* VariableTypeToString(Investigo::VariableType type)
{
    switch (type)
    {
        case Investigo::VariableType_Int:             return "int";
        case Investigo::VariableType_Double:          return "double";
        case Investigo::VariableType_Memory:           return "memory";
        case Investigo::VariableType_Milliseconds:     return "milliseconds";

        default:                                        
            assert(false);
    }

    return "unknown";
}

Variable::Variable(const std::string& _variableName, Investigo::VariableType _variableType, VariablePage* _page, VariableGroup* _group) : 
	name(_variableName),
	type(_variableType),
    page(_page),
    group(_group),
    history(_variableType)
{
	memset(&curValue, 0, sizeof(curValue));

	id = VariableManager::Instance()->RegisterVariable(this);
    group->AddVariable(this);
}

Variable::~Variable()
{
	VariableManager::Instance()->UnregisterVariable(this);
}

//
// Format the variable as a JSON string.
// This is designed to be called from the HTTP server thread.
// The page/variable lock should be acquired before calling this.
//
std::string Variable::FormatAsJSON(int indentLevel) const
{
	stringstream output;
	string indent(indentLevel * 4, ' ');
	
	output << indent << "{\n"
		   << indent << "    \"id\": \"" << id << "\",\n"
		   << indent << "    \"name\": \"" << name << "\"\n"
		   << indent << "}";

	return output.str();
}

//
// Format the history of the variable as a JSON string.
//
void Variable::FormatHistoryAsJSON(jsonstream& output) const
{
    history.FormatAsJSON(output);
}

//
// Clear the history.
//
void Variable::ClearHistory()
{
    history.Clear();
}

//
// Notify the page that the frame has ended.
// Called from the main thread.
//
void Variable::NotifyFrameEnd(int curFrameNumber)
{
	curValue.frameNumber = curFrameNumber;

	// Reset each frame.
	curValue.intValue = 0;
	curValue.doubleValue = 0;
}

//
// Update the history of the variable.
// Called from the history thread.
//
void Variable::AppendHistory(const VariableValue &value)
{
    history.Append(value);
}
