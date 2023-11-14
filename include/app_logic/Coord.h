#pragma once
#include <cctype>
#include <utility>
#include "app_logic/Enums.h"

class Coord {
public:
    Coord(int xIndex, int yIndex);
    Coord(char file, char rank);
    Coord();
    void setIndex(int xIndex, int yIndex);
    void setSquare(char file, char rank);
    void setXIndex(int xIndex);
    void setYIndex(int yIndex);
    void setFile(char file);
    void setRank(char rank);
    int x() const { return index.first; }
    int y() const { return index.second; }
    char file() const { return square.first; }
    char rank() const { return square.second; }

private:
    std::pair<int, int> index;
    std::pair<char, char> square;
    int squareToIndex(char fileOrRank);
    char indexToSqaure(int xOrY, SquareAxis fileOrRank);
};