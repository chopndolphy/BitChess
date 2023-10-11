#include "Rook.h"
#include "ChessBoard.h"

Rook::Rook(std::vector<int> square, Color pieceColor, ChessBoard* board) {
    location = square;
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
}

bool Rook::isLegalMove(std::vector<int> square) {
    std::cout << "this piece hasn't been implemented yet\n";
    return false; // temporary
}