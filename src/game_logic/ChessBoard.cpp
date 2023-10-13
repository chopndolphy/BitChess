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

        rawBoard.at(y * boardWidth + x) = piece;
    }
}

ChessBoard::~ChessBoard() {
    for (auto piece : rawBoard) {
        delete piece;
    }
}


ChessPiece* ChessBoard::getPieceAt(Location square) {
    if( square.x < 0 || square.y < 0 ||
        square.x >= boardWidth || square.y >= boardHeight) {
            return nullptr;
    }

    return rawBoard.at(boardWidth * square.y + square.x);
}

void ChessBoard::setPieceAt(Location to, ChessPiece* piece) {
    if(piece == nullptr){
        return;
    }

    if( to.x < 0 || to.y < 0 ||
        to.x >= boardWidth || to.y >= boardHeight) {
            return;
    }

    Location from = piece->getLocation();

    auto& fromBlock = rawBoard.at(boardWidth * from.y + from.x);
    auto& toBlock = rawBoard.at(boardWidth * to.y + to.x);

    // moves piece
    toBlock = std::move(fromBlock);
    fromBlock = nullptr;
}

void ChessBoard::removePieceAt(Location square) {
    if( square.x < 0 || square.y < 0 ||
        square.x >= boardWidth || square.y >= boardHeight) {
            return;
    }

    auto& block = rawBoard.at(boardWidth * square.y + square.x);
    delete block;
    block = nullptr;
}

GameState ChessBoard::checkGameState(Color colorTurn) {
    return Continue; // temporary
}

bool ChessBoard::canCastle(ChessPiece* piece, Location square) {
    return true; // temporary
}

bool ChessBoard::kingIsProtected(ChessPiece* piece, Location square) {
    return true; // temporary
}

void ChessBoard::cleanState(Color color) {
    for(ChessPiece* piece : rawBoard){
        if(piece != nullptr && piece->getColor() == color) {
            piece->cleanState();
        }
    }
}

Location ChessBoard::getLocation(const ChessPiece* piece) const {    
    int i=0;
    for(const auto p : rawBoard){
        if(p == piece){
            return Location(i % boardWidth, i / boardWidth);
        }
        ++i;
    }

    return Location {-1, -1}; // piece not on board
}

ChessPiece* ChessBoard::collisionLine(Location start, Location end, bool endInclusive) {
    ChessPiece *found = nullptr, *first = nullptr;

    // check valid destination
    if( start == end ||
        end.x < 0 || end.y < 0 ||
        end.x >= boardWidth || end.y >= boardHeight) {
        return nullptr;
    }

    int xdelta = std::abs(start.x - end.x);
    int ydelta = std::abs(start.y - end.y);

    Location vec (
        xdelta == 0 ? 0 : start.x < end.x ? 1 : -1, // 0, 1 or -1
        ydelta == 0 ? 0 : start.y < end.y ? 1 : -1  // 0, 1 or -1
    ); // search vector

    if( xdelta > 0 && ydelta > 0 && xdelta != ydelta) {
        return nullptr; // line must be either perfect diagonal or perfect orthogonal
    }
    first = getPieceAt(start);
    for(Location pos = start; (pos != end || endInclusive) && !found; pos += vec ) {

        if(pos != start){
            found = getPieceAt(pos);
        }

        if(pos == end) break;
    }

    return found != nullptr ? found : first;
}

void ChessBoard::printBoard() const {
    std::cout << "Board:\n";
    for(int y = 0; y < boardHeight; ++y){
        for(int x = 0; x < boardWidth; ++x){
            const ChessPiece* piece = rawBoard.at(y * boardWidth + x);

            if(piece == nullptr){
                std::cout << " ";
            } else {
                char c = piece->getCharacter() /* to lower case for black -> */ + '\x20' * char(piece->getColor() == Black);

                std::cout << c;
            }
        }
        std::cout << "\n";
    }
}