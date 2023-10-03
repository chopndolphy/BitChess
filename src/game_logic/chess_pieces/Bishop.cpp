#include "Bishop.h"
Bishop::Bishop(std::vector<int> square, Color pieceColor, ChessBoard* board) {
    location = square;
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
}
bool Bishop::isLegalMove(std::vector<int> square) {
    int pathLength = std::abs(square.at(0) - location.at(0));
    if (square == location) {
        return false;
    } else if (pathLength != std::abs(square.at(1) - location.at(1))) {
        return false;
    } else if (pathLength < 8) {
        for (int i = 1; i < pathLength; i++) {
            int x, y;
            if (square.at(0) - location.at(0) > 0) {
                int x = location.at(0) + i;
            } else {
                int x = location.at(0) - i;
            }
            if (square.at(1) - location.at(1) > 0) {
                int y = location.at(1) + i;
            } else {
                int y = location.at(1) - i;
            }
            if (pieceBoard->getPieceAt({x, y}) != nullptr) {
                return false;
            }
        }
        if (pieceBoard->getPieceAt(square)->getColor() != color) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}