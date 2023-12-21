#include "game_logic/ChessPiece.h"
#include "game_logic/ChessBoard.h"
#include "interface/BishopView.h"
#include "interface/KingView.h"
#include "interface/KnightView.h"
#include "interface/RookView.h"
#include "interface/PawnView.h"
#include "interface/QueenView.h"
#include "interface/BishopViewConsole.h"
#include "interface/KingViewConsole.h"
#include "interface/KnightViewConsole.h"
#include "interface/RookViewConsole.h"
#include "interface/PawnViewConsole.h"
#include "interface/QueenViewConsole.h"
#include <iostream>

ChessPiece::~ChessPiece() {
    delete view;
}