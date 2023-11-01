#pragma once

enum GameState {
    Continue,
    WhiteWins,
    BlackWins,
    Stalemate,
};
enum Color {
    White,
    Black,
};
enum ViewType {
    Console,
    GUI2D,
    GUI3D,
};
enum ErrorCode {
    MOVE01,
    MOVE02,
    GAME01,
};
enum PieceType {
    RookType,
    KnightType,
    BishopType,
    QueenType,
    KingType,
    PawnType,
};