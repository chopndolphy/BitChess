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
        uint64_t enPassantables = position.enPassantable_bb;
        // makes move 
        uint64_t fromTo = startSquare | move;

        if (whitesTurn && (pawns & startSquare) && ((move >> 8) & (enPassantables & black))) {
            enPassantables ^= move >> 8;
            pawns ^= (fromTo | (move >> 8));
            black ^= move >> 8;
            white ^= fromTo;
            pieces = (white | black);
        } else if (!whitesTurn && (pawns & startSquare) && ((move << 8) & (enPassantables & white))) {
            enPassantables ^= move << 8;
            pawns ^= (fromTo | (move << 8));
            white ^= move << 8;
            black ^= fromTo;
            pieces = (white | black);
        } else {  
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
        }

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

uint64_t Bitboard::GenerateCastleMoves(bool whitesTurn, const Position &position) {
    uint64_t castleMoves = 0;

    if ((whitesTurn && (position.castlingRights & 0x01)) && // White Kingside castle
    ((~position.pieces_bb & 0x0000000000000006) == 0x0000000000000006)) {
        bool castleFailed = false;
        std::vector<uint64_t> moves = {2, 4, 8};
        for (auto move : moves) {
            uint64_t pawnAttacks = (((move << 7) & Bitboard::notAfile_bb) |
                                    ((move << 9) & Bitboard::notHfile_bb));
            if (pawnAttacks & position.black_bb & position.pawn_bb) {
                castleFailed = true;
                break;
            }
            uint64_t knightAttacks = (((move <<  6) & Bitboard::notABfile_bb) |
                                      ((move << 10) & Bitboard::notGHfile_bb) | 
                                      ((move << 15) & Bitboard::notAfile_bb ) | 
                                      ((move << 17) & Bitboard::notHfile_bb ));  
            if (knightAttacks & position.black_bb & position.knight_bb) {
                castleFailed = true;
                break;
            }

            uint64_t kingAttacks = (((move << 1) & Bitboard::notHfile_bb) |
                                    ((move << 7) & Bitboard::notAfile_bb) |
                                    ((move << 8)                        ) |
                                    ((move << 9) & Bitboard::notHfile_bb) |
                                    ((move >> 1) & Bitboard::notAfile_bb)); 
            if (kingAttacks & position.black_bb & position.king_bb) {
                castleFailed = true;
                break;
            }


            uint64_t empty = ~position.pieces_bb;
            uint64_t scan = move;
            uint64_t flood = move;
            
            scan = move;
            flood = move;
            empty = ~position.pieces_bb & Bitboard::notHfile_bb;
            flood |= scan = (scan << 9) & empty; // northwest
            flood |= scan = (scan << 9) & empty;
            flood |= scan = (scan << 9) & empty;
            flood |= scan = (scan << 9) & empty;
            flood |= scan = (scan << 9) & empty;
            flood |=        (scan << 9) & empty; 
            uint64_t diagAttacks = (flood << 9) & Bitboard::notHfile_bb; // might later change to not include captures
            
            scan = move;
            flood = move;
            empty = ~position.pieces_bb & Bitboard::notAfile_bb;
            flood |= scan = (scan << 7) & empty; // northeast
            flood |= scan = (scan << 7) & empty;
            flood |= scan = (scan << 7) & empty;
            flood |= scan = (scan << 7) & empty;
            flood |= scan = (scan << 7) & empty;
            flood |=        (scan << 7) & empty; 
            diagAttacks |= (flood << 7) & Bitboard::notAfile_bb; // might later change to not include captures
            
            if (diagAttacks & position.black_bb & (position.queen_bb | position.bishop_bb)) {
                castleFailed = true;
                break;
            }

            empty = ~position.pieces_bb;
            scan = move;
            flood = move;

            flood |= scan = (scan << 8) & empty; // north
            flood |= scan = (scan << 8) & empty;
            flood |= scan = (scan << 8) & empty;
            flood |= scan = (scan << 8) & empty;
            flood |= scan = (scan << 8) & empty;
            flood |=        (scan << 8) & empty; 
            uint64_t rookAttacks = flood << 8; // might later change to not include captures

            if (rookAttacks & position.black_bb & (position.queen_bb | position.rook_bb)) {
                castleFailed = true;
                break;
            }
        }
        if (!castleFailed) {
            castleMoves |= 2;
        }
    }
    if ((whitesTurn && (position.castlingRights & 0x02)) && //White Queenside castle
    ((~position.pieces_bb & 0x0000000000000070) == 0x0000000000000070)) {
        bool castleFailed = false;
        std::vector<uint64_t> moves = {8, 16, 32};
        for (auto move : moves) {
            uint64_t pawnAttacks = (((move << 7) & Bitboard::notAfile_bb) |
                                    ((move << 9) & Bitboard::notHfile_bb));
            if (pawnAttacks & position.black_bb & position.pawn_bb) {
                castleFailed = true;
                break;
            }
            uint64_t knightAttacks = (((move <<  6) & Bitboard::notABfile_bb) |
                                      ((move << 10) & Bitboard::notGHfile_bb) | 
                                      ((move << 15) & Bitboard::notAfile_bb ) | 
                                      ((move << 17) & Bitboard::notHfile_bb ));  
            if (knightAttacks & position.black_bb & position.knight_bb) {
                castleFailed = true;
                break;
            }

            uint64_t kingAttacks = (((move << 1) & Bitboard::notHfile_bb) |
                                    ((move << 7) & Bitboard::notAfile_bb) |
                                    ((move << 8)                        ) |
                                    ((move << 9) & Bitboard::notHfile_bb) |
                                    ((move >> 1) & Bitboard::notAfile_bb)); 
            if (kingAttacks & position.black_bb & position.king_bb) {
                castleFailed = true;
                break;
            }


            uint64_t empty = ~position.pieces_bb;
            uint64_t scan = move;
            uint64_t flood = move;
            
            scan = move;
            flood = move;
            empty = ~position.pieces_bb & Bitboard::notHfile_bb;
            flood |= scan = (scan << 9) & empty; // northwest
            flood |= scan = (scan << 9) & empty;
            flood |= scan = (scan << 9) & empty;
            flood |= scan = (scan << 9) & empty;
            flood |= scan = (scan << 9) & empty;
            flood |=        (scan << 9) & empty; 
            uint64_t diagAttacks = (flood << 9) & Bitboard::notHfile_bb; // might later change to not include captures
            
            scan = move;
            flood = move;
            empty = ~position.pieces_bb & Bitboard::notAfile_bb;
            flood |= scan = (scan << 7) & empty; // northeast
            flood |= scan = (scan << 7) & empty;
            flood |= scan = (scan << 7) & empty;
            flood |= scan = (scan << 7) & empty;
            flood |= scan = (scan << 7) & empty;
            flood |=        (scan << 7) & empty; 
            diagAttacks |= (flood << 7) & Bitboard::notAfile_bb; // might later change to not include captures
            
            if (diagAttacks & position.black_bb & (position.queen_bb | position.bishop_bb)) {
                castleFailed = true;
                break;
            }

            empty = ~position.pieces_bb;
            scan = move;
            flood = move;

            flood |= scan = (scan << 8) & empty; // north
            flood |= scan = (scan << 8) & empty;
            flood |= scan = (scan << 8) & empty;
            flood |= scan = (scan << 8) & empty;
            flood |= scan = (scan << 8) & empty;
            flood |=        (scan << 8) & empty; 
            uint64_t rookAttacks = flood << 8; // might later change to not include captures

            if (rookAttacks & position.black_bb & (position.queen_bb | position.rook_bb)) {
                castleFailed = true;
                break;
            }
        }
        if (!castleFailed) {
            castleMoves |= 32;
        }
    }
    if ((!whitesTurn && (position.castlingRights & 0x04)) && // Black Kingside castle
    ((~position.pieces_bb & 0x0600000000000000) == 0x0600000000000000)) {
        bool castleFailed = false;
        std::vector<uint64_t> moves = {(uint64_t(2) << 56), (uint64_t(4) << 56), (uint64_t(8) << 56)};
        for (auto move : moves) {
            uint64_t pawnAttacks = (((move >> 7) & Bitboard::notHfile_bb) |
                                    ((move >> 9) & Bitboard::notAfile_bb));
            if (pawnAttacks & position.white_bb & position.pawn_bb) {
                castleFailed = true;
                break;
            }
            uint64_t knightAttacks = (((move >>  6) & Bitboard::notGHfile_bb) |
                                      ((move >> 10) & Bitboard::notABfile_bb) | 
                                      ((move >> 15) & Bitboard::notHfile_bb ) | 
                                      ((move >> 17) & Bitboard::notAfile_bb ));  
            if (knightAttacks & position.white_bb & position.knight_bb) {
                castleFailed = true;
                break;
            }

            uint64_t kingAttacks = (((move >> 1) & Bitboard::notAfile_bb) |
                                    ((move >> 7) & Bitboard::notHfile_bb) |
                                    ((move >> 8)                        ) |
                                    ((move >> 9) & Bitboard::notAfile_bb) |
                                    ((move << 1) & Bitboard::notHfile_bb)); 
            if (kingAttacks & position.white_bb & position.king_bb) {
                castleFailed = true;
                break;
            }


            uint64_t empty = ~position.pieces_bb;
            uint64_t scan = move;
            uint64_t flood = move;
            
            scan = move;
            flood = move;
            empty = ~position.pieces_bb & Bitboard::notAfile_bb;
            flood |= scan = (scan >> 9) & empty; // southeast
            flood |= scan = (scan >> 9) & empty;
            flood |= scan = (scan >> 9) & empty;
            flood |= scan = (scan >> 9) & empty;
            flood |= scan = (scan >> 9) & empty;
            flood |=        (scan >> 9) & empty; 
            uint64_t diagAttacks = (flood >> 9) & Bitboard::notAfile_bb; // might later change to not include captures
            
            scan = move;
            flood = move;
            empty = ~position.pieces_bb & Bitboard::notHfile_bb;
            flood |= scan = (scan >> 7) & empty; // southwest
            flood |= scan = (scan >> 7) & empty;
            flood |= scan = (scan >> 7) & empty;
            flood |= scan = (scan >> 7) & empty;
            flood |= scan = (scan >> 7) & empty;
            flood |=        (scan >> 7) & empty; 
            diagAttacks |= (flood >> 7) & Bitboard::notHfile_bb; // might later change to not include captures
            
            if (diagAttacks & position.white_bb & (position.queen_bb | position.bishop_bb)) {
                castleFailed = true;
                break;
            }

            empty = ~position.pieces_bb;
            scan = move;
            flood = move;

            flood |= scan = (scan >> 8) & empty; // south
            flood |= scan = (scan >> 8) & empty;
            flood |= scan = (scan >> 8) & empty;
            flood |= scan = (scan >> 8) & empty;
            flood |= scan = (scan >> 8) & empty;
            flood |=        (scan >> 8) & empty; 
            uint64_t rookAttacks = flood >> 8; // might later change to not include captures

            if (rookAttacks & position.white_bb & (position.queen_bb | position.rook_bb)) {
                castleFailed = true;
                break;
            }
        }
        if (!castleFailed) {
            castleMoves |= (uint64_t(2) << 56);
        }
    }
    if ((!whitesTurn && (position.castlingRights & 0x08)) && // Black Queenside castle
    ((~position.pieces_bb & 0x7000000000000000) == 0x7000000000000000)) {
        bool castleFailed = false;
        std::vector<uint64_t> moves = {(uint64_t(8) << 56), (uint64_t(16) << 56), (uint64_t(32) << 56)};
        for (auto move : moves) {
            uint64_t pawnAttacks = (((move >> 7) & Bitboard::notHfile_bb) |
                                    ((move >> 9) & Bitboard::notAfile_bb));
            if (pawnAttacks & position.white_bb & position.pawn_bb) {
                castleFailed = true;
                break;
            }
            uint64_t knightAttacks = (((move >>  6) & Bitboard::notGHfile_bb) |
                                      ((move >> 10) & Bitboard::notABfile_bb) | 
                                      ((move >> 15) & Bitboard::notHfile_bb ) | 
                                      ((move >> 17) & Bitboard::notAfile_bb ));  
            if (knightAttacks & position.white_bb & position.knight_bb) {
                castleFailed = true;
                break;
            }

            uint64_t kingAttacks = (((move >> 1) & Bitboard::notAfile_bb) |
                                    ((move >> 7) & Bitboard::notHfile_bb) |
                                    ((move >> 8)                        ) |
                                    ((move >> 9) & Bitboard::notAfile_bb) |
                                    ((move << 1) & Bitboard::notHfile_bb)); 
            if (kingAttacks & position.white_bb & position.king_bb) {
                castleFailed = true;
                break;
            }


            uint64_t empty = ~position.pieces_bb;
            uint64_t scan = move;
            uint64_t flood = move;
            
            scan = move;
            flood = move;
            empty = ~position.pieces_bb & Bitboard::notAfile_bb;
            flood |= scan = (scan >> 9) & empty; // southeast
            flood |= scan = (scan >> 9) & empty;
            flood |= scan = (scan >> 9) & empty;
            flood |= scan = (scan >> 9) & empty;
            flood |= scan = (scan >> 9) & empty;
            flood |=        (scan >> 9) & empty; 
            uint64_t diagAttacks = (flood >> 9) & Bitboard::notAfile_bb; // might later change to not include captures
            
            scan = move;
            flood = move;
            empty = ~position.pieces_bb & Bitboard::notHfile_bb;
            flood |= scan = (scan >> 7) & empty; // southwest
            flood |= scan = (scan >> 7) & empty;
            flood |= scan = (scan >> 7) & empty;
            flood |= scan = (scan >> 7) & empty;
            flood |= scan = (scan >> 7) & empty;
            flood |=        (scan >> 7) & empty; 
            diagAttacks |= (flood >> 7) & Bitboard::notHfile_bb; // might later change to not include captures
            
            if (diagAttacks & position.white_bb & (position.queen_bb | position.bishop_bb)) {
                castleFailed = true;
                break;
            }

            empty = ~position.pieces_bb;
            scan = move;
            flood = move;

            flood |= scan = (scan >> 8) & empty; // south
            flood |= scan = (scan >> 8) & empty;
            flood |= scan = (scan >> 8) & empty;
            flood |= scan = (scan >> 8) & empty;
            flood |= scan = (scan >> 8) & empty;
            flood |=        (scan >> 8) & empty; 
            uint64_t rookAttacks = flood >> 8; // might later change to not include captures

            if (rookAttacks & position.white_bb & (position.queen_bb | position.rook_bb)) {
                castleFailed = true;
                break;
            }
        }
        if (!castleFailed) {
            castleMoves |= (uint64_t(32) << 56);
        }
    }
    return castleMoves;
}
