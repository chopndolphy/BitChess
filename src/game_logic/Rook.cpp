#include "game_logic/Rook.h"

Rook::Rook(Color color, Coord location, ChessBoard* board) {
    this->location = location;
    this->color = color;
    this->board = board;
    movedYet = false;
    createView(color, PieceType::RookType);
}
bool Rook::isLegalMove(Coord destination) {
    
}