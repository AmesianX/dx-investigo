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
#include <map>

//
// Implements a simple config file.
//
class ConfigFile
{
public:
    ConfigFile(const char* fileName);
    ~ConfigFile();

    //
    // Get a value from the config file.
    //
    std::string GetValue(const std::string& key, const std::string& defaultValue) const;
    int GetValue(const std::string& key, int defaultValue) const;
    bool GetValue(const std::string& key, bool defaultValue) const;

private:

    //
    // Read the config file into memory.
    //
    void ReadConfigFile(const char* fileName);

    //
    // Data read from the config file.
    //
    typedef std::map<std::string, std::string> ConfigMap;
    ConfigMap config;
};

