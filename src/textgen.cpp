// Copyright 2024 Chernyadeva Anna
#include <random>
#include <deque>
#include <map>
#include <vector>
#include <time.h>
#include "textgen.h"
Generate::Generate() {
}
void Generate::CreateTable(const std::string& text, int countWordInPrefix) {
    std::string table[600];
    int tableSize = 0;
    std::string word;
    int left = 0;
    int countWord = 0;
    for (int i = 0; i <= text.size(); i++) {
        if (text[i] == ' ' || i == text.size()) {
            std::string word;
            word.append(text, left, i - left);
            table[countWord] = word;
            left = i + 1;
            countWord++;
        }
    }

    for (int i = 0; i < 600; i++) {
        if (table[i] != "") {
            tableSize++;
        }
    }

    for (int i = 0; i < countWordInPrefix; i++) {
        pprefix.push_back(table[i]);
    }

    int y = (tableSize - countWordInPrefix);
    for (unsigned int i = 0; i < y; i++) {
        prefix p;
        for (unsigned int j = 0; j < countWordInPrefix; j++) {
            p.push_back(table[i + j]);
        }
        statetab[p].push_back(table[i + countWordInPrefix]);
    }
}
std::string Generate::GenerateText(int maxgen, unsigned int time_generate) {
    std::string generateText;
    unsigned int seed = time(0);
    if (time_generate != 0) {
        seed = time_generate;
    }
    std::default_random_engine gen(seed);
    for (unsigned int i = 0; i < pprefix.size(); i++) {
        generateText += pprefix[i];
        generateText += ' ';
    }
    for (int i = 0; i < maxgen
         && statetab.find(pprefix) != statetab.end(); i++) {
        std::vector<std::string> suffix = statetab[pprefix];
        if (!suffix.empty()) {
            std::uniform_int_distribution<> dist(0, suffix.size() - 1);
            int randomIndex = dist(gen);
            generateText += suffix[randomIndex] + ' ';
            pprefix.pop_front();
            pprefix.push_back(suffix[randomIndex]);
        } else {
            break;
        }
    }

    return generateText;
}

void Generate::trainFromStateTable(
    const std::map<prefix,
    std::vector<std::string>>&newStateTable) {
    statetab = newStateTable;

    if (!statetab.empty()) {
        auto item = statetab.begin();
        pprefix = item->first;
    }
}

