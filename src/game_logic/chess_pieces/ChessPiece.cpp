#include "forward.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

ChessPiece::ChessPiece(): movedYet(false), doubleMoved(false) {}

void ChessPiece::move(std::vector<int> square) {
    pieceBoard->setPieceAt(square, this);
    location = square;
    movedYet = true;
}