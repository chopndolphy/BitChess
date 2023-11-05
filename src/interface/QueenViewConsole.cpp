#include "interface/QueenViewConsole.h"

QueenViewConsole::QueenViewConsole(Color color) {
    if (color == White) {
        displayCharColor = "w";
    } else if (color == Black) {
        displayCharColor = "b";
    }
}