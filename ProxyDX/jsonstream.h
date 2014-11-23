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

#include <sstream>
#include <stack>
#include <string>
#include <assert.h>

class jsonstream
{
private:

	class __OpenObject {};
	class __CloseObject {};
	class __OpenArray {};
	class __CloseArray {};

public:
	jsonstream();

	static __OpenObject openObject;
	static __CloseObject closeObject;
	static __OpenArray openArray;
	static __CloseArray closeArray;

	jsonstream& operator<<(const __OpenObject&);
	jsonstream& operator<<(const __CloseObject&);

	jsonstream& operator<<(const __OpenArray&);
	jsonstream& operator<<(const __CloseArray&);

	jsonstream& operator<<(const char* str);
	jsonstream& operator<<(const std::string& str);
	jsonstream& operator<<(int value);
	jsonstream& operator<<(unsigned int value);
	jsonstream& operator<<(unsigned long value);
	jsonstream& operator<<(float value);
    jsonstream& operator<<(double value);
    jsonstream& operator<<(bool value);
	jsonstream& operator<<(GUID const& item);

    void UnquotedValue(const std::string& str);

	std::string str() const 
	{ 
		assert(levelStack.size() == 0);
		assert(curLevel.state == Unknown);
		return output.str(); 
	}
	
private:

	enum State
	{
		Unknown,
		InObject_Name,
		InObject_Value,
		InArray,
	};

	struct Level
	{
		Level() :
			state(Unknown),
			numEntries(0)
		{
		}

		State state;
		int numEntries;
	};

	Level curLevel;
	std::stack<Level> levelStack;
	std::stringstream output;
	int indentLevel;


};

