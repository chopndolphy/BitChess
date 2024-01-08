#include "WhiteSelectingMoveState.h"
#include "WhiteSelectingPieceState.h"
#include "BlackSelectingPieceState.h"
#include "Game.h"
#include "Renderer2D.h"
#include "Board.h"

void WhiteSelectingMoveState::Enter(Game &game) { 
    std::cout << "Entering W select M" << std::endl;
}
void WhiteSelectingMoveState::ProcessClicks(Game &game) { 
    uint64_t bitSquareClicked;
    if (!game.GetRenderer().lock()->GetLastSquareClicked(bitSquareClicked)) {
        return;
    }
    if (bitSquareClicked & (game.GetBoard().lock()->GetQuietMoves(game.GetSelectedPiece(), true) | game.GetBoard().lock()->GetCaptures(game.GetSelectedPiece(), true))) {
        game.GetBoard().lock()->MakeMove(game.GetSelectedPiece(), bitSquareClicked, true);
        game.GetRenderer().lock()->UpdateBoardState(game.GetBoard().lock()->GetBoardString());
        game.GetRenderer().lock()->ShowAvailableMoves(std::string(64, '-'));
        std::string previousMoveString(64, '-');
        Util::PopulateStringBoard(previousMoveString, (game.GetSelectedPiece() | bitSquareClicked), 'm');
        game.GetRenderer().lock()->ShowPreviousMove(previousMoveString);
        // maybe flip board?
        game.SetState(BlackSelectingPieceState::GetInstance());
    } else {
        if (bitSquareClicked & game.GetBoard().lock()->white_bb) {
            std::string stringBoard(64, '-');
            Util::PopulateStringBoard(stringBoard, bitSquareClicked, 'c');
            Util::PopulateStringBoard(stringBoard, game.GetBoard().lock()->GetQuietMoves(bitSquareClicked, true), 'm'); 
            Util::PopulateStringBoard(stringBoard, game.GetBoard().lock()->GetCaptures(bitSquareClicked, true), 'a');
            game.GetRenderer().lock()->ShowAvailableMoves(stringBoard);
            game.SetSelectedPiece(bitSquareClicked);
            game.SetState(WhiteSelectingMoveState::GetInstance());
        } else {
            std::string stringBoard(64, '-');
            game.GetRenderer().lock()->ShowAvailableMoves(stringBoard);
            game.SetSelectedPiece(0);
            game.SetState(WhiteSelectingPieceState::GetInstance());
        }
    }
}
void WhiteSelectingMoveState::Exit(Game &game) { 

}
GameState& WhiteSelectingMoveState::GetInstance() {
    static WhiteSelectingMoveState singleton;
    return singleton;
}