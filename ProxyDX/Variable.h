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
#include "HistoryBuffer.h"

#include <string>
#include <vector>
#include <assert.h>

class VariablePage;
class VariableGroup;

//
// Converts a variable type enum value to a string representation.
//
const char* VariableTypeToString(Investigo::VariableType type);

//
// Base class for a particular variable.
//
class Variable : public Investigo::IVariable
{
public:

	Variable(const std::string& _variableName, Investigo::VariableType _variableType, VariablePage* _page, VariableGroup* _group);
    virtual ~Variable();

	//
	// Get the unique id of the variable.
	//
	int GetId() const { return id; }

	//
	// Get the name of the variable.
	//
	const std::string& GetName() const { return name; }

	//
	// Get the type of the variable.
	//
	Investigo::VariableType GetType() const { return type; }

    //
    // Get the page that contains the variable.
    //
    VariablePage* GetPage() const { return page; }

    //
    // Get the group that contains the variable.
    //
    VariableGroup* GetGroup() const { return group; }

    //
    // Get the current value of the variable.
    //
    const VariableValue& GetValue() const { return curValue; }

	//
	// Set the value of the variable.
	//
	virtual void SetValue(int value)
	{ 
		assert(GetType() == Investigo::VariableType_Int || GetType() == Investigo::VariableType_Memory); 

		curValue.intValue = value; 
	}

    //
    // Increment the value of the variable.
    //
    virtual void Increment()
    { 
        assert(GetType() == Investigo::VariableType_Int); 

        curValue.intValue += 1; 
    }

    //
	// Set the value of the variable.
	//
	virtual void SetValue(double value)
	{ 
		assert(GetType() == Investigo::VariableType_Double || GetType() == Investigo::VariableType_Milliseconds); 

		curValue.doubleValue = value; 
	}

    //
    // Reset the variable.
    //
    virtual void Reset()
    {
        memset(&curValue, 0, sizeof(curValue));
    }

	//
	// Format the variable as a JSON string.
	//
	std::string FormatAsJSON(int indentLevel) const;

	//
	// Format the history of the variable as a JSON string.
	//
	void FormatHistoryAsJSON(jsonstream& output) const;

    //
    // Clear the history.
    //
    void ClearHistory(); 

	//
	// Notify the page that the frame has ended.
	// Called from the main thread.
	//
	void NotifyFrameEnd(int curFrameNumber);

    //
    // Update the history of the variable.
    // Called from the history thread.
    //
    void AppendHistory(const VariableValue &value);

private:

	Variable(const Variable& other);
	Variable& operator=(const Variable& other);

    //
	// Unique id assigned to a variable.
	//
	int id;

	//
	// The  name of the variable.
	//
	std::string name;

	//
	// The type of the variable.
	//
	Investigo::VariableType type;

	//
	// Current value of the variable.
	//
	VariableValue curValue;

    //
    // History of the variable.
    //
    HistoryBuffer history;

    //
    // The page that contains the variable.
    //
    VariablePage* page;

    //
    // The group that contains the variable.
    //
    VariableGroup* group;

};
