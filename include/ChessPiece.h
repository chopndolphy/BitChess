#pragma once
#include <vector>
#include <cstdlib>
#include "Enums.h"
#include "ChessBoard.h"

class ChessPiece {
    public:
        void move(std::vector<int> square) {
            pieceBoard->setPieceAt(square, this);
            location = square;
        }
        virtual bool isLegalMove(std::vector<int> square) = 0;
        const Color getColor() const {
            return color;
        }
        const std::vector<int> getLocation() const {
            return location;
        }
    protected:
        std::vector<int> location;
        Color color;
        ChessBoard* pieceBoard;
};