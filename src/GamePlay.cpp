#include "GamePlay.h"
GamePlay::GamePlay(Player* white, Player* black, ChessBoard* board, UserInterface* interface) {
    whitePlayer = white;
    blackPlayer = black;
    chessBoard = board;
    colorTurn = White;
    userInterface = interface;
}
void GamePlay::setGameOver(Outcome outcome) {
    isGameOver = true;
    gameOutcome = outcome;
}
void GamePlay::takeTurn() {
    if (colorTurn = White) {
        whitePlayer->makeMove();
        colorTurn = Black;
    } else {
        blackPlayer->makeMove();
        colorTurn = White;
    }
}
