#pragma once
#include <vector>

#include "Enums.h"
#include "ChessPiece.h"
#include "UserInterface.h"
#include "ChessBoard.h"
#include "ErrorLogger.h"

class Player {
    public:
        Player(Color color, ChessBoard* board, UserInterface* interface);
        void makeMove();
        const Color getColor() const {
            return playerColor;
        }
    private:
        Color playerColor;
        ChessBoard* playerBoard;
        UserInterface* playerInterface;
};