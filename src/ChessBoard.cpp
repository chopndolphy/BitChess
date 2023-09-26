#include "ChessBoard.h"
ChessBoard::ChessBoard() {
    for (int i = 0; i < 8; i++) {
        whitePieces.push_back(Pawn({i, 1}, true));
        boardSpaces.at(1).at(i) = &whitePieces.back();
        blackPieces.push_back(Pawn({i, 6}, false));
        boardSpaces.at(6).at(i) = &blackPieces.back();
    }
    whitePieces.push_back(Rook({0, 0}, true));
    boardSpaces.at(0).at(0) = &whitePieces.back();
    whitePieces.push_back(Rook({7, 0}, true));
    boardSpaces.at(0).at(7) = &whitePieces.back();
    whitePieces.push_back(Knight({1, 0}, true));
    boardSpaces.at(0).at(1) = &whitePieces.back();
    whitePieces.push_back(Knight({6, 0}, true));
    boardSpaces.at(0).at(6) = &whitePieces.back();
    whitePieces.push_back(Bishop({2, 0}, true));
    boardSpaces.at(0).at(2) = &whitePieces.back();
    whitePieces.push_back(Bishop({5, 0}, true));
    boardSpaces.at(0).at(5) = &whitePieces.back();
    whitePieces.push_back(Queen({3, 0}, true));
    boardSpaces.at(0).at(3) = &whitePieces.back();
    whitePieces.push_back(King({4, 0}, true));
    boardSpaces.at(0).at(4) = &whitePieces.back();

    blackPieces.push_back(Rook({0, 7}, false));
    boardSpaces.at(7).at(0) = &whitePieces.back();
    blackPieces.push_back(Rook({7, 7}, false));
    boardSpaces.at(7).at(7) = &whitePieces.back();
    blackPieces.push_back(Knight({1, 7}, false));
    boardSpaces.at(7).at(1) = &whitePieces.back();
    blackPieces.push_back(Knight({6, 7}, false));
    boardSpaces.at(7).at(6) = &whitePieces.back();
    blackPieces.push_back(Bishop({2, 7}, false));
    boardSpaces.at(7).at(2) = &whitePieces.back();
    blackPieces.push_back(Bishop({5, 7}, false));
    boardSpaces.at(7).at(5) = &whitePieces.back();
    blackPieces.push_back(Queen({3, 7}, false));
    boardSpaces.at(7).at(3) = &whitePieces.back();
    blackPieces.push_back(King({4, 7}, false));
    boardSpaces.at(7).at(4) = &whitePieces.back();
}