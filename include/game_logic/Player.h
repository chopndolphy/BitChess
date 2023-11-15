#pragma once
#include <vector>
#include "app_logic/Enums.h"
#include "app_logic/ErrorLogger.h"
#include "app_logic/Coord.h"

class ChessPiece;
class UserInterface;
class ChessBoard;
class Player {
    public:
        Player(Color color, ChessBoard* board, UserInterface* interface);
        void makeMove();
        Color getColor() const {
            return color;
        }
    private:
        Color color;
        ChessBoard* board;
        UserInterface* interface;
};