#include "Knight.h"
Knight::Knight(std::vector<int> square, Color pieceColor, ChessBoard* board) {
    location = square;
    color = pieceColor;
    pieceBoard = board;
}
bool Knight::isLegalMove(std::vector<int> square) {
    
}