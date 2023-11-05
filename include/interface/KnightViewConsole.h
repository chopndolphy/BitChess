#pragma once
#include "interface/ChessPieceView.h"

class KnightViewConsole : public ChessPieceView {
    public:
        public:
        ~KnightViewConsole() {};
        KnightViewConsole(Color color);
        std::string getConsoleDisplay() {
            return displayCharColor + displayCharPieceType;
        }
    protected:
        std::string displayCharPieceType = "N";
        std::string displayCharColor;
};