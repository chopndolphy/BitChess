#include "Queen.h"
Queen::Queen(std::vector<int> square, Color pieceColor, ChessBoard* board) {
    location = square;
    color = pieceColor;
    pieceBoard = board;
}
bool Queen::isLegalMove(std::vector<int> square) {
    
}