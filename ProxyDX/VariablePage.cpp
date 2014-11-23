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
#include "VariablePage.h"
#include "VariablePage.h"
#include "Variable.h"
#include "VariableManager.h"

#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>

using std::stringstream;
using std::string;

VariablePage::VariablePage(const std::string& _pageTitle, VariablePage* _parentPage) :
	title(_pageTitle),
    parentPage(_parentPage)
{
    id = VariableManager::Instance()->RegisterPage(this);
}

VariablePage::~VariablePage()
{
    VariableManager::Instance()->UnregisterPage(this);
}

//
// Get the name of the page.
// This is generated from the title (with spaces replaced with underscores),
// it also includes parent names.
//
const std::string VariablePage::GetFullName() const
{
    if (!parentPage)
    {
        return "";
    }

    string fullName = parentPage->GetFullName();
    if (fullName.size() > 0)
    {
        fullName += "_";
    }

    string name = GetTitle();

    //
    // Replace characters that are invalid for file names.
    //
    boost::replace_all(name, " ", "_");
    boost::replace_all(name, "::", "_");

    fullName += name;
    return fullName;
}

//
// Get a variable from the page sub-page.
// Variable is created if it doesn't already exist.
//
Variable* VariablePage::GetVariable(const std::string& variableName, Investigo::VariableType type, VariableGroup* group)
{
	VariableMap::iterator found = variablesMap.find(variableName);
	if (found != variablesMap.end())
	{
		// Variable already added.
		return found->second;
	}

	Variable* variable = new Variable(variableName, type, this, group);
	variables.push_back(variable);
	variablesMap[variableName] = variable;
	return variable;
}

//
// Get a sub-page.
// Sub-page is craeted if it doesn't already exists.
//
VariablePage* VariablePage::GetSubPage(const std::string& pageTitle)
{
    VariablePageMap::iterator found = pagesMap.find(pageTitle);
    if (found != pagesMap.end())
    {
        return found->second;
    }

    VariablePage* page = new VariablePage(pageTitle, this);
    pagesList.push_back(page);
    pagesMap[pageTitle] = page;
    return page;
}

//
// Format the list of sub-pages as JSON.
//
std::string VariablePage::FormatPagesAsJSON(int indentLevel)
{
	stringstream output;
	string indent(indentLevel * 4, ' ');
	output << indent << "{\n"
			<< indent << "    \"id\": \"" << id << "\",\n"
			<< indent << "    \"name\": \"" << title << "\"";

	output	<< ",\n" 
			<< indent << "    \"pages\": \n";

    output << indent << "[\n";

    bool firstOne = true;

    BOOST_FOREACH(auto page, pagesList)
    {
        if (firstOne)
        {
            firstOne = false;
        }
        else
        {
            output << ",\n";
        }

        output << page->FormatPagesAsJSON(indentLevel+1);
    }		

    output  << "\n"
            << indent << "]\n";

	if (variables.size() > 0)
	{
		output	<< ",\n" 
		        << indent << "    \"variables\": \n"
			    << indent << "    [\n";

		bool firstOne = true;

		BOOST_FOREACH(auto variable, variables)
		{
			if (firstOne)
			{
				firstOne = false;
			}
			else
			{
				output << ",\n";
			}

			output << variable->FormatAsJSON(indentLevel+2);
		}

		output  << "\n"
				<< indent << "    ]";
	}

	output	<< "\n"
			<< indent << "}";

	return output.str();
}
