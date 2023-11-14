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
        ChessPiece* getPieceAt(std::vector<int> square) {
            return boardState.at(square.at(1)).at(square.at(0));
        }
        std::array<std::array<std::string, 8>, 8> getBoardView();
        void setPieceAt(std::vector<int> endSquare, ChessPiece* piece);
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
        bool canCastle(ChessPiece* piece, std::vector<int> sqaure);
        bool kingIsProtected(ChessPiece* piece, std::vector<int> square);
        void processInput(const std::string &moveInput, ChessPiece* &targetPiece, Coord &targetCoord);
    private:
        std::array<std::array<Square*, 8>, 8> boardState = {};
        bool nextMoveEnPassant;
        bool nextMoveCastle;
        bool nextMovePromoting;
        Square* getSquare(Coord coord);
};