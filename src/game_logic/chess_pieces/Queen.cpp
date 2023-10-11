#include "Queen.h"
#include "ChessBoard.h"

Queen::Queen(std::vector<int> square, Color pieceColor, ChessBoard* board) {
    location = square;
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
}
bool Queen::isLegalMove(std::vector<int> square) {
    
}