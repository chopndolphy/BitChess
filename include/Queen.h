#pragma once
#include "ChessPiece.h"

class Queen : public ChessPiece {
    public:
        Queen(std::vector<int> square, bool isWhiteBool);
    private:
        std::vector<int> location;
        bool isWhite;
};