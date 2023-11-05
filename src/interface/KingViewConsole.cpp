#include "interface/KingViewConsole.h"

KingViewConsole::KingViewConsole(Color color) {
    if (color == White) {
        displayCharColor = "w";
    } else if (color == Black) {
        displayCharColor = "b";
    }
}