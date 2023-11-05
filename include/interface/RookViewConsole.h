#pragma once
#include "interface/ChessPieceView.h"

class RookViewConsole : public ChessPieceView {
    public:
        public:
        ~RookViewConsole() {};
        RookViewConsole(Color color);
        std::string getConsoleDisplay() {
            return displayCharColor + displayCharPieceType;
        }
    protected:
        std::string displayCharPieceType = "R";
        std::string displayCharColor;
};