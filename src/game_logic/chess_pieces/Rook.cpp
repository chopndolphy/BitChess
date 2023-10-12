#include "Rook.h"
#include "ChessBoard.h"

Rook::Rook(Location square, Color pieceColor, ChessBoard* board) {
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
}

bool Rook::isLegalMove(Location square) {
    Location location = getLocation();

    std::cout << "this piece hasn't been implemented yet\n";
    return false; // temporary
}