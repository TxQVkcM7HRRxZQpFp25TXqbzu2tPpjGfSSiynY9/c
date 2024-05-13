#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

std::map<std::string, int> create_word_to_digit_map() {
    return {
        {"one", 1}, {"two", 2}, {"three", 3},
        {"four", 4}, {"five", 5}, {"six", 6},
        {"seven", 7}, {"eight", 8}, {"nine", 9}
    };
}

std::string convert_words_to_digits(const std::string& line, const std::map<std::string, int>& word_to_digit) {
    std::istringstream iss(line);
    std::string token;
    std::string result = "";
    while (iss >> token) {
        if (word_to_digit.find(token) != word_to_digit.end()) {
            result += std::to_string(word_to_digit.at(token));
        }
        else {
            result += token;
        }
    }
    return result;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
    int total = 0;
    auto word_to_digit = create_word_to_digit_map();

    if (!file) {
        std::cerr << "Nie udało się otworzyć pliku." << std::endl;
        return 1;
    }

    while (getline(file, line)) {
        std::string processed_line = convert_words_to_digits(line, word_to_digit);
        int first_digit = -1, last_digit = -1;

        for (char ch : processed_line) {
            if (isdigit(ch)) {
                if (first_digit == -1) first_digit = ch - '0';
                last_digit = ch - '0';
            }
        }

        if (first_digit != -1 && last_digit != -1) {
            total += first_digit * 10 + last_digit;
        }
    }

    file.close();
    std::cout << "Calkowita wartosc energii: " << total << std::endl;
    return 0;
}
