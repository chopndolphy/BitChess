#include "Pawn.h"
#include "ChessBoard.h"

Pawn::Pawn(Location square, Color pieceColor, ChessBoard* board) {
    color = pieceColor;
    pieceBoard = board;
    movedYet = false;
    doubleMoved = false;
}

bool Pawn::isLegalMove(Location square) {
    Location location = getLocation();

    int xdelta = square.x - location.x;
    int ydelta = square.y - location.y;
    int pathLengthX = std::abs(xdelta);
    int pathLengthY = std::abs(ydelta);

    ChessPiece* collide = pieceBoard->collisionLine(location, square);
    if(collide == nullptr){
        return false; // invalid move
    }

    if ( (ydelta > 0 && color == White) || (ydelta < 0 && color == Black) ) {
        return false; // White is moving down or Black is moving up
    }

    if(collide == this) { // no collisions
        if(pathLengthX == 0) { // normal ortho move
            if (pathLengthY == 1) {
                return true; // Moving forward one
            }
            if (pathLengthY == 2 && !movedYet) {
                doubleMoved = true;
                return true; // Moving forward two on first turn
            }
        }
        if(pathLengthX == 1 && pathLengthY == 1) { // check En Passant
            ChessPiece* enPass = pieceBoard->getPieceAt( Location(location.x + xdelta, location.y) ); // get that piece then check
            if(enPass != nullptr && enPass->getColor() != color && enPass->hasDoubleMoved()){
                pieceBoard->removePieceAt(enPass->getLocation()); // this should really be part of an action and not a calculation - both isLegalMove and makeMove need some rework for this to happen
                return true;
            }
        }
    } else {
        if(collide->getColor() != color && pathLengthX == 1 && pathLengthY == 1) { // collides with a different color and moves at a diagonal
            return true;
        }
    }

    return false; // invalid move
}