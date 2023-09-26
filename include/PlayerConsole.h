#pragma once
#include "Player.h"
#include "UserInterfaceConsole.h"

class PlayerConsole : public Player {
    public:
        PlayerConsole(Color color, ChessBoard* board, UserInterface* interface);
        void makeMove();
};