#include "pch.h"
#include "GetWords.h"

std::vector<std::string> getWords(const std::string& line, const char delim) noexcept {
    std::stringstream iss(line);
    std::string word;
    std::vector<std::string> words;
    while (std::getline(iss, word, delim)) {
        words.push_back(word);
    }
    return words;
}