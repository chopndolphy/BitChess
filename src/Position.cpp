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
    uint64_t moves = 0;
    if (whitesTurn) {
        (pawn_bb & white_bb & piece) ? moves = (piece << 8 | piece << 16) : 
        moves = 0;
    } else {
        (pawn_bb & black_bb & piece) ? moves = (piece >> 8 | piece >> 16) : 
        moves = 0;
    }
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
    if (whitesTurn) {
        if (pawn_bb & white_bb & from) pawn_bb ^= fromTo;
        //insert more piece checks 
        if (to & black_bb) {
            black_bb ^= to;
            if (pawn_bb & black_bb & to) pawn_bb ^= to;
            //insert more piece checks
            pieces_bb ^= from;
        } else {
            pieces_bb ^= fromTo;
        }
        white_bb ^= fromTo;
    } else {
        if (pawn_bb & black_bb & from) pawn_bb ^= fromTo;
        //insert more piece checks
        if (to & white_bb) {
            white_bb ^= to;
            if (pawn_bb & white_bb & from) pawn_bb ^= to;
            //insert more piece checks
            pieces_bb ^= from;
        } else {
            pieces_bb ^= fromTo;
        }
        black_bb ^= fromTo;
    }
}
