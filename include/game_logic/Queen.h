#pragma once
#include "game_logic/ChessPiece.h"

class Queen : public ChessPiece {
    public:
        Queen(std::vector<int> square, Color pieceColor, ChessBoard* board);
        bool isLegalMove(std::vector<int> square);
    private:
};