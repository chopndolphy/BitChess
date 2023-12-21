#include "game_logic/Queen.h"
#include "interface/QueenViewConsole.h"

Queen::Queen(Color color, Coord location, ChessBoard* board) {
    this->location = location;
    this->color = color;
    this->board = board;
    movedYet = false;
    createView();
}
bool Queen::isLegalMove(Coord destination) {
    
}
void Queen::createView() {
    view = new QueenViewConsole(color);
}