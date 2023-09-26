#pragma once
#include "ChessPiece.h"

class Bishop : public ChessPiece {
    public:
        Bishop(std::vector<int> square, bool isWhiteBool);
    private:
        std::vector<int> location;
        bool isWhite;
};