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
#include "ConfigFile.h"

#include <sstream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

using namespace boost::algorithm;

ConfigFile::ConfigFile(const char* fileName)
{
    ReadConfigFile(fileName);
}

ConfigFile::~ConfigFile()
{
}

//
// Get a value from the config file.
//
std::string ConfigFile::GetValue(const std::string& key, const std::string& defaultValue) const
{
    ConfigMap::const_iterator found = config.find(key);
    if (found != config.end())
    {
        return found->second;
    }

    return defaultValue;
}

int ConfigFile::GetValue(const std::string& key, int defaultValue) const
{
    ConfigMap::const_iterator found = config.find(key);
    if (found != config.end())
    {
        return atoi(found->second.c_str());
    }

    return defaultValue;
}

bool ConfigFile::GetValue(const std::string& key, bool defaultValue) const
{
    ConfigMap::const_iterator found = config.find(key);
    if (found != config.end())
    {
        if (stricmp(found->second.c_str(), "true") == 0)
        {
            return true;
        }
        else if (stricmp(found->second.c_str(), "false") == 0)
        {
            return false;
        }
    }

    return defaultValue;
}

//
// Read the config file into memory.
//
// http://stackoverflow.com/questions/6892754/creating-a-simple-configuration-file-and-parser-in-c
//
void ConfigFile::ReadConfigFile(const char* fileName) 
{
    std::ifstream configFile(fileName);

    std::string line;
    while (std::getline(configFile, line))
    {
        std::istringstream lineStream(line);
        std::string key;
        if (std::getline(lineStream, key, '='))
        {
            trim(key);

            std::string value;
            if (std::getline(lineStream, value) ) 
            {
                trim(value);
                config[key] = value;
            }
        }
    }
}
