#include "King.h"
King::King(std::vector<int> square, Color pieceColor, ChessBoard* board) {
    location = square;
    color = pieceColor;
    pieceBoard = board;
}
bool King::isLegalMove(std::vector<int> square) {
    
}