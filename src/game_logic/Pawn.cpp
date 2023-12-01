#include "game_logic/Pawn.h"
#include <iostream>

Pawn::Pawn(Color color, Coord location, ChessBoard* board) {
    this->location = location;
    this->color = color;
    this->board = board;
    movedYet = false;
    doubleMoved = false;
    createView(color, PieceType::PawnType);
}
bool Pawn::isLegalMove(Coord destination) {
    int pathLengthX = std::abs(destination.x() - location.x());
    int pathLengthY = std::abs(destination.y() - location.y());
    if (destination.x() == location.x() && destination.y() == location.y()) { 
        return false; // Moveing to same square
    } else if ((destination.y() - location.y() < 1 && color == Color::White) || (destination.y() - location.y() > -1 && color == Color::Black)) {
        return false; // White is moving down or Black is moving up
    } else if (board->getPieceAt(destination)->getColor() == color) {
        return false; // Moving to own color piece
    } else if (location.x() > 7 || location.x() < 0 || location.y() > 7 || location.y() < 0) {
        return false; // Moving out of bounds
    } else if (pathLengthX == 0 && pathLengthY == 1) {
        if ((color == Color::White && destination.y() == 7) || (color == Color::Black && destination.y() == 0)) {
            board->setNextMovePromoting(true);
        }
        return true; // Moving forward one
    } else if (pathLengthX == 0 && pathLengthY == 2 && !movedYet) {
        doubleMoved = true;
        return true; // Moving forward two on first turn
    } else if (pathLengthX == 1 && pathLengthY == 1 && board->getPieceAt(destination)->getColor() != color) {
        if ((color == Color::White && destination.y() == 7) || (color == Color::Black && destination.y() == 0)) {
            board->setNextMovePromoting(true);
        }
        return true; // Capturing normally
    } else if (canEnPassant(destination)) {
        return true; // Capturing en passant
    } else {
        return false;
    }
}
bool Pawn::canEnPassant(Coord destination) {
    if ((location.y() != 4 && destination.y() != 5 && color == Color::White) || (location.y() != 3 && destination.y() != 2 && color == Color::Black)) {
        return false; // Not on proper ranks
    } else if (std::abs(destination.x() - location.x()) != 1)
        return false; // Not moving diagonally one square
    else if (board->getPieceAt(destination) != nullptr) {
        return false; // Target square is not empty
     } else if (board->getPieceAt({destination.x(), destination.y() - 1})->getColor() == color) {
        return false; // Enemy piece is same color
    } else if (board->getPieceAt({destination.x(), destination.y() - 1})->hasDoubleMoved()) {
        board->setNextMoveEnPassant(true);
        return true; // Can en passant
    } else {
        return false;
    }
}