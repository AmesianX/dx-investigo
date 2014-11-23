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
#include "DLLResourceManager.h"
#include "resource.h"

#include <string.h>
#include <windows.h>

extern HINSTANCE hThisInstance;

struct ResourceMapEntry
{
	const char* resourceName;
	int resourceID;
	LPCSTR resourceType;
	const char* mimeType;
};

ResourceMapEntry resourceMap[] =
{
	{
		"/",
		IDR_HTML_UI,
		RT_HTML,
		"text/html",
	},
	{
		"/global.css",
		IDR_GLOBAL_CSS,
		"TEXT",
		"text/css",
	},
	{
		"/global.js",
		IDR_GLOBAL_JS,
		"TEXT",
		"text/javascript",
	},
	{
		"/jquery.tmpl.js",
		IDR_JQUERY_TMPL,
		"TEXT",
		"text/javascript",
	},
	{
		"/app.js",
		IDR_APP_JS,
		"TEXT",
		"text/javascript",
	},
	{
		"/page.js",
		IDR_PAGE_JS,
		"TEXT",
		"text/javascript",
	},
	{
		"/performance_page.js",
		IDR_PERFORMANCE_PAGE_JS,
		"TEXT",
		"text/javascript",
	},
	{
		"/performance_sub_page.js",
		IDR_PERFORMANCE_SUB_PAGE_JS,
		"TEXT",
		"text/javascript",
	},
	{
		"/graph.js",
		IDR_GRAPH_JS,
		"TEXT",
		"text/javascript",
	},
	{
		"/inspector_page.js",
		IDR_INSPECTOR_JS,
		"TEXT",
		"text/javascript",
	},
	{
		"/jquery-mobile-fluid960.css",
		IDR_960_CSS,
		"TEXT",
		"text/css",
	},

	{
		"/jquery-1.7.1.min.js",
		IDR_JQUERY_JS,
		"TEXT",
		"text/javascript",
	},
	{
		"/jquery.mobile-1.1.0.min.js",
		IDR_JQUERY_MOBILE_JS,
		"TEXT",
		"text/javascript",
	},
	{
		"/jquery.mobile-1.1.0.min.css",
		IDR_JQUERY_MOBILE_CSS,
		"TEXT",
		"text/css",
	},
	{
		"/config_page.js",
		IDR_CONFIG_PAGE_JS,
		"TEXT",
		"text/javascript",
	},	
	{
		"/debugger_page.js",
		IDR_DEBUGGER_JS,
		"TEXT",
		"text/javascript",
	},	
	{
		"/data_manager.js",
		IDR_DATA_MANAGER_JS,
		"TEXT",
		"text/javascript",
	},
	{
		"/lodash.js",
		IDR_LODASH_JS,
		"TEXT",
		"text/javascript",
	},
	{
		"/jquery.treeTable.js",
		IDR_JQUERY_TREETABLE_JS,
		"TEXT",
		"text/javascript",
	},
	{
		"/utils.js",
        IDR_UTILS_JS,
		"TEXT",
		"text/javascript",
	},
	{
		"/jquery.treeTable.css",
		IDR_JQUERY_TREETABLE_CSS,
		"TEXT",
		"text/css",
	},
	{
		"/images/ajax-loader.png",
		IDB_PNG1,
		"PNG",
		"image/png",
	},
	{
		"/images/icons-18-black.png",
		IDB_PNG2,
		"PNG",
		"image/png",
	},
	{
		"/images/icons-18-white.png",
		IDB_PNG3,
		"PNG",
		"image/png",
	},
	{
		"/images/icons-36-black.png",
		IDB_PNG4,
		"PNG",
		"image/png",
	},
	{
		"/images/icons-36-white.png",
		IDB_PNG5,
		"PNG",
		"image/png",
	},
	{
		"/toggle-collapse-dark.png",
		IDB_PNG6,
		"PNG",
		"image/png",
	},
	{
		"/toggle-collapse-light.png",
		IDB_PNG7,
		"PNG",
		"image/png",
	},
	{
		"/toggle-expand-dark.png",
		IDB_PNG8,
		"PNG",
		"image/png",
	},
	{
		"/toggle-expand-light.png",
		IDB_PNG9,
		"PNG",
		"image/png",
	},
};

const int RESOURCE_MAP_SIZE = sizeof(resourceMap) / sizeof(resourceMap[0]);

DLLResourceManager::DLLResourceManager()
{
}


DLLResourceManager::~DLLResourceManager()
{
}

//
// Finds an entry for the named resource.
// Returns NULL if the resource doesn't exists.
//
const ResourceMapEntry* DLLResourceManager::FindResourceEntry(const char* resourceName) const
{
	for (int resourceMapIndex = 0; resourceMapIndex < RESOURCE_MAP_SIZE; ++resourceMapIndex)
	{
		const ResourceMapEntry& resourceMapEntry = resourceMap[resourceMapIndex];
		if (stricmp(resourceName, resourceMapEntry.resourceName) == 0)
		{
			return &resourceMapEntry;
		}
	}

	return NULL;
}

//
// Retrieve the data for a named resource.
// Returns true on success, false if no resource could be found.
//
bool DLLResourceManager::GetResourceData(const char* resourceName, const unsigned char** resourceData, int* resourceDataSize, const char** mimeType) const
{
	const ResourceMapEntry* resourceMapEntry = FindResourceEntry(resourceName);
	if (resourceMapEntry == NULL)
	{
		return false;
	}

	HRSRC resource = FindResource(hThisInstance, MAKEINTRESOURCE(resourceMapEntry->resourceID), resourceMapEntry->resourceType);
	*resourceDataSize = SizeofResource(hThisInstance, resource);
	HGLOBAL global = LoadResource(hThisInstance, resource);
	*resourceData = (const unsigned char*) :: LockResource(global);
	*mimeType = resourceMapEntry->mimeType;
	return true;
}
