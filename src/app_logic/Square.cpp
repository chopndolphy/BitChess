#include "app_logic/Square.h"
#include "game_logic/ChessPiece.h"

Square::Square(Coord coord) {
    this->coord = coord;
    assignSquareColor();
}
Square::Square(Coord coord, ChessPiece* chessPiece) {
    this->coord = coord;
    this->chessPiece = chessPiece;
    assignSquareColor();
}
Square::~Square() {
    delete chessPiece;
}
void Square::addChessPiece(ChessPiece* chessPiece) {
    this->chessPiece = chessPiece;
}
void Square::removeChessPiece() {
    this->chessPiece = nullptr;
}
void Square::assignSquareColor() {
    if (coord.x() % 2 == coord.y() % 2) {
        squareColor = Color::Black;
    } else {
        squareColor = Color::White;
    }
}
