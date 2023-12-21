#pragma once

#include "app_logic/Enums.h"
#include "app_logic/Coord.h"
#include <memory>

class ChessPiece;

class Square {
public:
    Square(Coord coord);
    Square(Coord coord, ChessPiece* piece);
    ~Square();
    void addChessPiece(ChessPiece* piece);
    void removeChessPiece();
    ChessPiece* getPiece() {
        return chessPiece;
    }
    void moveToThisSquare(Square* previousSquare);
    void deleteChessPiece();
private:
    ChessPiece* chessPiece;
    Coord coord;
    Color squareColor;
    void assignSquareColor();
};