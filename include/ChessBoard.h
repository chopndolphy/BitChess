#pragma once
#include <vector>
#include "ChessPiece.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Outcome.h"

class ChessBoard {
    public:
        ChessBoard();
        ChessPiece getPieceAt(std::vector<int> square);
        void setPieceAt(std::vector<int> square, ChessPiece piece);
    private:
        void checkGameOver();
        std::vector<ChessPiece> whitePieces;
        std::vector<ChessPiece> blackPieces;
        std::vector<std::vector<ChessPiece*>> boardSpaces; 
};