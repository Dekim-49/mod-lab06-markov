// Copyright 2024 Chernyadeva Anna

#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_
#pragma once
#include <iostream>
#include <deque>
#include <map>
#include <vector>

class Generate {
 public:
    typedef std::deque<std::string> prefix;
    prefix pprefix;
    std::map<prefix, std::vector<std::string> > statetab;
    
 public:
    Generate();
    void CreateTable(const std::string& text, int countWordInPrefix);
    std::string GenerateText(int maxgen, unsigned int time_generate);
    void trainFromStateTable(
        const std::map<prefix,
        std::vector<std::string>>&);
};
#endif  // INCLUDE_TEXTGEN_H_
