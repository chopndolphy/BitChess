#include "interface/BishopViewConsole.h"
#include <iostream>

BishopViewConsole::BishopViewConsole(Color color) {
    if (color == White) {
        displayCharColor = "w";
    } else if (color == Black) {
        displayCharColor = "b";
    }
}