#include "Bitboard.h"
#include "Position.h"

uint64_t Bitboard::RemoveIllegalMoves(uint64_t startSquare, uint64_t pseudoLegalMoves, const Position &position) {
    bool whitesTurn = startSquare & position.white_bb;
    uint64_t legalMoves = pseudoLegalMoves;

    uint64_t biterator = 0x8000000000000000;
    std::vector<uint64_t> moves;
    for (size_t i = 0; i < 64; i++) {
        if (biterator & pseudoLegalMoves) {
            moves.push_back(biterator);
        }
        biterator >>= 1;
    }
    for (auto move : moves) {
        uint64_t pawns = position.pawn_bb;
        uint64_t knights = position.knight_bb;
        uint64_t bishops = position.bishop_bb;
        uint64_t rooks = position.rook_bb;
        uint64_t queens = position.queen_bb;
        uint64_t kings = position.king_bb;
        uint64_t white = position.white_bb;
        uint64_t black = position.black_bb;
        uint64_t pieces = position.pieces_bb;
        // makes move 
        uint64_t fromTo = startSquare | move;
        if (whitesTurn && (move & black)) { // white capturing
            black ^= move;
            if (pawns & move) pawns ^= move;
            if (knights & move) knights ^= move;
            if (bishops & move) bishops ^= move;
            if (rooks & move) rooks ^= move;
            if (queens & move) queens ^= move;
            if (kings & move) kings ^= move;
        } else if (!whitesTurn && (move & white)) { // black capturing
            white ^= move;
            if (pawns & move) pawns ^= move;
            if (knights & move) knights ^= move;
            if (bishops & move) bishops ^= move;
            if (rooks & move) rooks ^= move;
            if (queens & move) queens ^= move;
            if (kings & move) kings ^= move;
        }
        if (whitesTurn) {
            white ^= fromTo;
        } else {
            black ^= fromTo;
        }
        if (pawns & startSquare) pawns ^= fromTo;
        if (knights & startSquare) knights ^= fromTo;
        if (bishops & startSquare) bishops ^= fromTo;
        if (rooks & startSquare) rooks ^= fromTo;
        if (queens & startSquare) queens ^= fromTo;
        if (kings & startSquare) kings ^= fromTo;
        pieces = (white | black);

        uint64_t myKing;
        if (whitesTurn) {
            myKing = white & kings;
        } else {
            myKing = black & kings;
        }
        //checks if king is in check

        if (whitesTurn) {
            uint64_t pawnAttacks = (((myKing << 7) & Bitboard::notAfile_bb) |
                        ((myKing << 9) & Bitboard::notHfile_bb));
            if (pawnAttacks & black & pawns) {
                legalMoves ^= move;
                continue;
            };
        } else if (!whitesTurn) {
            uint64_t pawnAttacks = (((myKing >> 7) & Bitboard::notHfile_bb) |
                        ((myKing >> 9) & Bitboard::notAfile_bb));
            if (pawnAttacks & white & pawns) {
                legalMoves ^= move;
                continue;
            };
        }
        uint64_t knightAttacks = (((myKing <<  6) & Bitboard::notABfile_bb) |
            ((myKing << 10) & Bitboard::notGHfile_bb) | 
            ((myKing << 15) & Bitboard::notAfile_bb ) | 
            ((myKing << 17) & Bitboard::notHfile_bb ) | 
            ((myKing >>  6) & Bitboard::notGHfile_bb) |
            ((myKing >> 10) & Bitboard::notABfile_bb) |
            ((myKing >> 15) & Bitboard::notHfile_bb ) |
            ((myKing >> 17) & Bitboard::notAfile_bb ));
        if (knightAttacks & (whitesTurn? black : white) & knights) {
            legalMoves ^= move;
            continue;
        }

        uint64_t kingAttacks = (((myKing << 1) & Bitboard::notHfile_bb) |
                    ((myKing << 7) & Bitboard::notAfile_bb) |
                    ((myKing << 8)                        ) |
                    ((myKing << 9) & Bitboard::notHfile_bb) |
                    ((myKing >> 1) & Bitboard::notAfile_bb) |
                    ((myKing >> 7) & Bitboard::notHfile_bb) |
                    ((myKing >> 8)                        ) |
                    ((myKing >> 9) & Bitboard::notAfile_bb));
        if (kingAttacks & (whitesTurn? black : white) & kings) {
            legalMoves ^= move;
            continue;
        }


        uint64_t empty = ~pieces;
        uint64_t scan = myKing;
        uint64_t flood = myKing;
        
        scan = myKing;
        flood = myKing;
        empty = ~pieces & Bitboard::notHfile_bb;
        flood |= scan = (scan << 9) & empty; // northwest
        flood |= scan = (scan << 9) & empty;
        flood |= scan = (scan << 9) & empty;
        flood |= scan = (scan << 9) & empty;
        flood |= scan = (scan << 9) & empty;
        flood |=        (scan << 9) & empty; 
        uint64_t diagAttacks = (flood << 9) & Bitboard::notHfile_bb; // might later change to not include captures
        
        scan = myKing;
        flood = myKing;
        empty = ~pieces & Bitboard::notAfile_bb;
        flood |= scan = (scan >> 9) & empty; // southeast
        flood |= scan = (scan >> 9) & empty;
        flood |= scan = (scan >> 9) & empty;
        flood |= scan = (scan >> 9) & empty;
        flood |= scan = (scan >> 9) & empty;
        flood |=        (scan >> 9) & empty; 
        diagAttacks |= (flood >> 9) & Bitboard::notAfile_bb; // might later change to not include captures


        scan = myKing;
        flood = myKing;
        empty = ~pieces & Bitboard::notAfile_bb;
        flood |= scan = (scan << 7) & empty; // northeast
        flood |= scan = (scan << 7) & empty;
        flood |= scan = (scan << 7) & empty;
        flood |= scan = (scan << 7) & empty;
        flood |= scan = (scan << 7) & empty;
        flood |=        (scan << 7) & empty; 
        diagAttacks |= (flood << 7) & Bitboard::notAfile_bb; // might later change to not include captures
        
        scan = myKing;
        flood = myKing;
        empty = ~pieces & Bitboard::notHfile_bb;
        flood |= scan = (scan >> 7) & empty; // southwest
        flood |= scan = (scan >> 7) & empty;
        flood |= scan = (scan >> 7) & empty;
        flood |= scan = (scan >> 7) & empty;
        flood |= scan = (scan >> 7) & empty;
        flood |=        (scan >> 7) & empty; 
        diagAttacks |= (flood >> 7) & Bitboard::notHfile_bb; // might later change to not include captures

        if (diagAttacks & (whitesTurn? black : white) & (queens | bishops)) {
            legalMoves ^= move;
            continue;
        }

        empty = ~pieces;
        scan = myKing;
        flood = myKing;

        flood |= scan = (scan << 8) & empty; // north
        flood |= scan = (scan << 8) & empty;
        flood |= scan = (scan << 8) & empty;
        flood |= scan = (scan << 8) & empty;
        flood |= scan = (scan << 8) & empty;
        flood |=        (scan << 8) & empty; 
        uint64_t rookAttacks = flood << 8; // might later change to not include captures

        scan = myKing;
        flood = myKing;
        flood |= scan = (scan >> 8) & empty; // south
        flood |= scan = (scan >> 8) & empty;
        flood |= scan = (scan >> 8) & empty;
        flood |= scan = (scan >> 8) & empty;
        flood |= scan = (scan >> 8) & empty;
        flood |=        (scan >> 8) & empty; 
        rookAttacks |= flood >> 8; // might later change to not include captures

        scan = myKing;
        flood = myKing;
        empty = ~pieces & Bitboard::notHfile_bb;
        flood |= scan = (scan << 1) & empty; // west
        flood |= scan = (scan << 1) & empty;
        flood |= scan = (scan << 1) & empty;
        flood |= scan = (scan << 1) & empty;
        flood |= scan = (scan << 1) & empty;
        flood |=        (scan << 1) & empty; 
        rookAttacks |= (flood << 1) & Bitboard::notHfile_bb; // might later change to not include captures
        
        scan = myKing;
        flood = myKing;
        empty = ~pieces & Bitboard::notAfile_bb;
        flood |= scan = (scan >> 1) & empty; // east
        flood |= scan = (scan >> 1) & empty;
        flood |= scan = (scan >> 1) & empty;
        flood |= scan = (scan >> 1) & empty;
        flood |= scan = (scan >> 1) & empty;
        flood |=        (scan >> 1) & empty; 
        rookAttacks |= (flood >> 1) & Bitboard::notAfile_bb; // might later change to not include captures

        if (rookAttacks & (whitesTurn? black : white) & (queens | rooks)) {
            legalMoves ^= move;
            continue;
        }
    }
    return legalMoves;
}
