#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "app_logic/Enums.h"
#include <array>

class ChessBoard;
class ChessPiece;
class Player;

class UserInterface {
public:
    virtual std::string getMove(Color color) = 0;
    virtual void displayError(std::string message) = 0;
    virtual void displayGameOver(GameState gameState) = 0;
    virtual void displayBoard(std::array<std::array<std::string, 8>, 8> boardView) = 0;
};