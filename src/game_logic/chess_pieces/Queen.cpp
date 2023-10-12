#include "Queen.h"
#include "ChessBoard.h"

Queen::Queen(Location square, Color pieceColor, ChessBoard* board) {
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
}

bool Queen::isLegalMove(Location square) {
    Location location = getLocation();

    std::cout << "this piece hasn't been implemented yet\n";
    return false; // temporary
}