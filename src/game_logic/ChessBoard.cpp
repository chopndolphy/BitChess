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
    loadLayout(BoardLayouts::Normal);
}
ChessBoard::ChessBoard(BoardLayouts boardLayout) {
    loadLayout(boardLayout);
}
ChessBoard::~ChessBoard() {
}
void ChessBoard::setPieceAt(Coord destination, ChessPiece* piece) {
    if (nextMoveCastle) {
        nextMoveCastle = false;
        // castle logic
    } else if (nextMoveEnPassant) {
        nextMoveEnPassant = false;
        if (piece->getColor() == Color::White) {
            // removes attacked piece (!!!TODO!!!! Piece not deleted from memory!)
            getSquare(Coord(destination.x(), destination.y()-1))->removeChessPiece(); 
        } else if (piece->getColor() == Color::Black) {
            // removes attacked piece (!!!TODO!!!! Piece not deleted from memory!)
            getSquare(Coord(destination.x(), destination.y()+1))->removeChessPiece(); 
        }
    } else if (getSquare(destination)->getPiece() != nullptr) {
            // removes attacked piece (!!!TODO!!!! Piece not deleted from memory!)
            getSquare(destination)->removeChessPiece();
    }
    if (nextMovePromoting) {
        nextMovePromoting = false;
        // promotion logic
    }
    // move piece
    getSquare(destination)->moveToThisSquare(getSquare(piece->getLocation()));
}
GameState ChessBoard::checkGameState(Color colorTurn) {
    
}
bool ChessBoard::canCastle(ChessPiece* piece, Coord destination) {

}
bool ChessBoard::kingIsProtected(ChessPiece* piece, Coord destination) {

}
void ChessBoard::processInput(const std::string &moveInput, ChessPiece* &targetPiece, Coord &targetCoord) {
    
}
std::array<std::array<std::string, 8>, 8> ChessBoard::getBoardView() {
    std::array<std::array<std::string, 8>, 8> boardView;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (getSquare(Coord(j, i)) == nullptr) {
                boardView.at(i).at(j) = "  ";
            } else if (getSquare(Coord(j, i)) != nullptr) {
                boardView.at(i).at(j) = getPieceAt(Coord(j, i))->getConsoleView();
            } else {
                boardView.at(i).at(j) = "  ";
            }
        }
    }
    
    return boardView;
}
Square*& ChessBoard::getSquare(Coord coord) {
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
                for (int j = 2; j < 6; j++) {
                    getSquare(Coord(i, j))->removeChessPiece();
                }
            }
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
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    getSquare(Coord(i, j))->removeChessPiece();
                }
            }
    } 
}
void ChessBoard::movePiece(Coord location, Coord destination) {
}