#include "Pawn.h"
Pawn::Pawn(std::vector<int> square, Color pieceColor, ChessBoard* board) {
    location = square;
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
}
bool Pawn::isLegalMove(std::vector<int> square) {
    
}