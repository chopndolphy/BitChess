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
    ChessPiece* piece() const {
        return chessPiece;
    }
private:
    ChessPiece* chessPiece;
    Coord coord;
    Color squareColor;
    void assignSquareColor();
};