#include "forward.h"
#include "ChessBoard.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

ChessBoard::ChessBoard(): nextMoveCastle(false), nextMoveEnPassant(false), nextMovePromoting(false) {

    std::array<char, 64> gameBoard {
        'r', 'n', 'b', 'k', 'q', 'b', 'n', 'r',
        'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
        'R', 'N', 'B', 'K', 'Q', 'B', 'N', 'R'
    };

    for(int i = 0; i < gameBoard.size(); ++i) {
        char p = gameBoard.at(i);
        int x = i % 8;
        int y = i / 8;
        Color col = p < 'a' ? White : Black; // upper case: White; lower case: Black

        p = p < 'a' ? p : p - 32; // force upper case for cleaner code

        ChessPiece* piece = nullptr;
        switch(p){
            case 'R': piece = new Rook({x, y}, col, this); break; // Rook
            case 'N': piece = new Knight({x, y}, col, this); break; // Knight
            case 'B': piece = new Bishop({x, y}, col, this); break; // Bishop
            case 'P': piece = new Pawn({x, y}, col, this); break; // Pawn
            case 'Q': piece = new Queen({x, y}, col, this); break; // Queen
            case 'K': piece = new King({x, y}, col, this); break; // King
        }

        boardSpaces.at(y).at(x) = piece;
    }
}

ChessBoard::~ChessBoard() {
    for (auto row : boardSpaces) {
        for (auto square : row) {
            delete square;
        }
    }
}

void ChessBoard::setPieceAt(std::vector<int> endSquare, ChessPiece* piece) {
    /*
        Needs Rework:

        Having multiple stores of location data can cause serious bugs;
            makes it really difficult to focus on the *real* position of the piece.
        Try removing the location data from the pieces, and instead you can use a lookup if that position data is important.
            (iterating an 8x8 grid is absolutely nothing to the CPU)
    */
    if (nextMoveCastle) {
        nextMoveCastle = false;
        // castle logic
    } else if (nextMoveEnPassant) {
        nextMoveEnPassant = false;
        if (piece->getColor() == White) {
            // removes attacked piece
            ChessPiece*& piece = boardSpaces.at(endSquare.at(1) - 1).at(endSquare.at(0));
            delete piece;
            piece = nullptr;
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
    return Continue; // temporary
}

bool ChessBoard::canCastle(ChessPiece* piece, std::vector<int> square) {
    return true; // temporary
}

bool ChessBoard::kingIsProtected(ChessPiece* piece, std::vector<int> square) {
    return true; // temporary
}

void ChessBoard::printBoard() const {
    std::cout << "Board:\n";
    for(const auto& row : boardSpaces){
        for(const auto& col : row){            
            std::cout <<
                    ( col == nullptr ? " " : (
                      col->getColor() == Black ? "B" : "W"
                    ));
        }
        std::cout << "\n";
    }
}