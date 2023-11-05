#include "game_logic/Bishop.h"
#include <iostream>


Bishop::Bishop(std::vector<int> square, Color pieceColor, ChessBoard* board) {
    location = square;
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
    createView(color, BishopType);
}
bool Bishop::isLegalMove(std::vector<int> square) {
    int pathLength = std::abs(square.at(0) - location.at(0));
    if (square == location) {
        return false; // Moving to same square
    } else if (pathLength != std::abs(square.at(1) - location.at(1))) {
        return false; // Not moving diagonally
    } else if (square.at(0) < 8 || square.at(0) > -1 || square.at(1) < 8 || square.at(1) > -1) {
        // Moving within bounds
        for (int i = 1; i < pathLength; i++) {
            int x, y;
            if (square.at(0) - location.at(0) > 0) {
                x = location.at(0) + i;
            } else {
                x = location.at(0) - i;
            }
            if (square.at(1) - location.at(1) > 0) {
                y = location.at(1) + i;
            } else {
                y = location.at(1) - i;
            }
            if (pieceBoard->getPieceAt({x, y}) != nullptr) {
                return false; // Pieces in the way of path
            }
        }
        if (pieceBoard->getPieceAt(square)->getColor() != color) {
            return true;
        } else {
            return false; // Moving to same colored piece
        }
    } else {
        return false;
    }
}