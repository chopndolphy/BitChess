#pragma once
#include <vector>
#include <array>

#include "forward.h"
#include "alias.h"

#include "Enums.h"

class ChessBoard {
    public:
        ChessBoard();
        ~ChessBoard();
        ChessPiece* getPieceAt(Location square) {
            return boardSpaces.at(square.at(1)).at(square.at(0));
        }
        void setPieceAt(Location endSquare, ChessPiece* piece);
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
        bool canCastle(ChessPiece* piece, Location sqaure);
        bool kingIsProtected(ChessPiece* piece, Location square);
        void printBoard() const;
        Location getLocation(const ChessPiece* piece) const;
    private:
        std::array<std::array<ChessPiece*, 8>, 8> boardSpaces = {};
        bool nextMoveEnPassant;
        bool nextMoveCastle;
        bool nextMovePromoting;
};