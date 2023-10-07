#pragma once
#include <vector>
#include <array>
#include "ChessPiece.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Enums.h"

class ChessBoard {
    public:
        ChessBoard();
        ~ChessBoard();
        ChessPiece* getPieceAt(std::vector<int> square) {
            return boardSpaces.at(square.at(1)).at(square.at(0));
        }
        void setPieceAt(std::vector<int> endSquare, ChessPiece* piece);
        void setNextMoveEnPassant(bool isEnPassant) {
            nextMoveEnPassant = isEnPassant;
        }
        void setNextMoveCastle(bool isCastle) {
            nextMoveCastle = isCastle;
        }
        void setNextMovePromoting(bool isPromoting) {
            nextMovePromoting = isPromoting;
        }
        GameState checkGameState(Color colorTurn);
        bool canCastle(ChessPiece* piece, std::vector<int> sqaure);
        bool kingIsProtected(ChessPiece* piece, std::vector<int> square);
    private:
        std::array<std::array<ChessPiece*, 8>, 8> boardSpaces = {};
        bool nextMoveEnPassant;
        bool nextMoveCastle;
        bool nextMovePromoting;
};