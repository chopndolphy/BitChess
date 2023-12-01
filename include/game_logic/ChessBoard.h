#pragma once
#include <vector>
#include <array>
#include <string>
#include "app_logic/Enums.h"
#include "app_logic/Coord.h"
#include "app_logic/Square.h"

class ChessPiece;
class ChessBoard {
    public:
        ChessBoard();
        ChessBoard(BoardLayouts boardLayout);
        ~ChessBoard();
        const std::unique_ptr<ChessPiece>& getPieceAt(Coord location) {
            return getSquare(location)->getPiece();
        }
        std::array<std::array<std::string, 8>, 8> getBoardView();
        void setPieceAt(Coord destination, Coord location);
        void setNextMoveEnPassant(bool isEnPassant) {
            nextMoveEnPassant = isEnPassant;
        }
        void setNextMoveCastle(bool isCastle) {
            nextMoveCastle = isCastle;
        }
        void setNextMovePromoting(bool isPromoting) {
            nextMovePromoting = isPromoting;
        }
        GameState checkGameState(Color colorTurn);
        bool canCastle(const std::unique_ptr<ChessPiece>& piece, Coord destination);
        bool kingIsProtected(const std::unique_ptr<ChessPiece>& piece, Coord destination);
    private:
        std::array<std::array<Square*, 8>, 8> boardState = {};
        bool nextMoveEnPassant;
        bool nextMoveCastle;
        bool nextMovePromoting;
        Square*& getSquare(Coord coord);
        void addChessPiece(PieceType pieceType, Color color, Coord location);
        void loadLayout(BoardLayouts boardLayout);
        void movePiece(Coord location, Coord destination);
};