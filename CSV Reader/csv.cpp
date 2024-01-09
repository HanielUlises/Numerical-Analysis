#include "csv.h"

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    std::ifstream file("wine.csv");
    if (!file.is_open()) {
        std::cout << "File could not be opened!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');
        for (const auto &token : tokens) {
            std::cout << token << " ";
        }
        std::cout << std::endl;
    }

    file.close();
    return 0;
}