#pragma once
#include <stdint.h>

class Board {
    public:
        Board();
        uint64_t pawn_bb;
        uint64_t knight_bb;
        uint64_t bishop_bb;
        uint64_t rook_bb;
        uint64_t queen_bb;
        uint64_t king_bb;
        uint64_t white_bb;
        uint64_t black_bb;
        uint64_t pieces_bb;
};