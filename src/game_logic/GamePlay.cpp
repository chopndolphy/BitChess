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

    colorTurn = Color::White;
    gameOver = false;
}
void GamePlay::takeTurn() {
    updateView(chessBoard->getBoardView());
    if (colorTurn == Color::White) {
        whitePlayer->makeMove();
        colorTurn = Color::Black;
    } else {
        blackPlayer->makeMove();
        colorTurn = Color::White;
    }
    updateGameState();
}
void GamePlay::updateGameState() {
    switch (chessBoard->checkGameState(colorTurn)) {
        case GameState::Continue:
            break;
        case GameState::WhiteWins:
            userInterface->displayGameOver(GameState::WhiteWins);
            gameOver = true;
            updateView(chessBoard->getBoardView());
            break;
        case GameState::BlackWins:
            userInterface->displayGameOver(GameState::BlackWins);
            gameOver = true;
            updateView(chessBoard->getBoardView());
            break;
        case GameState::Stalemate:
            userInterface->displayGameOver(GameState::Stalemate);
            gameOver = true;
            updateView(chessBoard->getBoardView());
            break;
        default:
            ErrorLogger::relayError(ErrorCode::GAME01, userInterface);
    }
}
void GamePlay::updateView(std::array<std::array<std::string, 8>, 8> boardView) {
    
    userInterface->displayBoard(boardView);
}