#include "Position.h"
#include "Util.h"

Position::Position() {
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
uint64_t Position::GetCaptures(uint64_t piece, bool whitesTurn) {
    uint64_t moves = 0;
    if (whitesTurn) {

    } else {

    }
    return moves;
}
uint64_t Position::GetQuietMoves(uint64_t piece, bool whitesTurn) {
    if ((!whitesTurn && (white_bb & piece)) || (whitesTurn && (black_bb & piece))) {
        return 0;
    }
    uint64_t moves = 0;

    if (whitesTurn && (pawn_bb & piece)) {
        moves |= piece << 8;
        if (piece & (Bitboard::horiLine_bb << 8)) { // pawn is at start square and can move two
            moves |= piece << 16;
        }
    } else if (!whitesTurn && (pawn_bb & piece)) {
        moves |= piece >> 8;
        if (piece & (Bitboard::horiLine_bb << 48)) { // pawn is at start square and can move two
            moves |= piece >> 16;
        }
    } else if (knight_bb & piece) {
        moves = (((piece <<  6) & Bitboard::notABfile_bb) |
                 ((piece << 10) & Bitboard::notGHfile_bb) | 
                 ((piece << 15) & Bitboard::notAfile_bb ) | 
                 ((piece << 17) & Bitboard::notHfile_bb ) | 
                 ((piece >>  6) & Bitboard::notGHfile_bb) |
                 ((piece >> 10) & Bitboard::notABfile_bb) |
                 ((piece >> 15) & Bitboard::notHfile_bb ) |
                 ((piece >> 17) & Bitboard::notAfile_bb ));
    }

    moves &= ~pieces_bb;

    return moves;
}
std::string Position::GetBoardString() {
    std::string boardString(64, '-');
    Util::PopulateStringBoard(boardString, (pawn_bb & white_bb), 'P');
    Util::PopulateStringBoard(boardString, (pawn_bb & black_bb), 'p');
    Util::PopulateStringBoard(boardString, (knight_bb & white_bb), 'N');
    Util::PopulateStringBoard(boardString, (knight_bb & black_bb), 'n');
    Util::PopulateStringBoard(boardString, (bishop_bb & white_bb), 'B');
    Util::PopulateStringBoard(boardString, (bishop_bb & black_bb), 'b');
    Util::PopulateStringBoard(boardString, (rook_bb & white_bb), 'R');
    Util::PopulateStringBoard(boardString, (rook_bb & black_bb), 'r');
    Util::PopulateStringBoard(boardString, (queen_bb & white_bb), 'Q');
    Util::PopulateStringBoard(boardString, (queen_bb & black_bb), 'q');
    Util::PopulateStringBoard(boardString, (king_bb & white_bb), 'K');
    Util::PopulateStringBoard(boardString, (king_bb & black_bb), 'k');
    return boardString;
}
void Position::MakeMove(uint64_t from, uint64_t to, bool whitesTurn){
    uint64_t fromTo = from | to;
    if (whitesTurn && (to & black_bb)) { // white capturing
        black_bb ^= to;
        if (pawn_bb & to) pawn_bb ^= to;
        if (knight_bb & to) knight_bb ^= to;
        if (bishop_bb & to) bishop_bb ^= to;
        if (rook_bb & to) rook_bb ^= to;
        if (queen_bb & to) queen_bb ^= to;
        if (king_bb & to) king_bb ^= to;
    } else if (!whitesTurn && (to & white_bb)) { // black capturing
        white_bb ^= to;
        if (pawn_bb & to) pawn_bb ^= to;
        if (knight_bb & to) knight_bb ^= to;
        if (bishop_bb & to) bishop_bb ^= to;
        if (rook_bb & to) rook_bb ^= to;
        if (queen_bb & to) queen_bb ^= to;
        if (king_bb & to) king_bb ^= to;
    }
    if (whitesTurn) {
        white_bb ^= fromTo;
    } else {
        black_bb ^= fromTo;
    }
    if (pawn_bb & from) pawn_bb ^= fromTo;
    if (knight_bb & from) knight_bb ^= fromTo;
    if (bishop_bb & from) bishop_bb ^= fromTo;
    if (rook_bb & from) rook_bb ^= fromTo;
    if (queen_bb & from) queen_bb ^= fromTo;
    if (king_bb & from) king_bb ^= fromTo;
    pieces_bb = (white_bb | black_bb);
}