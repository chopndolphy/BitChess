#include "game_logic/ChessBoard.h"
#include "game_logic/ChessPiece.h"
#include "game_logic/Bishop.h"
#include "game_logic/King.h"
#include "game_logic/Knight.h"
#include "game_logic/Pawn.h"
#include "game_logic/Queen.h"
#include "game_logic/Rook.h"
#include <iostream>

ChessBoard::ChessBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 2; j < 6; j++) {
            Square* square = getSquare(Coord(i, j));
            square = new Square(Coord(i, j));
        }
    }
    for (int i = 0; i < 8; i++) {
        boardState.at(1).at(i) = new Pawn({i, 1}, Color::White, this);
        boardState.at(6).at(i) = new Pawn({i, 6}, Color::Black, this);
    }
    boardState.at(0).at(0) = new Rook({0, 0}, Color::White, this);
    boardState.at(0).at(7) = new Rook({7, 0}, Color::White, this);
    boardState.at(0).at(1) = new Knight({1, 0}, Color::White, this);
    boardState.at(0).at(6) = new Knight({6, 0}, Color::White, this);
    boardState.at(0).at(2) = new Bishop({2, 0}, Color::White, this);
    boardState.at(0).at(5) = new Bishop({5, 0}, Color::White, this);
    boardState.at(0).at(3) = new Queen({3, 0}, Color::White, this);
    boardState.at(0).at(4) = new King({4, 0}, Color::White, this);

    boardState.at(7).at(0) = new Rook({0, 7}, Color::Black, this);
    boardState.at(7).at(7) = new Rook({7, 7}, Color::Black, this);
    boardState.at(7).at(1) = new Knight({1, 7}, Color::Black, this);
    boardState.at(7).at(6) = new Knight({6, 7}, Color::Black, this);
    boardState.at(7).at(2) = new Bishop({2, 7}, Color::Black, this);
    boardState.at(7).at(5) = new Bishop({5, 7}, Color::Black, this);
    boardState.at(7).at(3) = new Queen({3, 7}, Color::Black, this);
    boardState.at(7).at(4) = new King({4, 7}, Color::Black, this);
}
ChessBoard::ChessBoard(BoardLayouts boardLayout) {

}
ChessBoard::~ChessBoard() {
    for (auto row : boardState) {
        for (auto square : row) {
            delete square;
        }
    }
}
Square* ChessBoard::getSquare(Coord coord) {
    return boardState.at(coord.y()).at(coord.x());
}
void ChessBoard::setPieceAt(std::vector<int> endSquare, ChessPiece* piece) {
    if (nextMoveCastle) {
        nextMoveCastle = false;
        // castle logic
    } else if (nextMoveEnPassant) {
        nextMoveEnPassant = false;
        if (piece->getColor() == Color::White) {
            // removes attacked piece
            delete boardState.at(endSquare.at(1) - 1).at(endSquare.at(0)); 
            boardState.at(endSquare.at(1) - 1).at(endSquare.at(0)) = nullptr;
        } else if (piece->getColor() == Color::Black) {
            // removes attacked piece
            delete boardState.at(endSquare.at(1) + 1).at(endSquare.at(0)); 
            boardState.at(endSquare.at(1) + 1).at(endSquare.at(0)) = nullptr;
        }
        // moves piece
        boardState.at(piece->getLocation().at(1)).at(piece->getLocation().at(0)) = nullptr;
        boardState.at(endSquare.at(1)).at(endSquare.at(0)) = piece;
    } else {
        if (boardState.at(endSquare.at(1)).at(endSquare.at(0)) != nullptr) {
            // removes attack piece
            delete boardState.at(endSquare.at(1)).at(endSquare.at(0));
        }
        // moves piece
        boardState.at(piece->getLocation().at(1)).at(piece->getLocation().at(0)) = nullptr;
        boardState.at(endSquare.at(1)).at(endSquare.at(0)) = piece;
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
void ChessBoard::processInput(const std::string &moveInput, ChessPiece* &targetPiece, Coord &targetCoord) {
    
}
std::array<std::array<std::string, 8>, 8> ChessBoard::getBoardView() {
    std::array<std::array<std::string, 8>, 8> boardView;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (boardState.at(i).at(j) == nullptr) {
                boardView.at(i).at(j) = "  ";
            } else if (boardState.at(i).at(j) != nullptr) {
                boardView.at(i).at(j) = boardState.at(i).at(j)->getConsoleView();
            } else {
                boardView.at(i).at(j) = "  ";
            }
        }
    }
    
    return boardView;
}