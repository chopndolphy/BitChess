#pragma once
#include <vector>

class ChessPiece {
    public:
        virtual void move(std::vector<int> square);
    private:
        virtual bool checkMove(std::vector<int> square);
};