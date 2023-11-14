#include "interface/RookViewConsole.h"

RookViewConsole::RookViewConsole(Color color) {
    if (color == Color::White) {
        displayCharColor = "w";
    } else if (color == Color::Black) {
        displayCharColor = "b";
    }
}