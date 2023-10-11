#pragma once
#include <vector>
#include <cstdlib>

#include "forward.h"

#include "Enums.h"
#include "ErrorLogger.h"

class ChessPiece {
    public:
        void move(std::vector<int> square);
        virtual bool isLegalMove(std::vector<int> square) = 0;

        const Color getColor() const {
            return color;
        }
        const std::vector<int> getLocation() const {
            return location;
        }
        const bool hasDoubleMoved() const {
            return doubleMoved;
        }

    protected:
        std::vector<int> location;
        Color color;
        bool movedYet;
        bool doubleMoved = false;
        ChessBoard* pieceBoard;
};