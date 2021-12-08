#ifndef BINGO_BOARD_HPP
#define BINGO_BOARD_HPP

#include <vector>
#include <string>



// ==============================
// Class describing a bingo board
// ==============================
class BingoBoard {

    public:

        BingoBoard();
        ~BingoBoard();

        void add_row(std::string row);
        void call_number(int num);
        bool is_winner();
        int sum_unmarked();
        void print();

    private:

        std::vector<std::vector<int>> board;
        std::vector<std::vector<bool>> ticked;

};


#endif // BINGO_BOARD_HPP
