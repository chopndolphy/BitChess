#include "PlayerConsole.h"
PlayerConsole::PlayerConsole(Color color, ChessBoard* board, UserInterface* interface) {
    playerColor = color;
    playerBoard = board;
    playerInterface = interface;
}
void PlayerConsole::makeMove() {
    ChessPiece* currentMovePiece = playerInterface->getMoveChessPiece(this, playerBoard);
    std::vector<int> currentMoveSquare = playerInterface->getMoveSquare(playerBoard);
    while (!currentMovePiece->isLegalMove(currentMoveSquare)) {
        ErrorLogger::relayError(MOV01, this, playerInterface);
        currentMovePiece = playerInterface->getMoveChessPiece(this, playerBoard);
        currentMoveSquare = playerInterface->getMoveSquare(playerBoard);
    }
    currentMovePiece->move(currentMoveSquare);
}