#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <unordered_map>

int word_to_digit(const std::string& word) {
    static const std::unordered_map<std::string, int> word_to_digit_map = {
        {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
        {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
    };
    auto it = word_to_digit_map.find(word);
    return (it != word_to_digit_map.end()) ? it->second : -1;
}

void extract_digits(const std::string& line, int& first_digit, int& last_digit) {
    first_digit = -1;
    last_digit = -1;
    std::string word;

    for (size_t i = 0; i < line.length(); ++i) {
        if (isdigit(line[i])) {
            int digit = line[i] - '0';
            if (first_digit == -1) first_digit = digit;
            last_digit = digit;
        }
        else if (isalpha(line[i])) {
            word += line[i];
            if (word.length() >= 3) {
                int digit = word_to_digit(word);
                if (digit != -1) {
                    if (first_digit == -1) first_digit = digit;
                    last_digit = digit;
                    word.clear();
                }
            }
        }
        else {
            word.clear();
        }
    }
}

int main() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "Could not open file\n";
        return 1;
    }

    std::string line;
    int total_sum = 0;

    while (std::getline(file, line)) {
        int first_digit, last_digit;
        extract_digits(line, first_digit, last_digit);
        if (first_digit != -1 && last_digit != -1) {
            int number = first_digit * 10 + last_digit;
            total_sum += number;
        }
    }

    file.close();

    std::cout << "Total sum: " << total_sum << std::endl;

    return 0;
}
