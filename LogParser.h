#pragma once

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "TagModel.h"
#include "TagDefault.h"

class LogParser
{    
    std::ifstream logfile;

    std::vector<TagModel*> tags;
    std::vector<std::vector<std::string>> logtable;

    std::string next(const TagModel&);

public:
    LogParser()                             = delete;
    LogParser(const LogParser& )            = delete;
    LogParser& operator= (const LogParser&) = delete;
    LogParser(const std::string);

    void reset();                           // clear all included models
    bool run();                             // process log file with included tag-models
    size_t countTags();                     // return count of included models

    operator bool() const;
    void printInternal(std::ostream& out = std::cout);
    const std::vector<TagModel*> & getTags() const;
    const std::vector<std::vector<std::string>> & getTable() const;

    // add new model
    template<typename T = TagDefault, typename... Args>
    void addTag(Args&&... args)
    {
        tags.emplace_back(new T(std::forward<Args>(args)...));
    }
};
