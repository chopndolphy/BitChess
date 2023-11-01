#include "game_logic/King.h"

King::King(std::vector<int> square, Color pieceColor, ChessBoard* board) {
    location = square;
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
    createView(color, KingType);
}
bool King::isLegalMove(std::vector<int> square) {
    int pathLengthX = std::abs(square.at(0) - location.at(0));
    int pathLengthY = std::abs(square.at(1) - location.at(1));
    if (square == location) {
        return false; // Moving to same square
    } else if (pieceBoard->canCastle(this, square)) {
        return true; // Castling
    } else if (pathLengthX > 1 || pathLengthY > 1) {
        return false; // Not moving one square
    } else if (square.at(0) > 7 || square.at(0) < 0 || square.at(1) > 7 || square.at(1) < 0) {
        return false; // Moving out of bounds
    } else if (pieceBoard->getPieceAt(square)->getColor() != color) {
            return true; // Not moving to same colored piece
    } else {
        return false;
    }
}
