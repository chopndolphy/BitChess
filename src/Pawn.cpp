#include "Pawn.h"
Pawn::Pawn(std::vector<int> square, bool isWhiteBool) {
    location = square;
    isWhite = isWhiteBool;
}