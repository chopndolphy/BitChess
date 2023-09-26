#pragma once
#include <vector>
#include "Enums.h"
#include "ChessPiece.h"
#include "UserInterface.h"
#include "ChessBoard.h"
#include "ErrorLogger.h"

class Player {
    public:
        virtual void makeMove() = 0;
        const Color getColor() const {
            return playerColor;
        }
    protected:
        Color playerColor;
        ChessBoard* playerBoard;
        UserInterface* playerInterface;
};