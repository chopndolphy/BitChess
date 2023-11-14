#include "interface/KnightViewConsole.h"

KnightViewConsole::KnightViewConsole(Color color) {
    if (color == Color::White) {
        displayCharColor = "w";
    } else if (color == Color::Black) {
        displayCharColor = "b";
    }
}