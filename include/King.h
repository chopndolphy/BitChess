#pragma once
#include "ChessPiece.h"

class King : public ChessPiece {
    public:
        King(std::vector<int> square, bool isWhiteBool);
    private:
        std::vector<int> location;
        bool isWhite;
};