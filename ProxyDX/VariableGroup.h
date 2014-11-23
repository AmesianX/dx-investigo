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

#include <string>
#include <vector>

class Variable;

typedef std::vector<int> IntVector;

//
// Defines a group of variables.
// Variables are output to performance log in groups.
//
class VariableGroup
{
public:
    
    VariableGroup(const std::string& _groupTitle);
    ~VariableGroup();

    //
    // Get the unique id of the group.
    //
    int GetId() const { return id; }

    //
    // Get the title of the group.
    //
    const std::string& GetTitle() const { return title; }

    //
    // Get the order of variables in the page.
    //
    const IntVector& GetVariableOrder() const { return variableOrder; }
    
    //
    // Add a variable to the group.
    //
    void AddVariable(Variable* variable);

private:

    //
    // Unique ID of the group.
    //
    int id;

    //
    // The name of the group.
    //
    std::string title;

    //
    // Defines the variable order in a particular page.
    //
    IntVector variableOrder;
};

