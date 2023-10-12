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

        Color getColor() const {
            return color;
        }

        bool hasDoubleMoved() const {
            return doubleMoved;
        }

        Location getLocation() const;
    protected:
        Color color;
        bool movedYet;
        bool doubleMoved = false;
        ChessBoard* pieceBoard;
};