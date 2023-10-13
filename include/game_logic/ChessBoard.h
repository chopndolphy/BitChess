#pragma once
#include <vector>
#include <array>
#include <cstdint>

#include "forward.h"
#include "alias.h"

#include "Enums.h"

class ChessBoard {
    public:
        ChessBoard();
        ~ChessBoard();

        ChessPiece* getPieceAt(Location square);

        void setPieceAt(Location endSquare, ChessPiece* piece);

        void removePieceAt(Location square);

        Location getLocation(const ChessPiece* piece) const;

        void setNextMoveEnPassant(bool isEnPassant) {
            nextMoveEnPassant = isEnPassant;
        }

        void setNextMoveCastle(bool isCastle) {
            nextMoveCastle = isCastle;
        }

        void setNextMovePromoting(bool isPromoting) {
            nextMovePromoting = isPromoting;
        }

        void cleanState(Color color);

        GameState checkGameState(Color colorTurn);

        bool canCastle(ChessPiece* piece, Location sqaure);

        bool kingIsProtected(ChessPiece* piece, Location square);

        void printBoard() const;

        // helper functions

        ChessPiece* collisionLine(Location start, Location end, bool endInclusive = true); // return the first piece that collides with the line - includes the last square if endInclusive is enabled - nullptr on error


    private:
        const uint32_t boardWidth = 8;
        const uint32_t boardHeight = 8;
        std::array<ChessPiece*, 64> rawBoard;

        // std::array<std::array<ChessPiece*, 8>, 8> boardSpaces = {};

        bool nextMoveEnPassant;
        bool nextMoveCastle;
        bool nextMovePromoting;
};