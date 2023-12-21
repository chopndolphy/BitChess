#pragma once
#include "game_logic/ChessPiece.h"

class Knight : public ChessPiece {
    public:
        Knight(Color color, Coord location, ChessBoard* board);
        bool isLegalMove(Coord destination);
    private:
        void createView();
};