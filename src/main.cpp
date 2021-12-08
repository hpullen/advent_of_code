#include <iostream>
#include <vector>
#include <tuple>

#include "functions.hpp"
#include "BingoBoard.hpp"


// Get list of numbers called and bingo boards
std::tuple<std::vector<int>, std::vector<BingoBoard*>> get_nums_and_boards(
        const std::string& filename
        ) {

    // Read lines from file
    auto lines = funcs::read_file(filename);

    // Read called numbers into vector
    auto num_strs = funcs::split_string(lines[0], ",");

    // Convert to ints
    std::vector<int> nums;
    for (auto str : num_strs) {
        nums.push_back(std::stoi(str));
    }

    // Create bingo boards
    std::vector<BingoBoard *> boards;
    BingoBoard *current_board;
    for (int i=1; i < lines.size(); i++) {

        // If line is blank, make new board
        if (!lines[i].length()) {
            current_board = new BingoBoard();
            boards.push_back(current_board);
        }

        // Otherwise, add row to current board
        else {
            current_board->add_row(lines[i]);
        }
    }

    return {nums, boards};
}


// Part one: find first board to win and return sum of its unticked numbers
int part_one(
        const std::vector<int>& nums, 
        const std::vector<BingoBoard*>& boards
        ) {

    // Call all numbers until a winner is found
    for (auto const& num : nums) {
        for (auto const& b : boards) {
            b->call_number(num);
            if (b->is_winner()) {
                return b->sum_unticked() * num;
            }
        }
    }

    return -1;
}


// Part two: find last board to win and return sum of its unticked numbers
int part_two(
        const std::vector<int>& nums, 
        std::vector<BingoBoard*> boards
        ) {

    for (auto const& num : nums) {
        
        // Call number for all boards
        for (auto const& b : boards) {
            b->call_number(num);
        }

        // Check whether only one board remains and has won
        if (boards.size() == 1 && boards[0]->is_winner()) {
            return boards[0]->sum_unticked() * num;
        }

        // Reduce boards list to only those that haven't yet won
        std::vector<BingoBoard*> remaining;
        for (auto const& b : boards) {
            if (!b->is_winner()) {
                remaining.push_back(b);
            }
        }
        boards = remaining;
    }

    return -1;
}


int main(int argc, char* argv[]) {

    // Get filename
    if (argc < 2) {
        std::cout << "Usage: ./Solution <filename>" << std::endl;
        return -1;
    }
    std::string filename = argv[1];

    // Load bingo numbers and bingo boards
    auto [nums, boards] = get_nums_and_boards(filename);

    // Complete challenges
    std::cout << "Part 1: " << part_one(nums, boards) << std::endl;
    std::cout << "Part 2: " << part_two(nums, boards) << std::endl;
    
    // Delete BingoBoard objects
    for (auto b : boards) {
        delete b;
    }

    return 0;
}
