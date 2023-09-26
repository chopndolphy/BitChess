#pragma once
#include "ChessPiece.h"

class Knight : public ChessPiece {
    public:
        Knight(std::vector<int> square, bool isWhiteBool);
    private:
        std::vector<int> location;
        bool isWhite;
};