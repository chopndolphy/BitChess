#include "game_logic/GamePlay.h"
#include "interface/UserInterface.h"
#include "game_logic/ChessBoard.h"
#include "game_logic/Player.h"
#include "game_logic/ChessPiece.h"

GamePlay::GamePlay(Player* white, Player* black, ChessBoard* board, UserInterface* interface) {
    whitePlayer = white;
    blackPlayer = black;
    chessBoard = board;
    userInterface = interface;

    colorTurn = White;
    gameOver = false;
}
void GamePlay::takeTurn() {
    updateView(chessBoard->getBoardView());
    if (colorTurn == White) {
        whitePlayer->makeMove();
        colorTurn = Black;
    } else {
        blackPlayer->makeMove();
        colorTurn = White;
    }
    updateGameState();
}
void GamePlay::updateGameState() {
    switch (chessBoard->checkGameState(colorTurn)) {
        case Continue:
            break;
        case WhiteWins:
            userInterface->displayGameOver(WhiteWins);
            gameOver = true;
            updateView(chessBoard->getBoardView());
            break;
        case BlackWins:
            userInterface->displayGameOver(BlackWins);
            gameOver = true;
            updateView(chessBoard->getBoardView());
            break;
        case Stalemate:
            userInterface->displayGameOver(Stalemate);
            gameOver = true;
            updateView(chessBoard->getBoardView());
            break;
        default:
            ErrorLogger::relayError(GAME01, userInterface);
    }
}
void GamePlay::updateView(std::array<std::array<std::string, 8>, 8> boardView) {
    
    userInterface->displayBoard(boardView);
}