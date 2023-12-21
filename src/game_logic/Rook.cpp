#include "game_logic/Rook.h"
#include "interface/RookViewConsole.h"

Rook::Rook(Color color, Coord location, ChessBoard* board) {
    this->location = location;
    this->color = color;
    this->board = board;
    movedYet = false;
    createView();
}
bool Rook::isLegalMove(Coord destination) {
    
}
void Rook::createView() {
    view = new RookViewConsole(color);
}