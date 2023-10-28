#include "game_logic/ChessBoard.h"
#include "game_logic/ChessPiece.h"
#include "game_logic/Bishop.h"
#include "game_logic/King.h"
#include "game_logic/Knight.h"
#include "game_logic/Pawn.h"
#include "game_logic/Queen.h"
#include "game_logic/Rook.h"

ChessBoard::ChessBoard() {
    for (int i = 0; i < 8; i++) {
        boardSpaces.at(1).at(i) = new Pawn({i, 1}, White, this);
        boardSpaces.at(6).at(i) = new Pawn({i, 6}, Black,this);
    }
    boardSpaces.at(0).at(0) = new Rook({0, 0}, White, this);
    boardSpaces.at(0).at(7) = new Rook({7, 0}, White, this);
    boardSpaces.at(0).at(1) = new Knight({1, 0}, White, this);
    boardSpaces.at(0).at(6) = new Knight({6, 0}, White, this);
    boardSpaces.at(0).at(2) = new Bishop({2, 0}, White, this);
    boardSpaces.at(0).at(5) = new Bishop({5, 0}, White, this);
    boardSpaces.at(0).at(3) = new Queen({3, 0}, White, this);
    boardSpaces.at(0).at(4) = new King({4, 0}, White, this);

    boardSpaces.at(0).at(0) = new Rook({0, 7}, Black, this);
    boardSpaces.at(0).at(7) = new Rook({7, 7}, Black, this);
    boardSpaces.at(0).at(1) = new Knight({1, 7}, Black, this);
    boardSpaces.at(0).at(6) = new Knight({6, 7}, Black, this);
    boardSpaces.at(0).at(2) = new Bishop({2, 7}, Black, this);
    boardSpaces.at(0).at(5) = new Bishop({5, 7}, Black, this);
    boardSpaces.at(0).at(3) = new Queen({3, 7}, Black, this);
    boardSpaces.at(0).at(4) = new King({4, 7}, Black, this);
}
ChessBoard::~ChessBoard() {
    for (auto row : boardSpaces) {
        for (auto square : row) {
            delete square;
        }
    }
}
void ChessBoard::setPieceAt(std::vector<int> endSquare, ChessPiece* piece) {
    if (nextMoveCastle) {
        nextMoveCastle = false;
        // castle logic
    } else if (nextMoveEnPassant) {
        nextMoveEnPassant = false;
        if (piece->getColor() == White) {
            // removes attacked piece
            delete boardSpaces.at(endSquare.at(1) - 1).at(endSquare.at(0)); 
            boardSpaces.at(endSquare.at(1) - 1).at(endSquare.at(0)) = nullptr;
        } else if (piece->getColor() == Black) {
            // removes attacked piece
            delete boardSpaces.at(endSquare.at(1) + 1).at(endSquare.at(0)); 
            boardSpaces.at(endSquare.at(1) + 1).at(endSquare.at(0)) = nullptr;
        }
        // moves piece
        boardSpaces.at(piece->getLocation().at(1)).at(piece->getLocation().at(0)) = nullptr;
        boardSpaces.at(endSquare.at(1)).at(endSquare.at(0)) = piece;
    } else {
        if (boardSpaces.at(endSquare.at(1)).at(endSquare.at(0)) != nullptr) {
            // removes attack piece
            delete boardSpaces.at(endSquare.at(1)).at(endSquare.at(0));
        }
        // moves piece
        boardSpaces.at(piece->getLocation().at(1)).at(piece->getLocation().at(0)) = nullptr;
        boardSpaces.at(endSquare.at(1)).at(endSquare.at(0)) = piece;
        if (nextMovePromoting) {
            nextMovePromoting = false;
            // promotion logic
        }
    }
}
GameState ChessBoard::checkGameState(Color colorTurn) {
    
}
bool ChessBoard::canCastle(ChessPiece* piece, std::vector<int> square) {

}
bool ChessBoard::kingIsProtected(ChessPiece* piece, std::vector<int> square) {

}