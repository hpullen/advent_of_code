#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <string>

namespace funcs {

    std::vector<std::string> read_file(std::string filename);
    std::vector<int> read_file_to_ints(std::string filename);

    std::vector<std::string> split_string(std::string str);
    std::vector<std::string> split_string(
            std::string str, 
            std::string delimiter);

    template<typename T>
    void print_vector(std::vector<T> input, int max=-1) {

        int counter = 0;
        for (auto val : input) {
            std::cout << val << std::endl;
            counter++;
            if (max > 0 && counter >= max) break;
        }
    }

}


#endif // FUNCTIONS_HPP
