#include "interface/BishopViewConsole.h"
#include <iostream>

BishopViewConsole::BishopViewConsole(Color color) {
    if (color == Color::White) {
        displayCharColor = "w";
    } else if (color == Color::Black) {
        displayCharColor = "b";
    }
}