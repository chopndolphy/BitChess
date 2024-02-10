#pragma once
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <random>
#include <cmath>
#include <array>
#include <utility>
#include <iostream>
#include "Bitboard.h"
#include "Enums.h"
#include "HashTable.h"
#include <iterator>


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
        uint64_t enPassantable_bb;
        uint8_t castlingRights;
        uint8_t fiftyMoveCounter;
        HashTable hashKey;
        uint64_t GetQuietMoves(uint64_t piece, bool whitesTurn);
        uint64_t GetCaptures(uint64_t piece, bool whitesTurn);
        uint64_t GetPromotionSquare(uint64_t piece, bool whitesTurn);
        uint64_t GetPromotionOptions(uint64_t promotionSquare, bool whitesTurn);
        std::string GetBoardString();
        bool CheckForNoMoves(bool whitesTurn);
        bool CheckForRepetition(bool whitesTurn);
        bool CheckForDeadPosition();
        uint64_t HashPosition(bool whitesTurn);
        void initZobristHashing();
        void MakeMove(uint64_t from, uint64_t to, bool whitesTurn);
        void PromotePawn(uint64_t from, uint64_t to, uint64_t selectionSquare, bool whitesTurn);
        uint64_t IsInCheck(bool whitesTurn);
        GameOver IsDraw(bool whitesTurn);
        std::unordered_map<uint64_t, bool> whiteRepetitionLookup;
        std::unordered_map<uint64_t, bool> blackRepetitionLookup;
};