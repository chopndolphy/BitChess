#pragma once

enum class GameState {
    Continue,
    WhiteWins,
    BlackWins,
    Stalemate,
};
enum class Color {
    White,
    Black,
};
enum class ViewType {
    Console,
    GUI2D,
    GUI3D,
};
enum class ErrorCode {
    MOVE01,
    MOVE02,
    MOVE03,
    GAME01,
};
enum class PieceType {
    RookType,
    KnightType,
    BishopType,
    QueenType,
    KingType,
    PawnType,
};
enum class SquareAxis {
    File,
    Rank,
};
enum class BoardLayouts {
    Empty,
    Normal,
};