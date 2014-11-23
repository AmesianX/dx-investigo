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
#include <windows.h>
#include "jsonstream.h"
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <iomanip>

using std::string;

jsonstream::__OpenObject jsonstream::openObject;
jsonstream::__CloseObject jsonstream::closeObject;
jsonstream::__OpenArray jsonstream::openArray;
jsonstream::__CloseArray jsonstream::closeArray;

jsonstream::jsonstream() :
	indentLevel(0)
{
}

jsonstream& jsonstream::operator<<(const __OpenObject&)
{
	assert(curLevel.state == Unknown || curLevel.state == InArray || curLevel.state == InObject_Value);

	if (curLevel.state == InArray && curLevel.numEntries > 0)
	{
		output << ",\n" << string(indentLevel*4, ' ');
	}

	++indentLevel;
	levelStack.push(curLevel);

	curLevel.state = InObject_Name;
	curLevel.numEntries = 0;

	output << "{\n" << string(indentLevel*4, ' ');
	return *this;
}

jsonstream& jsonstream::operator<<(const __CloseObject&)
{
	assert(curLevel.state == InObject_Name);
	assert(indentLevel > 0);

	--indentLevel;
	curLevel = levelStack.top();
	levelStack.pop();

	if (curLevel.state == InObject_Value)
	{
		curLevel.state = InObject_Name;
		++curLevel.numEntries;
	}
	else if (curLevel.state == InArray)
	{
		++curLevel.numEntries;
	}

	output << "\n}\n" << string(indentLevel*4, ' ');

	return *this;
}

jsonstream& jsonstream::operator<<(const __OpenArray&)
{
	assert(curLevel.state == Unknown || curLevel.state == InArray || curLevel.state == InObject_Value);

	if (curLevel.state == InArray && curLevel.numEntries > 0)
	{
		output << ",\n" << string(indentLevel*4, ' ');
	}

	++indentLevel;
	levelStack.push(curLevel);

	curLevel.state = InArray;
	curLevel.numEntries = 0;

	output << "[\n" << string(indentLevel*4, ' ');
	return *this;
}

jsonstream& jsonstream::operator<<(const __CloseArray&)
{
	assert(curLevel.state == InArray);
	assert(indentLevel > 0);

	--indentLevel;
	curLevel = levelStack.top();
	levelStack.pop();	

	if (curLevel.state == InObject_Value)
	{
		curLevel.state = InObject_Name;
		++curLevel.numEntries;
	}
	else if (curLevel.state == InArray)
	{
		++curLevel.numEntries;
	}

	output << "\n]\n" << string(indentLevel*4, ' ');
	return *this;
}

jsonstream& jsonstream::operator<<(const char* str)
{
	assert(curLevel.state != Unknown);
	assert(indentLevel > 0);

	string s = str;
	boost::replace_all(s, "\\", "\\\\");

	if (curLevel.state == InArray)
	{
		if (curLevel.numEntries > 0)
		{
			output << ",\n" << string(indentLevel*4, ' ');
		}

		output << "\"" << s << "\"";
		++curLevel.numEntries;
	}
	else if (curLevel.state == InObject_Name)
	{
		if (curLevel.numEntries > 0)
		{
			output << ",\n" << string(indentLevel*4, ' ');
		}

		output << "\"" << s << "\": ";
		curLevel.state = InObject_Value;
	}
	else if (curLevel.state == InObject_Value)
	{
		output << "\"" << s << "\" ";	
		curLevel.state = InObject_Name;
		++curLevel.numEntries;
	}

	return *this;
}

jsonstream& jsonstream::operator<<(const std::string& str)
{
	return operator<<(str.c_str());
}

void jsonstream::UnquotedValue(const std::string& str)
{
    assert(curLevel.state != Unknown);
    assert(indentLevel > 0);

    if (curLevel.state == InArray)
    {
        if (curLevel.numEntries > 0)
        {
            output << ",\n" << string(indentLevel*4, ' ');
        }

        output << str;
        ++curLevel.numEntries;
    }
    else if (curLevel.state == InObject_Name)
    {
        if (curLevel.numEntries > 0)
        {
            output << ",\n" << string(indentLevel*4, ' ');
        }

        output << str;
        curLevel.state = InObject_Value;
    }
    else if (curLevel.state == InObject_Value)
    {
        output << str;
        curLevel.state = InObject_Name;
        ++curLevel.numEntries;
    }

}

jsonstream& jsonstream::operator<<(int value)
{
    UnquotedValue((boost::format("%d") % value).str());
	return *this;
}

jsonstream& jsonstream::operator<<(unsigned int value)
{
    UnquotedValue((boost::format("%d") % value).str());
    return *this;
}

jsonstream& jsonstream::operator<<(unsigned long value)
{
    UnquotedValue((boost::format("%d") % value).str());
    return *this;
}

jsonstream& jsonstream::operator<<(float value)
{
    UnquotedValue((boost::format("%f") % value).str());
    return *this;
}

jsonstream& jsonstream::operator<<(double value)
{
    UnquotedValue((boost::format("%f") % value).str());
    return *this;
}

jsonstream& jsonstream::operator<<(bool value)
{
    UnquotedValue(value ? "true" : "false");
    return *this;
}

// http://codelaboratories.com/forums/viewthread/346/
/// Returns a hex-representation of an integral type variable
template <typename T>
std::string toHex(const T& in, int width=2*sizeof(T))
{
	std::ostringstream strstr;
	strstr << std::hex << std::setfill('0') << std::setw(width) << in;
	return strstr.str();
}

// Composes a string from a GUID structure
inline std::string toString(const GUID& id)
{
	return
		toHex(id.Data1)+"-"+toHex(id.Data2)+"-"+toHex(id.Data3)+"-"
		+toHex((int)id.Data4[0],2)+toHex((int)id.Data4[1],2)+"-"
		+toHex((int)id.Data4[2],2)+toHex((int)id.Data4[3],2)
		+toHex((int)id.Data4[4],2)+toHex((int)id.Data4[5],2)
		+toHex((int)id.Data4[6],2)+toHex((int)id.Data4[7],2)
		;
} 
jsonstream& jsonstream::operator<<(GUID const& item) 
{
	return operator<<(toString(item));
}
