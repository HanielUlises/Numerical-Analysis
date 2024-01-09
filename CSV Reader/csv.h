// csv.h
#ifndef CSV_H
#define CSV_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::vector<double>> read_csv(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "File could not be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::vector<double>> data;
    std::string line;
    
    // Skip the first line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');
        std::vector<double> row;
        for (const auto &token : tokens) {
            row.push_back(std::stod(token));
        }
        data.push_back(row);
    }

    file.close();
    return data;
}

#endif // CSV_H
