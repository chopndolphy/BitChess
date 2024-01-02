#include "Board.h"

Board::Board() {
    pawn_bb   = 0x00FF00000000FF00;
    knight_bb = 0x4200000000000042; 
    bishop_bb = 0x2400000000000024;
    rook_bb   = 0x8100000000000081;
    queen_bb  = 0x1000000000000010;
    king_bb   = 0x0800000000000008;
    white_bb  = 0x000000000000FFFF;
    black_bb  = 0xFFFF000000000000;
    pieces_bb = 0xFFFF00000000FFFF;
}