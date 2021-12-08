#include <sstream>
#include <fstream>
#include <iostream>

#include "functions.hpp"

namespace funcs {

    // =====================================================
    // Read contents of a file into a std::vector of strings
    // =====================================================
    std::vector<std::string> read_file(std::string filename) {

        std::vector<std::string> vals;
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            vals.push_back(line);
        }
        return vals;
    }

    // ==================================================
    // Read contents of a file into a std::vector of ints
    // ==================================================
    std::vector<int> read_file_to_ints(std::string filename) {

        std::vector<int> vals;
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            vals.push_back(std::stoi(line));
        }
        return vals;
    }

    // =================================================
    // Split a string at spaces into a vector of strings
    // =================================================
    std::vector<std::string> split_string(std::string str) {

        std::stringstream ss(str);
        std::vector<std::string> output;
        std::string buffer;
        while (ss >> buffer) {
            output.push_back(buffer);
        }
        return output;
    }


    // ===================================
    // Split a string at a given character
    // ===================================
    std::vector<std::string> split_string(
            std::string str, 
            std::string delimiter) {

        std::vector<std::string> output;
        std::string buffer = "";
        for (auto c : str) {
            if (c == *delimiter.c_str()) {
                output.push_back(buffer);
                buffer = "";
            } else {
                buffer += c;
            }
        }
        return output;
    }

}
