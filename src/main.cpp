#include <iostream>
#include <memory>
#include <map>
#include <tuple>
#include <vector>

#include "functions.hpp"
#include "BingoBoard.hpp"


typedef std::vector<int> NumList;
typedef std::vector<std::unique_ptr<BingoBoard>> BoardList;


// Get bingo numbers and bingo boards
std::tuple<NumList, BoardList> get_nums_and_boards(const std::string& filename) 
{

    // Read lines from input file
    auto lines = funcs::read_file(filename);

    // Read numbers into vector of strings
    auto num_strs = funcs::split_string(lines[0], ",");

    // Convert to ints
    NumList nums;
    for (auto str : num_strs) {
        nums.push_back(std::stoi(str));
    }

    // Create bingo boards
    BoardList boards;
    int id = -1;
    for (int i = 1; i < lines.size(); i++) {

        // If line is blank, make new board
        if (!lines[i].length()) {
            id++;
            auto new_board = std::make_unique<BingoBoard>();
            boards.push_back(std::move(new_board));
        }

        // Otherwise, add row to current board
        else {
            boards[id]->add_row(lines[i]);
        }
    }

    return {nums, std::move(boards)};
}


// Part one: find first board to win
int part_one(const NumList& nums, const BoardList& boards) {

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


// Part two: find last board to win
int part_two(const NumList& nums, const BoardList& boards) {

    // Make list of positions of remaining boards; initially all boards
    std::vector<int> board_ids;
    for (int i = 0; i < boards.size(); i++) {
        board_ids.push_back(i);
    }

    // Loop through bingo numbers
    for (auto const& num : nums) {

        // Call number for remaining boards
        std::vector<int> remaining;
        for (int id : board_ids) {

            boards[id]->call_number(num);

            // Store IDs of boards that still haven't won
            if (!boards[id]->is_winner()) {
                remaining.push_back(id);
            }
        }

        // Check whether only one board remained and has now won
        if (board_ids.size() == 1 && remaining.size() == 0) {
            return boards[board_ids[0]]->sum_unticked() * num;
        }

        // Set board IDs list to only those that haven't yet won
        board_ids = remaining;
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
    
    return 0;
}
