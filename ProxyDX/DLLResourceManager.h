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

struct ResourceMapEntry;

//
// This class manages retrieval of named resources from the exe or dll's embedded resources.
//
class DLLResourceManager
{
public:
	DLLResourceManager();
	~DLLResourceManager();

	//
	// Retrieve the data for a named resource.
	// Returns true on success, false if no resource could be found.
	//
	bool GetResourceData(const char* resourceName, const unsigned char** resourceData, int* resourceDataSize, const char** mimeType) const;

private:

	//
	// Finds an entry for the named resource.
	// Returns NULL if the resource doesn't exists.
	//
	const ResourceMapEntry* FindResourceEntry(const char* resourceName) const;
};

