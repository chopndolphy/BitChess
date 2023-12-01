#pragma once

#include "app_logic/Enums.h"
#include "app_logic/Coord.h"
#include <memory>

class ChessPiece;

class Square {
public:
    Square(Coord coord);
    Square(Coord coord, std::unique_ptr<ChessPiece> chessPiece);
    ~Square();
    void addChessPiece(std::unique_ptr<ChessPiece> chessPiece);
    void removeChessPiece();
    const ChessPiece* getPiece() const {
        return chessPiece.get();
    }
    void moveToThisSquare(Square* previousSquare);
private:
    std::unique_ptr<ChessPiece> chessPiece;
    Coord coord;
    Color squareColor;
    void assignSquareColor();
};