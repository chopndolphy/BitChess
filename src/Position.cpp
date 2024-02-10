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
    enPassantable_bb  = 0;
    castlingRights = 0x0F;
    fiftyMoveCounter = 0;
    initZobristHashing();
}
uint64_t Position::GetCaptures(uint64_t piece, bool whitesTurn) {
    if ((!whitesTurn && (white_bb & piece)) || (whitesTurn && (black_bb & piece))) {
        return 0;
    }
    uint64_t pseudoCaps = 0;
    
    if (whitesTurn && (pawn_bb & piece)) {
        pseudoCaps = (((piece << 7) & Bitboard::notAfile_bb) |
                      ((piece << 9) & Bitboard::notHfile_bb));
        pseudoCaps &= black_bb;
        if (((piece << 1) & Bitboard::notHfile_bb) & (enPassantable_bb & black_bb)) {
            pseudoCaps |= piece << 9;
        }
        if (((piece >> 1) & Bitboard::notAfile_bb) & (enPassantable_bb & black_bb)) {
            pseudoCaps |= piece << 7;
        }
    } else if (!whitesTurn && (pawn_bb & piece)) {
        pseudoCaps = (((piece >> 7) & Bitboard::notHfile_bb) |
                      ((piece >> 9) & Bitboard::notAfile_bb));
        pseudoCaps &= white_bb;
        if (((piece << 1) & Bitboard::notHfile_bb) & (enPassantable_bb & white_bb)) {
            pseudoCaps |= piece >> 7;
        }
        if (((piece >> 1) & Bitboard::notAfile_bb) & (enPassantable_bb & white_bb)) {
            pseudoCaps |= piece >> 9;
        }
    } else if ((knight_bb & piece) || (king_bb & piece) || (bishop_bb & piece) || (rook_bb & piece) || (queen_bb & piece)) {
        pseudoCaps = GetQuietMoves(piece, whitesTurn); //this function isnt totally true to it's name for the purpose
                                                       //of not reusing code here. might change.
        if (whitesTurn) {
            pseudoCaps &= black_bb;
        } else {
            pseudoCaps &= white_bb;
        }
    }
    return Bitboard::RemoveIllegalMoves(piece, pseudoCaps, *this);
}
uint64_t Position::GetPromotionSquare(uint64_t piece, bool whitesTurn) {
    uint64_t moves = 0;
    if (whitesTurn && (pawn_bb & piece & (Bitboard::horiLine_bb << 48))) {
        moves = (((piece << 7) & Bitboard::notAfile_bb) |
                 ((piece << 9) & Bitboard::notHfile_bb));
        moves &= black_bb;
        moves |= ((piece << 8) & ~pieces_bb);
    } else if (!whitesTurn && (pawn_bb & piece & (Bitboard::horiLine_bb << 8) )) {
        moves = (((piece >> 7) & Bitboard::notHfile_bb) |
                 ((piece >> 9) & Bitboard::notAfile_bb));
        moves &= white_bb;
        moves |= ((piece >> 8) & ~pieces_bb);
    }
    return Bitboard::RemoveIllegalMoves(piece, moves, *this);
}
uint64_t Position::GetPromotionOptions(uint64_t promotionSquare, bool whitesTurn) {
    uint64_t options = 0;
    if (whitesTurn) {
        options = ((promotionSquare      ) |
                   (promotionSquare >>  8) |
                   (promotionSquare >> 16) |
                   (promotionSquare >> 24)); 
    } else {
        options = ((promotionSquare      ) |
                   (promotionSquare <<  8) |
                   (promotionSquare <<  8) |
                   (promotionSquare << 16));
    }
    return options;
}
uint64_t Position::GetQuietMoves(uint64_t piece, bool whitesTurn) {
    if ((!whitesTurn && (white_bb & piece)) || (whitesTurn && (black_bb & piece))) {
        return 0;
    }
    uint64_t moves = 0;

    if (whitesTurn && (pawn_bb & piece)) {
        moves |= piece << 8;
        if ((piece & (Bitboard::horiLine_bb << 8)) && ((piece << 8) & ~pieces_bb)) { // pawn is at start square and can move two
            moves |= piece << 16;
        }
        moves &= ~pieces_bb;
    } else if (!whitesTurn && (pawn_bb & piece)) {
        moves |= piece >> 8;
        if ((piece & (Bitboard::horiLine_bb << 48)) && ((piece >> 8) & ~pieces_bb)) { // pawn is at start square and can move two
            moves |= piece >> 16;
        }
        moves &= ~pieces_bb;
    } else if (knight_bb & piece) {
        moves = (((piece <<  6) & Bitboard::notABfile_bb) |
                 ((piece << 10) & Bitboard::notGHfile_bb) | 
                 ((piece << 15) & Bitboard::notAfile_bb ) | 
                 ((piece << 17) & Bitboard::notHfile_bb ) | 
                 ((piece >>  6) & Bitboard::notGHfile_bb) |
                 ((piece >> 10) & Bitboard::notABfile_bb) |
                 ((piece >> 15) & Bitboard::notHfile_bb ) |
                 ((piece >> 17) & Bitboard::notAfile_bb ));
        moves &= (whitesTurn) ? ~white_bb : ~black_bb; // might later change to not include captures
    } else if (king_bb & piece) {
        moves = (((piece << 1) & Bitboard::notHfile_bb) |
                 ((piece << 7) & Bitboard::notAfile_bb) |
                 ((piece << 8)                        ) |
                 ((piece << 9) & Bitboard::notHfile_bb) |
                 ((piece >> 1) & Bitboard::notAfile_bb) |
                 ((piece >> 7) & Bitboard::notHfile_bb) |
                 ((piece >> 8)                        ) |
                 ((piece >> 9) & Bitboard::notAfile_bb));
        moves &= (whitesTurn) ? ~white_bb : ~black_bb; // might later change to not include captures
        moves |= Bitboard::GenerateCastleMoves(whitesTurn, *this);
    } else if (bishop_bb & piece) {
        uint64_t empty = ~pieces_bb;
        uint64_t scan = piece;
        uint64_t flood = piece;
        
        scan = piece;
        flood = piece;
        empty = ~pieces_bb & Bitboard::notHfile_bb;
        flood |= scan = (scan << 9) & empty; // northwest
        flood |= scan = (scan << 9) & empty;
        flood |= scan = (scan << 9) & empty;
        flood |= scan = (scan << 9) & empty;
        flood |= scan = (scan << 9) & empty;
        flood |=        (scan << 9) & empty; 
        moves |= (flood << 9) & Bitboard::notHfile_bb; // might later change to not include captures
        
        scan = piece;
        flood = piece;
        empty = ~pieces_bb & Bitboard::notAfile_bb;
        flood |= scan = (scan >> 9) & empty; // southeast
        flood |= scan = (scan >> 9) & empty;
        flood |= scan = (scan >> 9) & empty;
        flood |= scan = (scan >> 9) & empty;
        flood |= scan = (scan >> 9) & empty;
        flood |=        (scan >> 9) & empty; 
        moves |= (flood >> 9) & Bitboard::notAfile_bb; // might later change to not include captures


        scan = piece;
        flood = piece;
        empty = ~pieces_bb & Bitboard::notAfile_bb;
        flood |= scan = (scan << 7) & empty; // northeast
        flood |= scan = (scan << 7) & empty;
        flood |= scan = (scan << 7) & empty;
        flood |= scan = (scan << 7) & empty;
        flood |= scan = (scan << 7) & empty;
        flood |=        (scan << 7) & empty; 
        moves |= (flood << 7) & Bitboard::notAfile_bb; // might later change to not include captures
        
        scan = piece;
        flood = piece;
        empty = ~pieces_bb & Bitboard::notHfile_bb;
        flood |= scan = (scan >> 7) & empty; // southwest
        flood |= scan = (scan >> 7) & empty;
        flood |= scan = (scan >> 7) & empty;
        flood |= scan = (scan >> 7) & empty;
        flood |= scan = (scan >> 7) & empty;
        flood |=        (scan >> 7) & empty; 
        moves |= (flood >> 7) & Bitboard::notHfile_bb; // might later change to not include captures

        moves &= (whitesTurn) ? ~white_bb : ~black_bb; // might later change to not include captures
    } else if (rook_bb & piece) {
        uint64_t empty = ~pieces_bb;
        uint64_t scan = piece;
        uint64_t flood = piece;

        flood |= scan = (scan << 8) & empty; // north
        flood |= scan = (scan << 8) & empty;
        flood |= scan = (scan << 8) & empty;
        flood |= scan = (scan << 8) & empty;
        flood |= scan = (scan << 8) & empty;
        flood |=        (scan << 8) & empty; 
        moves |= flood << 8; // might later change to not include captures

        scan = piece;
        flood = piece;
        flood |= scan = (scan >> 8) & empty; // south
        flood |= scan = (scan >> 8) & empty;
        flood |= scan = (scan >> 8) & empty;
        flood |= scan = (scan >> 8) & empty;
        flood |= scan = (scan >> 8) & empty;
        flood |=        (scan >> 8) & empty; 
        moves |= flood >> 8; // might later change to not include captures

        scan = piece;
        flood = piece;
        empty = ~pieces_bb & Bitboard::notHfile_bb;
        flood |= scan = (scan << 1) & empty; // west
        flood |= scan = (scan << 1) & empty;
        flood |= scan = (scan << 1) & empty;
        flood |= scan = (scan << 1) & empty;
        flood |= scan = (scan << 1) & empty;
        flood |=        (scan << 1) & empty; 
        moves |= (flood << 1) & Bitboard::notHfile_bb; // might later change to not include captures
        
        scan = piece;
        flood = piece;
        empty = ~pieces_bb & Bitboard::notAfile_bb;
        flood |= scan = (scan >> 1) & empty; // east
        flood |= scan = (scan >> 1) & empty;
        flood |= scan = (scan >> 1) & empty;
        flood |= scan = (scan >> 1) & empty;
        flood |= scan = (scan >> 1) & empty;
        flood |=        (scan >> 1) & empty; 
        moves |= (flood >> 1) & Bitboard::notAfile_bb; // might later change to not include captures

        moves &= (whitesTurn) ? ~white_bb : ~black_bb; // might later change to not include captures
    } else if (queen_bb & piece) {
        uint64_t empty = ~pieces_bb;
        uint64_t scan = piece;
        uint64_t flood = piece;

        flood |= scan = (scan << 8) & empty; // north
        flood |= scan = (scan << 8) & empty;
        flood |= scan = (scan << 8) & empty;
        flood |= scan = (scan << 8) & empty;
        flood |= scan = (scan << 8) & empty;
        flood |=        (scan << 8) & empty; 
        moves |= flood << 8; // might later change to not include captures

        scan = piece;
        flood = piece;
        flood |= scan = (scan >> 8) & empty; // south
        flood |= scan = (scan >> 8) & empty;
        flood |= scan = (scan >> 8) & empty;
        flood |= scan = (scan >> 8) & empty;
        flood |= scan = (scan >> 8) & empty;
        flood |=        (scan >> 8) & empty; 
        moves |= flood >> 8; // might later change to not include captures

        scan = piece;
        flood = piece;
        empty = ~pieces_bb & Bitboard::notHfile_bb;
        flood |= scan = (scan << 1) & empty; // west
        flood |= scan = (scan << 1) & empty;
        flood |= scan = (scan << 1) & empty;
        flood |= scan = (scan << 1) & empty;
        flood |= scan = (scan << 1) & empty;
        flood |=        (scan << 1) & empty; 
        moves |= (flood << 1) & Bitboard::notHfile_bb; // might later change to not include captures
        
        scan = piece;
        flood = piece;
        empty = ~pieces_bb & Bitboard::notAfile_bb;
        flood |= scan = (scan >> 1) & empty; // east
        flood |= scan = (scan >> 1) & empty;
        flood |= scan = (scan >> 1) & empty;
        flood |= scan = (scan >> 1) & empty;
        flood |= scan = (scan >> 1) & empty;
        flood |=        (scan >> 1) & empty; 
        moves |= (flood >> 1) & Bitboard::notAfile_bb; // might later change to not include captures

        scan = piece;
        flood = piece;
        empty = ~pieces_bb & Bitboard::notHfile_bb;
        flood |= scan = (scan << 9) & empty; // northwest
        flood |= scan = (scan << 9) & empty;
        flood |= scan = (scan << 9) & empty;
        flood |= scan = (scan << 9) & empty;
        flood |= scan = (scan << 9) & empty;
        flood |=        (scan << 9) & empty; 
        moves |= (flood << 9) & Bitboard::notHfile_bb; // might later change to not include captures
        
        scan = piece;
        flood = piece;
        empty = ~pieces_bb & Bitboard::notAfile_bb;
        flood |= scan = (scan >> 9) & empty; // southeast
        flood |= scan = (scan >> 9) & empty;
        flood |= scan = (scan >> 9) & empty;
        flood |= scan = (scan >> 9) & empty;
        flood |= scan = (scan >> 9) & empty;
        flood |=        (scan >> 9) & empty; 
        moves |= (flood >> 9) & Bitboard::notAfile_bb; // might later change to not include captures


        scan = piece;
        flood = piece;
        empty = ~pieces_bb & Bitboard::notAfile_bb;
        flood |= scan = (scan << 7) & empty; // northeast
        flood |= scan = (scan << 7) & empty;
        flood |= scan = (scan << 7) & empty;
        flood |= scan = (scan << 7) & empty;
        flood |= scan = (scan << 7) & empty;
        flood |=        (scan << 7) & empty; 
        moves |= (flood << 7) & Bitboard::notAfile_bb; // might later change to not include captures
        
        scan = piece;
        flood = piece;
        empty = ~pieces_bb & Bitboard::notHfile_bb;
        flood |= scan = (scan >> 7) & empty; // southwest
        flood |= scan = (scan >> 7) & empty;
        flood |= scan = (scan >> 7) & empty;
        flood |= scan = (scan >> 7) & empty;
        flood |= scan = (scan >> 7) & empty;
        flood |=        (scan >> 7) & empty; 
        moves |= (flood >> 7) & Bitboard::notHfile_bb; // might later change to not include captures

        moves &= (whitesTurn) ? ~white_bb : ~black_bb; // might later change to not include captures
    }

    return Bitboard::RemoveIllegalMoves(piece, moves, *this);
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
bool Position::CheckForNoMoves(bool whitesTurn) {
    uint64_t myPieces = 0;
    if (whitesTurn) {
        myPieces = white_bb;
    } else {
        myPieces = black_bb;
    }
    uint64_t biterator = 0x8000000000000000;
    std::vector<uint64_t> moves;
    for (size_t i = 0; i < 64; i++) {
        if (biterator & myPieces) {
            moves.push_back(biterator);
        }
        biterator >>= 1;
    }
    for (auto move : moves) {
        if (GetQuietMoves(move, whitesTurn)) {
            return false;
        } else if (GetCaptures(move, whitesTurn)) {
            return false;
        }
    }
    return true;
}
bool Position::CheckForRepetition(bool whitesTurn)
{
    uint64_t currentHash = HashPosition(whitesTurn);
    if (whitesTurn) {
        auto const& result = whiteRepetitionLookup.insert({currentHash, false});
        if (result.second == false) {
            if (!result.first->second) {
                whiteRepetitionLookup.at(currentHash) = true;
                return false; // Position was repeated twice
            } else {
                return true; // Threefold repetition
            }
        } else {
            return false; // Position was not repeated
        }
    } else {
        auto const& result = blackRepetitionLookup.insert({currentHash, false});
        if (result.second == false) {
            if (!result.first->second) {
                blackRepetitionLookup.at(currentHash) = true;
                return false; // Position was repeated twice
            } else {
                return true; // Threefold repetition
            }
        } else {
            return false; // Position was not repeated
        }
    }
}
bool Position::CheckForDeadPosition() {
    if (pawn_bb != 0) return false;
    if (rook_bb != 0) return false;
    if (queen_bb != 0) return false;
    if ((knight_bb & white_bb) && (knight_bb & black_bb)) return false;
    if ((knight_bb & white_bb) && (knight_bb & black_bb) == 0 && (bishop_bb & black_bb) == 0) {
        uint64_t biterator = 0x8000000000000000;
        int count = 0;
        for (size_t i = 0; i < 64; i++) {
            if (biterator & (knight_bb & white_bb)) {
                count++;
                if (count >= 2) return false;
            }
            biterator >>= 1;
        }
    }
    if ((knight_bb & black_bb) && (knight_bb & white_bb) == 0 && (bishop_bb & white_bb) == 0) {
        uint64_t biterator = 0x8000000000000000;
        int count = 0;
        for (size_t i = 0; i < 64; i++) {
            if (biterator & (knight_bb & black_bb)) {
                count++;
                if (count >= 2) return false;
            }
        }
    }
    if ((bishop_bb & white_bb) && (knight_bb & black_bb) == 0 && (bishop_bb & black_bb) == 0) {
        uint64_t biterator = 0x8000000000000000;
        int count = 0;
        for (size_t i = 0; i < 64; i++) {
            if (biterator & (bishop_bb & white_bb)) {
                count++;
                if (count >= 2) return false;
            }
            biterator >>= 1;
        }
    }
    if ((bishop_bb & black_bb) && (knight_bb & white_bb) == 0 && (bishop_bb & white_bb) == 0) {
        uint64_t biterator = 0x8000000000000000;
        int count = 0;
        for (size_t i = 0; i < 64; i++) {
            if (biterator & (bishop_bb & black_bb)) {
                count++;
                if (count >= 2) return false;
            }
            biterator >>= 1;
        }
    }
    if ((bishop_bb & black_bb) && (knight_bb & black_bb) == 0 && (bishop_bb & white_bb) && (knight_bb & white_bb) == 0) {
        uint64_t biterator = 0x8000000000000000;
        int count = 0;
        bool whiteIsWhite;
        for (size_t i = 0; i < 64; i++) {
            if (biterator & (bishop_bb & white_bb)) {
                count++;
                if (count >= 2) return false;
                size_t square = i % 8;
                if (square % 2 == 0) {
                    whiteIsWhite = true;
                } else {
                    whiteIsWhite = false;
                }
            }
            biterator >>= 1;
        }
        biterator = 0x8000000000000000;
        count = 0;
        bool blackIsWhite;
        for (size_t i = 0; i < 64; i++) {
            if (biterator & (bishop_bb & black_bb)) {
                count++;
                if (count >= 2) return false;
                size_t square = i % 8;
                if (square % 2 == 0) {
                    blackIsWhite = true;
                } else {
                    blackIsWhite = false;
                }
            }
            biterator >>= 1;
        }
        if (whiteIsWhite != blackIsWhite) {
            return false;
        }
    }
    return true;
}
uint64_t Position::HashPosition(bool whitesTurn)
{
    uint64_t biterator = 0x8000000000000000;
    uint64_t hash = 0;
    if (whitesTurn) hash ^= hashKey.WhitesTurn;
    if (8 & castlingRights) hash ^= hashKey.CastleBQ;
    if (4 & castlingRights) hash ^= hashKey.CastleBK;
    if (2 & castlingRights) hash ^= hashKey.CastleWQ;
    if (1 & castlingRights) hash ^= hashKey.CastleWK;
    for (size_t i = 0; i < 64; i++) {
        if (biterator & (pawn_bb & white_bb)) hash ^= hashKey.SquaresPieces[i][Pawn_w];
        if (biterator & (pawn_bb & black_bb)) hash ^= hashKey.SquaresPieces[i][Pawn_b];
        if (biterator & (knight_bb & white_bb)) hash ^= hashKey.SquaresPieces[i][Knight_w];
        if (biterator & (knight_bb & black_bb)) hash ^= hashKey.SquaresPieces[i][Knight_b];
        if (biterator & (bishop_bb & white_bb)) hash ^= hashKey.SquaresPieces[i][Bishop_w];
        if (biterator & (bishop_bb & black_bb)) hash ^= hashKey.SquaresPieces[i][Bishop_b];
        if (biterator & (rook_bb & white_bb)) hash ^= hashKey.SquaresPieces[i][Rook_w];
        if (biterator & (rook_bb & black_bb)) hash ^= hashKey.SquaresPieces[i][Rook_b];
        if (biterator & (queen_bb & white_bb)) hash ^= hashKey.SquaresPieces[i][Queen_w];
        if (biterator & (queen_bb & black_bb)) hash ^= hashKey.SquaresPieces[i][Queen_b];
        if (biterator & (king_bb & white_bb)) hash ^= hashKey.SquaresPieces[i][King_w];
        if (biterator & (king_bb & black_bb)) hash ^= hashKey.SquaresPieces[i][King_b];
        if (biterator & (enPassantable_bb & white_bb)) hash ^= hashKey.SquaresPieces[i][EnPassant_w];
        if (biterator & (enPassantable_bb & black_bb)) hash ^= hashKey.SquaresPieces[i][EnPassant_b];
        biterator >>= 1;
    }
    return hash;
}
void Position::initZobristHashing() {
    std::random_device rd;
    std::mt19937_64 e2(rd());
    std::uniform_int_distribution<long long int> dist(std::llround(std::pow(2, 61)), std::llround(std::pow(2, 62)));

    for (size_t i = 0; i < 64; i++) {
        for (size_t j = 0; j < 14; j++) {
            hashKey.SquaresPieces[i][j] = dist(e2);
        }
    }
    hashKey.WhitesTurn = dist(e2);
    hashKey.CastleBQ = dist(e2);
    hashKey.CastleBK = dist(e2);
    hashKey.CastleWQ = dist(e2);
    hashKey.CastleWK = dist(e2);
}
void Position::MakeMove(uint64_t from, uint64_t to, bool whitesTurn) {
    uint64_t fromTo = from | to;

    if (whitesTurn && (pawn_bb & from) && ((to >> 8) & (enPassantable_bb & black_bb))) { // en passant taken
        enPassantable_bb ^= to >> 8;
        pawn_bb ^= (fromTo | (to >> 8));
        black_bb ^= to >> 8;
        white_bb ^= fromTo;
        pieces_bb = (white_bb | black_bb);
        whiteRepetitionLookup.clear();
        blackRepetitionLookup.clear();
        fiftyMoveCounter = 0;
        return;
    } else if (!whitesTurn && (pawn_bb & from) && ((to << 8) & (enPassantable_bb & white_bb))) {
        enPassantable_bb ^= to << 8;
        pawn_bb ^= (fromTo | (to << 8));
        white_bb ^= to << 8;
        black_bb ^= fromTo;
        pieces_bb = (white_bb | black_bb);
        whiteRepetitionLookup.clear();
        blackRepetitionLookup.clear();
        fiftyMoveCounter = 0;
        return;
    }

    if (enPassantable_bb) { // En Passant not taken
        whiteRepetitionLookup.clear();
        blackRepetitionLookup.clear();
    }
    if (whitesTurn) {
        enPassantable_bb ^= (black_bb & enPassantable_bb);
    } else {
        enPassantable_bb ^= (white_bb & enPassantable_bb);
    }

    if (to & uint64_t(2) && (castlingRights & 0x01) && (from & king_bb & white_bb)) { // White Kingside Castle
        castlingRights = (castlingRights & 0x0C); // Set both whites castle rights to 0, without affecting blacks
        uint64_t rookFromTo = 0x0000000000000005;
        white_bb ^= rookFromTo | fromTo;
        pieces_bb ^= rookFromTo | fromTo;
        king_bb ^= fromTo; 
        rook_bb ^= rookFromTo;
        whiteRepetitionLookup.clear();
        blackRepetitionLookup.clear();
        return;
    } else if (to & uint64_t(32) && (castlingRights & 0x02) && (from & king_bb & white_bb)) { // White Queenside Castle
        castlingRights = (castlingRights & 0x0C); // Set both whites castle rights to 0, without affecting blacks
        uint64_t rookFromTo = 0x0000000000000090;
        white_bb ^= rookFromTo | fromTo;
        pieces_bb ^= rookFromTo | fromTo;
        king_bb ^= fromTo; 
        rook_bb ^= rookFromTo;
        whiteRepetitionLookup.clear();
        blackRepetitionLookup.clear();
        return;
    } else if (to & (uint64_t(2) << 56) && (castlingRights & 0x04) && (from & king_bb & black_bb)) { // Black Kingside Castle 
        castlingRights = (castlingRights & 0x03); // Set both blacks castle rights to 0, without affecting whites
        uint64_t rookFromTo = 0x0500000000000000;
        black_bb ^= rookFromTo | fromTo;
        pieces_bb ^= rookFromTo | fromTo;
        king_bb ^= fromTo; 
        rook_bb ^= rookFromTo;
        whiteRepetitionLookup.clear();
        blackRepetitionLookup.clear();
        return;
    } else if (to & (uint64_t(32) << 56) && (castlingRights & 0x08) && (from & king_bb & black_bb)) { // Black Queenside Castle
        castlingRights = (castlingRights & 0x03); // Set both blacks castle rights to 0, without affecting whites
        uint64_t rookFromTo = 0x9000000000000000;
        black_bb ^= rookFromTo | fromTo;
        pieces_bb ^= rookFromTo | fromTo;
        king_bb ^= fromTo; 
        rook_bb ^= rookFromTo;
        whiteRepetitionLookup.clear();
        blackRepetitionLookup.clear();
        return;
    }
    if (whitesTurn && (from & uint64_t(1) & rook_bb)) {
        castlingRights &= 0x0E;
        whiteRepetitionLookup.clear();
        blackRepetitionLookup.clear();
    } else if (whitesTurn && (from & 128 & rook_bb)) {
        castlingRights &= 0x0D;
        whiteRepetitionLookup.clear();
        blackRepetitionLookup.clear();
    } else if (!whitesTurn && (from & (uint64_t(1) << 56) & rook_bb)) {
        castlingRights &= 0x0B;
        whiteRepetitionLookup.clear();
        blackRepetitionLookup.clear();
    } else if (!whitesTurn && (from & (uint64_t(128) << 56) & rook_bb)) {
        castlingRights &= 0x07;
        whiteRepetitionLookup.clear();
        blackRepetitionLookup.clear();
    } else if (whitesTurn && (from & white_bb & king_bb)) {
        castlingRights &= 0x0C;
        whiteRepetitionLookup.clear();
        blackRepetitionLookup.clear();
    } else if (!whitesTurn && (from & black_bb & king_bb)) {
        castlingRights &= 0x03;
        whiteRepetitionLookup.clear();
        blackRepetitionLookup.clear();
    }
    if (whitesTurn && (to & black_bb)) { // white capturing
        black_bb ^= to;
        if (pawn_bb & to) pawn_bb ^= to;
        if (knight_bb & to) knight_bb ^= to;
        if (bishop_bb & to) bishop_bb ^= to;
        if (rook_bb & to) rook_bb ^= to;
        if (queen_bb & to) queen_bb ^= to;
        if (king_bb & to) king_bb ^= to;
        whiteRepetitionLookup.clear();
        blackRepetitionLookup.clear();
        fiftyMoveCounter = 0;
    } else if (!whitesTurn && (to & white_bb)) { // black capturing
        white_bb ^= to;
        if (pawn_bb & to) pawn_bb ^= to;
        if (knight_bb & to) knight_bb ^= to;
        if (bishop_bb & to) bishop_bb ^= to;
        if (rook_bb & to) rook_bb ^= to;
        if (queen_bb & to) queen_bb ^= to;
        if (king_bb & to) king_bb ^= to;
        whiteRepetitionLookup.clear();
        blackRepetitionLookup.clear();
        fiftyMoveCounter = 0;
    } else {
        fiftyMoveCounter++;
    }
    if (whitesTurn) {
        white_bb ^= fromTo;
    } else {
        black_bb ^= fromTo;
    }
    if (pawn_bb & from) {
        pawn_bb ^= fromTo;
        if (((from & (Bitboard::horiLine_bb << 8)) && (to & (from << 16))) ||
        ((from & (Bitboard::horiLine_bb << 48) && (to & (from >> 16))))) {
            enPassantable_bb ^= to;
            whiteRepetitionLookup.clear();
            blackRepetitionLookup.clear();
            fiftyMoveCounter = 0;
        }
    }
    if (knight_bb & from) knight_bb ^= fromTo;
    if (bishop_bb & from) bishop_bb ^= fromTo;
    if (rook_bb & from) rook_bb ^= fromTo;
    if (queen_bb & from) queen_bb ^= fromTo;
    if (king_bb & from) king_bb ^= fromTo;
    pieces_bb = (white_bb | black_bb);
}

void Position::PromotePawn(uint64_t from, uint64_t to, uint64_t selectionSquare, bool whitesTurn) {
    uint64_t fromTo = from | to;
    if (whitesTurn) {
        if (to & black_bb) {
            black_bb ^= to;
            if (pawn_bb & to) pawn_bb ^= to;
            if (knight_bb & to) knight_bb ^= to;
            if (bishop_bb & to) bishop_bb ^= to;
            if (rook_bb & to) rook_bb ^= to;
            if (queen_bb & to) queen_bb ^= to;
            if (king_bb & to) king_bb ^= to;
        }
        if (selectionSquare & to) {
            queen_bb ^= to;    
        } else if (selectionSquare & (to >>  8)) {
            rook_bb ^= to;
        } else if (selectionSquare & (to >> 16)) {
            bishop_bb ^= to;
        } else if (selectionSquare & (to >> 24)) {
            knight_bb ^= to;
        }
        white_bb ^= fromTo;
    } else {
        if (to & white_bb) {
            white_bb ^= to;
            if (pawn_bb & to) pawn_bb ^= to;
            if (knight_bb & to) knight_bb ^= to;
            if (bishop_bb & to) bishop_bb ^= to;
            if (rook_bb & to) rook_bb ^= to;
            if (queen_bb & to) queen_bb ^= to;
            if (king_bb & to) king_bb ^= to;
        }
        if (selectionSquare & to) {
            queen_bb ^= to;
        } else if (selectionSquare & (to <<  8)) {
            rook_bb ^= to;
        } else if (selectionSquare & (to << 16)) {
            bishop_bb ^= to;
        } else if (selectionSquare & (to << 24)) {
            knight_bb ^= to;
        }
        black_bb ^= fromTo;
    }
    pawn_bb ^= from;
    pieces_bb = (white_bb | black_bb);
    whiteRepetitionLookup.clear();
    blackRepetitionLookup.clear();
    fiftyMoveCounter = 0;
}

uint64_t Position::IsInCheck(bool whitesTurn) {
    uint64_t myKing;
    if (whitesTurn) {
        myKing = king_bb & white_bb;
    } else {
        myKing = king_bb & black_bb;
    }
    if (whitesTurn) {
        uint64_t pawnAttacks = (((myKing << 7) & Bitboard::notAfile_bb) |
                    ((myKing << 9) & Bitboard::notHfile_bb));
        if (pawnAttacks & black_bb & pawn_bb) {
            return myKing;
        };
    } else if (!whitesTurn) {
        uint64_t pawnAttacks = (((myKing >> 7) & Bitboard::notHfile_bb) |
                    ((myKing >> 9) & Bitboard::notAfile_bb));
        if (pawnAttacks & white_bb & pawn_bb) {
            return myKing;
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
    if (knightAttacks & (whitesTurn? black_bb : white_bb) & knight_bb) {
        return myKing;
    }

    uint64_t kingAttacks = (((myKing << 1) & Bitboard::notHfile_bb) |
                ((myKing << 7) & Bitboard::notAfile_bb) |
                ((myKing << 8)                        ) |
                ((myKing << 9) & Bitboard::notHfile_bb) |
                ((myKing >> 1) & Bitboard::notAfile_bb) |
                ((myKing >> 7) & Bitboard::notHfile_bb) |
                ((myKing >> 8)                        ) |
                ((myKing >> 9) & Bitboard::notAfile_bb));
    if (kingAttacks & (whitesTurn? black_bb : white_bb) & king_bb) {
        return myKing;
    }


    uint64_t empty = ~pieces_bb;
    uint64_t scan = myKing;
    uint64_t flood = myKing;
    
    scan = myKing;
    flood = myKing;
    empty = ~pieces_bb & Bitboard::notHfile_bb;
    flood |= scan = (scan << 9) & empty; // northwest
    flood |= scan = (scan << 9) & empty;
    flood |= scan = (scan << 9) & empty;
    flood |= scan = (scan << 9) & empty;
    flood |= scan = (scan << 9) & empty;
    flood |=        (scan << 9) & empty; 
    uint64_t diagAttacks = (flood << 9) & Bitboard::notHfile_bb; // might later change to not include captures
    
    scan = myKing;
    flood = myKing;
    empty = ~pieces_bb & Bitboard::notAfile_bb;
    flood |= scan = (scan >> 9) & empty; // southeast
    flood |= scan = (scan >> 9) & empty;
    flood |= scan = (scan >> 9) & empty;
    flood |= scan = (scan >> 9) & empty;
    flood |= scan = (scan >> 9) & empty;
    flood |=        (scan >> 9) & empty; 
    diagAttacks |= (flood >> 9) & Bitboard::notAfile_bb; // might later change to not include captures


    scan = myKing;
    flood = myKing;
    empty = ~pieces_bb & Bitboard::notAfile_bb;
    flood |= scan = (scan << 7) & empty; // northeast
    flood |= scan = (scan << 7) & empty;
    flood |= scan = (scan << 7) & empty;
    flood |= scan = (scan << 7) & empty;
    flood |= scan = (scan << 7) & empty;
    flood |=        (scan << 7) & empty; 
    diagAttacks |= (flood << 7) & Bitboard::notAfile_bb; // might later change to not include captures
    
    scan = myKing;
    flood = myKing;
    empty = ~pieces_bb & Bitboard::notHfile_bb;
    flood |= scan = (scan >> 7) & empty; // southwest
    flood |= scan = (scan >> 7) & empty;
    flood |= scan = (scan >> 7) & empty;
    flood |= scan = (scan >> 7) & empty;
    flood |= scan = (scan >> 7) & empty;
    flood |=        (scan >> 7) & empty; 
    diagAttacks |= (flood >> 7) & Bitboard::notHfile_bb; // might later change to not include captures

    if (diagAttacks & (whitesTurn? black_bb : white_bb) & (queen_bb | bishop_bb)) {
        return myKing;
    }

    empty = ~pieces_bb;
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
    empty = ~pieces_bb & Bitboard::notHfile_bb;
    flood |= scan = (scan << 1) & empty; // west
    flood |= scan = (scan << 1) & empty;
    flood |= scan = (scan << 1) & empty;
    flood |= scan = (scan << 1) & empty;
    flood |= scan = (scan << 1) & empty;
    flood |=        (scan << 1) & empty; 
    rookAttacks |= (flood << 1) & Bitboard::notHfile_bb; // might later change to not include captures
    
    scan = myKing;
    flood = myKing;
    empty = ~pieces_bb & Bitboard::notAfile_bb;
    flood |= scan = (scan >> 1) & empty; // east
    flood |= scan = (scan >> 1) & empty;
    flood |= scan = (scan >> 1) & empty;
    flood |= scan = (scan >> 1) & empty;
    flood |= scan = (scan >> 1) & empty;
    flood |=        (scan >> 1) & empty; 
    rookAttacks |= (flood >> 1) & Bitboard::notAfile_bb; // might later change to not include captures

    if (rookAttacks & (whitesTurn? black_bb : white_bb) & (queen_bb | rook_bb)) {
        return myKing;
    }
    return 0;
}

GameOver Position::IsDraw(bool whitesTurn) {
    if (CheckForRepetition(whitesTurn)) {
        std::cout << "Draw by threefold repetition!" << std::endl;
        return GameOver::ThreeRepetition;
    } else if (CheckForNoMoves(!whitesTurn)) {
        std::cout << "Draw by stalemate!" << std::endl;
        return GameOver::Stalemate;
    } else if (fiftyMoveCounter >= 50) {
        std::cout << "Draw by fifty moves without a capture or pawn push!" << std::endl;
        return GameOver::FiftyNothingMoves;
    } else if (CheckForDeadPosition()) {
        std::cout << "Draw by insufficient mating material!" << std::endl;
        return GameOver::DeadPosition;
    } else {
        return GameOver::None;
    }
}
