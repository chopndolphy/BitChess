#pragma once
#include "interface/ChessPieceView.h"

class PawnViewConsole : public ChessPieceView {
    public:
        public:
        ~PawnViewConsole() {};
        PawnViewConsole(Color color);
        std::string getConsoleDisplay() {
            return displayCharColor + displayCharPieceType;
        }
    protected:
        std::string displayCharPieceType = " ";
        std::string displayCharColor;
};