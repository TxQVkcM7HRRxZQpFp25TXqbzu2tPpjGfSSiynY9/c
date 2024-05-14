#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct DiceSet {
    int red;
    int green;
    int blue;
};

void parse_dice(const std::string& str, DiceSet& set) {
    set.red = 0;
    set.green = 0;
    set.blue = 0;
    std::istringstream iss(str);
    std::string word;
    while (iss >> word) {
        int count = std::stoi(word);
        iss >> word;
        if (word.find("red") != std::string::npos) set.red += count;
        if (word.find("green") != std::string::npos) set.green += count;
        if (word.find("blue") != std::string::npos) set.blue += count;
    }
}

bool is_possible_game(const DiceSet& max_set, const std::vector<DiceSet>& game_sets) {
    for (const auto& set : game_sets) {
        if (set.red > max_set.red || set.green > max_set.green || set.blue > max_set.blue) {
            return false;
        }
    }
    return true;
}

int main() {
    std::ifstream file("input_2.txt");
    if (!file.is_open()) {
        std::cerr << "Could not open file" << std::endl;
        return 1;
    }

    std::string line;
    DiceSet max_set = { 12, 13, 14 };
    int possible_sum = 0;
    long long power_sum = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string game_info, subsets_info;
        if (std::getline(iss, game_info, ':') && std::getline(iss, subsets_info)) {
            int game_id;
            sscanf(game_info.c_str(), "Game %d", &game_id);

            std::istringstream subsets_stream(subsets_info);
            std::vector<DiceSet> game_sets;
            std::string subset;
            while (std::getline(subsets_stream, subset, ';')) {
                DiceSet set;
                parse_dice(subset, set);
                game_sets.push_back(set);
            }

            if (is_possible_game(max_set, game_sets)) {
                possible_sum += game_id;
            }

            int min_red = 0, min_green = 0, min_blue = 0;
            for (const auto& set : game_sets) {
                if (set.red > min_red) min_red = set.red;
                if (set.green > min_green) min_green = set.green;
                if (set.blue > min_blue) min_blue = set.blue;
            }
            power_sum += static_cast<long long>(min_red) * min_green * min_blue;
        }
    }

    file.close();

    std::cout << "Sum of possible game IDs: " << possible_sum << std::endl;
    std::cout << "Sum of powers of minimum sets: " << power_sum << std::endl;

    return 0;
}
