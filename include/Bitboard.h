#pragma once
#include <stdint.h>
#include <vector>
class Position;
class Bitboard {
    public:
        static const uint64_t horiLine_bb  = 0x00000000000000FF;
        static const uint64_t notAfile_bb  = 0x7F7F7F7F7F7F7F7F; 
        static const uint64_t notABfile_bb = 0x3F3F3F3F3F3F3F3F; 
        static const uint64_t notHfile_bb  = 0xFEFEFEFEFEFEFEFE; 
        static const uint64_t notGHfile_bb = 0xFCFCFCFCFCFCFCFC; 
        static uint64_t RemoveIllegalMoves(uint64_t startSquare, uint64_t pseudoLegalMoves, const Position &position);
};