#include "game_logic/ChessPiece.h"
#include "game_logic/ChessBoard.h"
#include "interface/BishopView.h"
#include "interface/KingView.h"
#include "interface/KnightView.h"
#include "interface/RookView.h"
#include "interface/PawnView.h"
#include "interface/QueenView.h"

void ChessPiece::createView(Color color, PieceType type) {
    switch (type) {
    case RookType:
        view = new RookView(color);
        break;
    case BishopType:
        view = new BishopView(color);
        break;
    case KnightType:
        view = new KnightView(color);
        break;
    case QueenType:
        view = new QueenView(color);
        break;
    case PawnType:
        view = new PawnView(color);
        break;
    case KingType:
        view = new KingView(color);
        break;
    default:
        break;
    }
}