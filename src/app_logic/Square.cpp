#include "app_logic/Square.h"
#include "game_logic/ChessPiece.h"
#include <memory>

Square::Square(Coord coord) {
    this->coord = coord;
    this->chessPiece = nullptr;
    assignSquareColor();
}
Square::Square(Coord coord, std::unique_ptr<ChessPiece> chessPiece) {
    this->coord = coord;
    this->chessPiece = std::move(chessPiece);
    assignSquareColor();
}
Square::~Square() {
}
void Square::addChessPiece(std::unique_ptr<ChessPiece> chessPiece) {
    this->chessPiece = std::move(chessPiece);
}
void Square::removeChessPiece() {
    if (chessPiece = nullptr) {
        return;
    }
    this->chessPiece = nullptr;
}
void Square::assignSquareColor() {
    if (coord.x() % 2 == coord.y() % 2) {
        squareColor = Color::Black;
    } else {
        squareColor = Color::White;
    }
}
void Square::moveToThisSquare(Square* previousSquare) {
    this->chessPiece = std::move(previousSquare->chessPiece);
}

