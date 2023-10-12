#include "forward.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

ChessPiece::ChessPiece(): movedYet(false), doubleMoved(false) {}

void ChessPiece::move(Location square) {
    pieceBoard->setPieceAt(square, this);
    movedYet = true;
}

Location ChessPiece::getLocation() const {
    return pieceBoard->getLocation(this);
}