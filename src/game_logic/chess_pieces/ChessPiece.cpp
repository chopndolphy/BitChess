#include "forward.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

ChessPiece::ChessPiece(): movedYet(false), lastMoved(false), doubleMoved(false) {}

void ChessPiece::move(Location square) {
    pieceBoard->setPieceAt(square, this);
    lastMoved = movedYet = true;
}

Location ChessPiece::getLocation() const {
    return pieceBoard->getLocation(this);
}

void ChessPiece::cleanState() {
    lastMoved = doubleMoved = false;
}