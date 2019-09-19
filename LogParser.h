#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TagModel.h"

// value1 ... value2 >
class LogParser
{    
    std::ifstream logfile;

    std::vector<TagModel*> tags;
    std::vector<std::vector<std::string>> logtable;

    //+ parser mode linear or chaotic
    //+ mb regex? need strong order yet!!!
    std::string next(const TagModel&);
public:
    LogParser()                             = delete;
    LogParser(const LogParser& )            = delete;
    LogParser& operator= (const LogParser&) = delete;

    LogParser(const std::string);

    template<typename T, typename... Args>
    void addTag(Args&&... args) // add new model
    {
        tags.emplace_back(new T(std::forward<Args>(args)...));
    }

    void reset();                           // clear all included models
    bool process();                         // process log file with included tag-models
    size_t countTags();                     // return count of included models

    operator bool() const;
    void printInternal(std::ostream& out = std::cout);
};
