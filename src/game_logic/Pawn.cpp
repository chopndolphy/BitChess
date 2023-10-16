#include "Pawn.h"
Pawn::Pawn(std::vector<int> square, Color pieceColor, ChessBoard* board) {
    location = square;
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
    doubleMoved = false;
}
bool Pawn::isLegalMove(std::vector<int> square) {
    int pathLengthX = std::abs(square.at(0) - location.at(0));
    int pathLengthY = std::abs(square.at(1) - location.at(1));
    if (square == location) { 
        return false; // Moveing to same square
    } else if ((square.at(1) - location.at(1) < 1 && color == White) || (square.at(1) - location.at(1) > -1 && color == Black)) {
        return false; // White is moving down or Black is moving up
    } else if (pieceBoard->getPieceAt(square)->getColor() == color) {
        return false; // Moving to own color piece
    } else if (location.at(0) > 7 || location.at(0) < 0 || location.at(1) > 7 || location.at(1) < 0) {
        return false; // Moving out of bounds
    } else if (pathLengthX == 0 && pathLengthY == 1) {
        if ((color == White && square.at(1) == 7) || (color == Black && square.at(1) == 0)) {
            pieceBoard->setNextMovePromoting(true);
        }
        return true; // Moving forward one
    } else if (pathLengthX == 0 && pathLengthY == 2 && !movedYet) {
        doubleMoved = true;
        return true; // Moving forward two on first turn
    } else if (pathLengthX == 1 && pathLengthY == 1 && pieceBoard->getPieceAt(square)->getColor() != color) {
        if ((color == White && square.at(1) == 7) || (color == Black && square.at(1) == 0)) {
            pieceBoard->setNextMovePromoting(true);
        }
        return true; // Capturing normally
    } else if (canEnPassant(square)) {
        return true; // Capturing en passant
    } else {
        return false;
    }
}
bool Pawn::canEnPassant(std::vector<int> square) {
    ChessPiece* enemyPiece = pieceBoard->getPieceAt({square.at(0), square.at(1) - 1});
    if ((location.at(1) != 4 && square.at(1) != 5 && color == White) || (location.at(1) != 3 && square.at(1) != 2 && color == Black)) {
        return false; // Not on proper ranks
    } else if (std::abs(square.at(0) - location.at(0)) != 1)
        return false; // Not moving diagonally one square
    else if (pieceBoard->getPieceAt(square) != nullptr) {
        return false; // Target square is not empty
     } else if (enemyPiece->getColor() == color) {
        return false; // Enemy piece is same color
    } else if (enemyPiece->hasDoubleMoved()) {
        pieceBoard->setNextMoveEnPassant(true);
        return true; // Can en passant
    } else {
        return false;
    }
}