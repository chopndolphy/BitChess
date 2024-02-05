#pragma once
#include <stdint.h>
#include <string>
#include <Bitboard.h>

class Position {
    public:
        Position();
        uint64_t pawn_bb;
        uint64_t knight_bb;
        uint64_t bishop_bb;
        uint64_t rook_bb;
        uint64_t queen_bb;
        uint64_t king_bb;
        uint64_t white_bb;
        uint64_t black_bb;
        uint64_t pieces_bb;
        uint64_t GetQuietMoves(uint64_t piece, bool whitesTurn);
        uint64_t GetCaptures(uint64_t piece, bool whitesTurn);
        std::string GetBoardString();
        void MakeMove(uint64_t from, uint64_t to, bool whitesTurn);
};