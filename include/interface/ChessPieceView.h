#pragma once
#include "app_logic/Enums.h"
#include <string>
class ChessPieceView {
    public:
        virtual ~ChessPieceView() {};
        virtual std::string getConsoleDisplay() = 0;
    protected:
};