#include "interface/KingViewConsole.h"

KingViewConsole::KingViewConsole(Color color) {
    if (color == Color::White) {
        displayCharColor = "w";
    } else if (color == Color::Black) {
        displayCharColor = "b";
    }
}