#include "app_logic/Coord.h"

Coord::Coord(int xIndex, int yIndex) {
    index.first = xIndex;
    index.second = yIndex;
    square.first = indexToSqaure(xIndex, File);
    square.second = indexToSqaure(yIndex, Rank);
    }
Coord::Coord(char file, char rank) {
    square.first = std::toupper(file);
    square.second = std::toupper(rank);
    index.first = squareToIndex(file);
    index.second = squareToIndex(rank);
    }
void Coord::setIndex(int xIndex, int yIndex) {
    index.first = xIndex;
    index.second = yIndex;
    square.first = indexToSqaure(xIndex, File);
    square.second = indexToSqaure(yIndex, Rank);
    }
void Coord::setSquare(char file, char rank) {
    square.first = std::toupper(file);
    square.second = std::toupper(rank);
    index.first = squareToIndex(file);
    index.second = squareToIndex(rank);
    }
void Coord::setXIndex(int xIndex) {
    index.first = xIndex;
    square.first = indexToSqaure(xIndex, File);
    }
void Coord::setYIndex(int yIndex) {
    index.second = yIndex;
    square.second = indexToSqaure(yIndex, Rank);
    }
void Coord::setFile(char file) {
    square.first = std::toupper(file);
    index.first = squareToIndex(file);
    }
void Coord::setRank(char rank) {
    square.second = std::toupper(rank);
    index.second = squareToIndex(rank);
    }
int Coord::squareToIndex(char fileOrRank) {
    char character = toupper(fileOrRank);
    if ('0' < character < '9') { // is a number between 1 and 8
        character -= '1';
    } else if ('@' < character < 'I') { // is a letter between A and H
        character -= 'A';
    }
    return static_cast<int>(character);
}
char Coord::indexToSqaure(int xOrY, SquareAxis fileOrRank) {
    int number = xOrY;
    switch (fileOrRank) {
        case File:
            number += 65;
            break;
        case Rank:
            number += 49;
            break;
    }
    return static_cast<char>(number);
}