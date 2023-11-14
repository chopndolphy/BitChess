#include "game_logic/Rook.h"

Rook::Rook(std::vector<int> square, Color pieceColor, ChessBoard* board) {
    location = square;
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
    createView(color, PieceType::RookType);
}
bool Rook::isLegalMove(std::vector<int> square) {
    
}