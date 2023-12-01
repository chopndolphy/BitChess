#include "game_logic/Queen.h"

Queen::Queen(Color color, Coord location, ChessBoard* board) {
    this->location = location;
    this->color = color;
    this->board = board;
    movedYet = false;
    createView(color, PieceType::QueenType);
}
bool Queen::isLegalMove(Coord destination) const {
    
}