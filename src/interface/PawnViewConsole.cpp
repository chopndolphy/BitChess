#include "interface/PawnViewConsole.h"

PawnViewConsole::PawnViewConsole(Color color) {
    if (color == White) {
        displayCharColor = "w";
    } else if (color == Black) {
        displayCharColor = "b";
    }
}