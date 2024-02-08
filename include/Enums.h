#pragma once

enum class GameOver {
    None,
    Checkmate,
    Stalemate,
    DeadPosition,
    ThreeRepetition,
    FiftyNothingMoves,
};
enum class EndDisplay {
    None,
    White,
    Black,
    Draw,
};