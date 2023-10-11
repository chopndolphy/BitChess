#include "forward.h"
#include "GamePlay.h"

GamePlay::GamePlay(Player* white, Player* black, ChessBoard* board, UserInterface* interface) {
    whitePlayer = white;
    blackPlayer = black;
    chessBoard = board;
    userInterface = interface;

    colorTurn = White;
    gameOver = false;
}

void GamePlay::takeTurn() {
    switch(colorTurn){
        case White:
            whitePlayer->makeMove();
            colorTurn = Black;
        break;
        case Black:
            blackPlayer->makeMove();
            colorTurn = White;
        break;
    }

    updateView();
    updateGameState();
}

void GamePlay::updateGameState() {
    switch (chessBoard->checkGameState(colorTurn)) {
        case Continue:
            break;
        case WhiteWins:
            userInterface->displayGameOver(WhiteWins);
            gameOver = true;
            break;
        case BlackWins:
            userInterface->displayGameOver(BlackWins);
            gameOver = true;
            break;
        case Stalemate:
            userInterface->displayGameOver(Stalemate);
            gameOver = true;
            break;
        default:
            ErrorLogger::relayError(GAME01, userInterface);
    }
}

void GamePlay::updateView() {
    chessBoard->printBoard();
}