#pragma once

#include "app_logic/Enums.h"
#include "app_logic/Coord.h"

class ChessPiece;

class Square {
public:
    Square(Coord coord);
    Square(Coord coord, ChessPiece* chessPiece);
    ~Square();
    void addChessPiece(ChessPiece* chessPiece);
    void removeChessPiece();
    ChessPiece* getPiece() const {
        return chessPiece;
    }
    void moveToThisSquare(Square* previousLocation);
private:
    ChessPiece* chessPiece;
    Coord coord;
    Color squareColor;
    void assignSquareColor();
};