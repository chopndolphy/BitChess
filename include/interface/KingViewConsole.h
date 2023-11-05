#pragma once
#include "interface/ChessPieceView.h"

class KingViewConsole : public ChessPieceView {
   public:
        ~KingViewConsole() {};
        KingViewConsole(Color color);
        std::string getConsoleDisplay() {
            return displayCharColor + displayCharPieceType;
        }
    protected:
        std::string displayCharPieceType = "K";
        std::string displayCharColor;
};