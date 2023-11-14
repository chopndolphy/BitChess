#include "game_logic/Queen.h"

Queen::Queen(std::vector<int> square, Color pieceColor, ChessBoard* board) {
    location = square;
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
    createView(color, PieceType::QueenType);
}
bool Queen::isLegalMove(std::vector<int> square) {
    
}