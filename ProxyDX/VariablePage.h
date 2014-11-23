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

#include <map>
#include <string>
#include <list>
#include <vector>

class Variable;
class VariableGroup;

//
// Manages a page of variables.
//
class VariablePage
{
public:

	VariablePage(const std::string& _pageTitle, VariablePage* _parentPage);
	virtual ~VariablePage();

    //
    // Get the unique id of the page.
    //
    int GetId() const { return id; }

    //
	// Get the title of the page.
	//
	const std::string& GetTitle() const { return title; }

    //
    // Get the full name of the page.
    // This is generated from the title (with spaces replaced with underscores),
    // it also includes parent names.
    //
    const std::string GetFullName() const;

	//
    // Get a variable from the page sub-page.
    // Variable is craeted if it doesn't already exist.
	//
	Variable* GetVariable(const std::string& variableName, Investigo::VariableType type, VariableGroup* group);

    //
    // Get a sub-page.
    // Sub-page is craeted if it doesn't already exists.
    //
    VariablePage* GetSubPage(const std::string& pageTitle);

	//
	// Format the list of sub-pages as JSON.
	//
	std::string FormatPagesAsJSON(int indentLevel);

private:

	VariablePage(const VariablePage& other);
	VariablePage& operator=(const VariablePage& other); 

    typedef std::list<Variable*> VariableList;
	typedef std::map<std::string, Variable*> VariableMap;

    //
    // Unique ID of the page.
    //
    int id;

	//
	// The name of the page.
	//
	std::string title;

    //
    // The page that contains this page.
    // Set to NULL for root pages.
    //
    VariablePage* parentPage;

	//
	// Variables in the page.
	//
	VariableList variables;
	VariableMap variablesMap;

    //
    // A list of all pages.
    //
    typedef std::list<VariablePage*> VariablePageList;
    VariablePageList pagesList;

    //
    // A map of all pages of variables.
    //
    typedef std::map<std::string, VariablePage*> VariablePageMap;
    VariablePageMap pagesMap;

};
