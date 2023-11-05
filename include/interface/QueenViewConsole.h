#pragma once
#include "interface/ChessPieceView.h"

class QueenViewConsole : public ChessPieceView {
    public:
        public:
        ~QueenViewConsole() {};
        QueenViewConsole(Color color);
        std::string getConsoleDisplay() {
            return displayCharColor + displayCharPieceType;
        }
    protected:
        std::string displayCharPieceType = "Q";
        std::string displayCharColor;
};