#pragma once
#include "game_logic/ChessPiece.h"
class Bishop : public ChessPiece {
    public:
        Bishop(Color color, Coord location, ChessBoard* board);
        bool isLegalMove(Coord destination);
    private:
        void createView();
};