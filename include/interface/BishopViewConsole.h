#pragma once
#include "interface/ChessPieceView.h"

class BishopViewConsole : public ChessPieceView {
    public:
        ~BishopViewConsole() {};
        BishopViewConsole(Color color);
        std::string getConsoleDisplay() {
            return displayCharColor + displayCharPieceType;
        }
    protected:
        std::string displayCharPieceType = "B";
        std::string displayCharColor;
};