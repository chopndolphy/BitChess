#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece {
    public:
        Pawn(std::vector<int> square, bool isWhiteBool);
    private:
        std::vector<int> location;
        bool isWhite;
};