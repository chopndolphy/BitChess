#pragma once
#include "ChessPiece.h"

class Rook : public ChessPiece {
    public:
        Rook(std::vector<int> square, bool isWhiteBool);
    private:
        std::vector<int> location;
        bool isWhite;
};