#include "Knight.h"
Knight::Knight(std::vector<int> square, Color pieceColor, ChessBoard* board) {
    location = square;
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
}
bool Knight::isLegalMove(std::vector<int> square) {
    int pathLengthX = std::abs(square.at(0) - location.at(0));
    int pathLengthY = std::abs(square.at(1) - location.at(1));
    if (square == location) {
        return false;
    } else if (pieceBoard->getPieceAt(square)->getColor() == color) {
        return false;
    } else if (location.at(0) > 7 || location.at(0) < 0 || location.at(1) > 7 || location.at(1) < 0) {
        return false;
    } else if ((pathLengthX == 1 && pathLengthY == 2) || (pathLengthX == 2 && pathLengthY == 1)) {
            return true;
    } else {
        return false;
    }
}