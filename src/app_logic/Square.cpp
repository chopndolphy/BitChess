#include "app_logic/Square.h"
#include "game_logic/ChessPiece.h"
#include <memory>

Square::Square(Coord coord) {
    this->coord = coord;
    chessPiece = nullptr;
    assignSquareColor();
}
Square::Square(Coord coord, ChessPiece* piece) {
    this->coord = coord;
    chessPiece = piece;
    assignSquareColor();
}
Square::~Square() {
}
void Square::addChessPiece(ChessPiece* piece) {
    chessPiece = piece;
}
void Square::removeChessPiece() {
    if (chessPiece == nullptr) {
        return;
    }
    chessPiece = nullptr;
}
void Square::assignSquareColor() {
    if (coord.x() % 2 == coord.y() % 2) {
        squareColor = Color::Black;
    } else {
        squareColor = Color::White;
    }
}
void Square::moveToThisSquare(Square* previousSquare) {
    chessPiece = previousSquare->chessPiece;
    previousSquare->removeChessPiece();
}
void Square::deleteChessPiece() {
    delete chessPiece;
}