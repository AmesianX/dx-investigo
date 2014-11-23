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
#ifndef __Timer_h__
#define __Timer_h__

#include <windows.h>

//
// A class for measuring time.
//
class Timer
{
public:

	Timer()
	{
		QueryPerformanceFrequency(&frequency);
	}

    //
    // Start the timer.
    //
	void Start()
	{
		QueryPerformanceCounter(&startTime);
	}

    //
    // Get the time since the timer was started.
    // Returns the time in seconds.
    //
	double GetElapsedTime() const
	{
		LARGE_INTEGER curTime;
		QueryPerformanceCounter(&curTime);
		return (((double) (curTime.QuadPart - startTime.QuadPart)) / frequency.QuadPart);
	}

private:

	LARGE_INTEGER startTime;
	LARGE_INTEGER frequency;
};

#endif // __Timer_h__
