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
enum Pieces {
    Pawn_w        =  0, 
    Pawn_b        =  1,
    Knight_w      =  2,
    Knight_b      =  3,
    Bishop_w      =  4,
    Bishop_b      =  5,
    Rook_w        =  6,
    Rook_b        =  7,
    Queen_w       =  8,
    Queen_b       =  9,
    King_w        = 10,
    King_b        = 11,
    EnPassant_w   = 12,
    EnPassant_b   = 13,
};