// Copyright 2024 Chernyadeva Anna
#include <iostream>
#include <fstream>
#include <sstream>
#include "textgen.h"

int main() {
    const int NREF = 2;
    const int MAXGEN = 1000;
    std::string text;
    std::string textFile;
    std::ifstream file("text.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            textFile += line + " ";
        }
        textFile.pop_back();
        file.close();
    }
    Generate gen;
    gen.CreateTable(textFile, NREF);
    text = gen.GenerateText(MAXGEN, 10);
    std::cout << text;
}
