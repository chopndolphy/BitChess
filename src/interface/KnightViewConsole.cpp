#include "interface/KnightViewConsole.h"

KnightViewConsole::KnightViewConsole(Color color) {
    if (color == White) {
        displayCharColor = "w";
    } else if (color == Black) {
        displayCharColor = "b";
    }
}