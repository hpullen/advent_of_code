#include <iostream> 

#include "BingoBoard.hpp"
#include "functions.hpp"


// ===========
// Constructor
// ===========
BingoBoard::BingoBoard() {}


// ==========
// Destructor
// ==========
BingoBoard::~BingoBoard() {}


// ====================
// Add row to the board
// ====================
void BingoBoard::add_row(std::string row) {

    std::vector<int> row_ints;
    std::vector<bool> ticked_row;
    for (auto str : funcs::split_string(row)) {
        row_ints.push_back(std::stoi(str));
        ticked_row.push_back(false);
    }
    board.push_back(row_ints);
    ticked.push_back(ticked_row);

}


// ====================================================
// Call a number and tick off any matches on this board
// ====================================================
void BingoBoard::call_number(int num) {

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == num) {
                ticked[i][j] = true;
            }
        }
    }
}


// ==========================================
// Check whether this bingo board is a winner
// ==========================================
bool BingoBoard::is_winner() {

    // Check rows
    for (auto row : ticked) {
        bool filled = true;
        for (auto col : row) {
            if (!col) filled = false;
        }
        if (filled) return true;
    }

    // Check columns
    for (int i = 0; i < ticked[0].size(); i++) {
        bool filled = true;
        for (auto row : ticked) {
            if (!row[i]) filled = false;
        }
        if (filled) return true;
    }

    return false;
}


// ==============================
// Return sum of unticked numbers
// ==============================
int BingoBoard::sum_unticked() {
    
    int sum = 0;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (!ticked[i][j]) sum += board[i][j];
        }
    }
    return sum;
}


// =======================
// Print the current board
// =======================
void BingoBoard::print() {

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (ticked[i][j]) std::cout << "*";
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
