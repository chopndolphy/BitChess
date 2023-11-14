#include "interface/QueenViewConsole.h"

QueenViewConsole::QueenViewConsole(Color color) {
    if (color == Color::White) {
        displayCharColor = "w";
    } else if (color == Color::Black) {
        displayCharColor = "b";
    }
}