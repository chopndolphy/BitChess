#pragma once
#include <vector>
#include <cstdlib>

#include "forward.h"
#include "alias.h"

#include "Enums.h"
#include "ErrorLogger.h"

class ChessPiece {
    public:
        ChessPiece();

        void move(Location square);
        virtual bool isLegalMove(Location square) = 0;
        virtual char getCharacter() const = 0;

        Color getColor() const {
            return color;
        }

        bool hasDoubleMoved() const {
            return doubleMoved;
        }

        Location getLocation() const;

        void cleanState();

    protected:
        Color color;
        bool movedYet;
        bool lastMoved;
        bool doubleMoved = false;
        ChessBoard* pieceBoard;
};