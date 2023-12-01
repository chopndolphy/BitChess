#include "game_logic/Bishop.h"
#include <iostream>


Bishop::Bishop(Color color, Coord location, ChessBoard* board) {
    this->location = location;
    this->color = color;
    this->board = board;
    movedYet = false;
    createView(color, PieceType::BishopType);
}
bool Bishop::isLegalMove(Coord destination) const {
    int pathLength = std::abs(destination.x() - location.x());
    if (destination.x() == location.x() && destination.y() == location.y()) {
        return false; // Moving to same square
    } else if (pathLength != std::abs(destination.y() - location.y())) {
        return false; // Not moving diagonally
    } else if (destination.x() < 8 || destination.x() > -1 || destination.y() < 8 || destination.y() > -1) {
        // Moving within bounds
        for (int i = 1; i < pathLength; i++) {
            int x, y;
            if (destination.x() - location.x() > 0) {
                x = location.x() + i;
            } else {
                x = location.x() - i;
            }
            if (destination.y() - location.y() > 0) {
                y = location.y() + i;
            } else {
                y = location.y() - i;
            }
            if (board->getPieceAt(Coord(x, y)) != nullptr) {
                return false; // Pieces in the way of path
            }
        }
        if (board->getPieceAt(destination)->getColor() != color) {
            return true;
        } else {
            return false; // Moving to same colored piece
        }
    } else {
        return false;
    }
}