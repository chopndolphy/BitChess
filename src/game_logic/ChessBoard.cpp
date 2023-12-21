#include "game_logic/ChessBoard.h"
#include "game_logic/ChessPiece.h"
#include "game_logic/Bishop.h"
#include "game_logic/King.h"
#include "game_logic/Knight.h"
#include "game_logic/Pawn.h"
#include "game_logic/Queen.h"
#include "game_logic/Rook.h"
#include <iostream>
#include <memory>

ChessBoard::ChessBoard() {
    loadBoard();
    loadLayout(BoardLayouts::Normal);
}
ChessBoard::ChessBoard(BoardLayouts boardLayout) {
    loadBoard();
    loadLayout(boardLayout);
}
ChessBoard::~ChessBoard() {
    deleteBoard();
}
void ChessBoard::setPieceAt(Coord destination, Coord location) {
    if (nextMoveCastle) {
        nextMoveCastle = false;
        // insert castle logic here
    } else if (nextMoveEnPassant) {
        nextMoveEnPassant = false;
        if (getPieceAt(location)->getColor() == Color::White) {
            getSquare(Coord(destination.x(), destination.y()-1))->deleteChessPiece(); 
        } else if (getPieceAt(location)->getColor() == Color::Black) {
            getSquare(Coord(destination.x(), destination.y()+1))->deleteChessPiece(); 
        }
    } else if (getSquare(destination)->getPiece() != nullptr) {
            getSquare(destination)->deleteChessPiece();
    }
    if (nextMovePromoting) {
        nextMovePromoting = false;
        // insert promotion logic here
    }
    getSquare(destination)->moveToThisSquare(getSquare(location));
}
GameState ChessBoard::checkGameState(Color colorTurn) {
    
}
bool ChessBoard::canCastle(ChessPiece* piece, Coord destination) {

}
bool ChessBoard::kingIsProtected(ChessPiece* piece, Coord destination) {

}
std::array<std::array<std::string, 8>, 8> ChessBoard::getBoardView() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (getSquare(Coord(j, i))->getPiece() == nullptr) {
                boardView.at(i).at(j) = "  ";
            } else if (getSquare(Coord(j, i))->getPiece() != nullptr) {
                boardView.at(i).at(j) = getSquare(Coord(j, i))->getPiece()->getConsoleView();
            } else {
                boardView.at(i).at(j) = "  ";
            }
        }
    }
    
    return boardView;
}
Square* ChessBoard::getSquare(Coord coord) {
    return boardState.at(coord.y()).at(coord.x());
}
void ChessBoard::addChessPiece(PieceType pieceType, Color color, Coord coord) {
    switch (pieceType) {
        case PieceType::BishopType:
            getSquare(coord)->addChessPiece(new Bishop(color, coord, this));
            break;
        case PieceType::KingType:
            getSquare(coord)->addChessPiece(new King(color, coord, this));
            break;
        case PieceType::KnightType:
            getSquare(coord)->addChessPiece(new Knight(color, coord, this));
            break;
        case PieceType::PawnType:
            getSquare(coord)->addChessPiece(new Pawn(color, coord, this));
            break;
        case PieceType::QueenType:
            getSquare(coord)->addChessPiece(new Queen(color, coord, this));
            break;
        case PieceType::RookType:
            getSquare(coord)->addChessPiece(new Rook(color, coord, this));
            break;
    } 
}
void ChessBoard::loadLayout(BoardLayouts boardLayout) {
    switch (boardLayout) {
        case BoardLayouts::Normal:
            for (int i = 0; i < 8; i++) {
                addChessPiece(PieceType::PawnType, Color::White, Coord(i, 1));
                addChessPiece(PieceType::PawnType, Color::Black, Coord(i, 6));
            }
            addChessPiece(PieceType::RookType, Color::White, Coord('A', '1'));
            addChessPiece(PieceType::RookType, Color::White, Coord('H', '1'));
            addChessPiece(PieceType::KnightType, Color::White, Coord('B', '1'));
            addChessPiece(PieceType::KnightType, Color::White, Coord('G', '1'));
            addChessPiece(PieceType::BishopType, Color::White, Coord('C', '1'));
            addChessPiece(PieceType::BishopType, Color::White, Coord('F', '1'));
            addChessPiece(PieceType::QueenType, Color::White, Coord('D', '1'));
            addChessPiece(PieceType::KingType, Color::White, Coord('E', '1'));
            
            addChessPiece(PieceType::RookType, Color::Black, Coord('A', '8'));
            addChessPiece(PieceType::RookType, Color::Black, Coord('H', '8'));
            addChessPiece(PieceType::KnightType, Color::Black, Coord('B', '8'));
            addChessPiece(PieceType::KnightType, Color::Black, Coord('G', '8'));
            addChessPiece(PieceType::BishopType, Color::Black, Coord('C', '8'));
            addChessPiece(PieceType::BishopType, Color::Black, Coord('F', '8'));
            addChessPiece(PieceType::QueenType, Color::Black, Coord('D', '8'));
            addChessPiece(PieceType::KingType, Color::Black, Coord('E', '8'));
            break;
        case BoardLayouts::Empty:
            break;
    } 
}
void ChessBoard::movePiece(Coord location, Coord destination) {
    getSquare(destination)->moveToThisSquare(getSquare(location));
}
void ChessBoard::loadBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            boardState.at(i).at(j) = new Square(Coord(j, i));
        }
    }
}
void ChessBoard::deleteBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete boardState.at(i).at(j);
        }
    }
}