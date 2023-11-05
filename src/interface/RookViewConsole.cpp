#include "interface/RookViewConsole.h"

RookViewConsole::RookViewConsole(Color color) {
    if (color == White) {
        displayCharColor = "w";
    } else if (color == Black) {
        displayCharColor = "b";
    }
}