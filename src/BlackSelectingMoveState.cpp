#include "BlackSelectingMoveState.h"
#include "BlackSelectingPieceState.h"
#include "WhiteSelectingPieceState.h"
#include "Game.h"
#include "Renderer2D.h"
#include "Board.h"

void BlackSelectingMoveState::Enter(Game &game) {
    std::cout << "Entering B select M" << std::endl;
}
void BlackSelectingMoveState::ProcessClicks(Game &game) {
    uint64_t bitSquareClicked;
    if (!game.GetRenderer().lock()->GetLastSquareClicked(bitSquareClicked)) {
        return;
    }
    if (bitSquareClicked & (game.GetBoard().lock()->GetQuietMoves(game.GetSelectedPiece(), false) | game.GetBoard().lock()->GetCaptures(game.GetSelectedPiece(), true))) {
        game.GetBoard().lock()->MakeMove(game.GetSelectedPiece(), bitSquareClicked, false);
        game.GetRenderer().lock()->UpdateBoardState(game.GetBoard().lock()->GetBoardString());
        game.GetRenderer().lock()->ShowAvailableMoves(std::string(64, '-'));
        std::string previousMoveString(64, '-');
        Util::PopulateStringBoard(previousMoveString, (game.GetSelectedPiece() | bitSquareClicked), 'm');
        game.GetRenderer().lock()->ShowPreviousMove(previousMoveString);
        game.SetState(WhiteSelectingPieceState::GetInstance());
    } else {
        if (bitSquareClicked & game.GetBoard().lock()->black_bb) {
            std::string stringBoard(64, '-');
            Util::PopulateStringBoard(stringBoard, bitSquareClicked, 'c');
            Util::PopulateStringBoard(stringBoard, game.GetBoard().lock()->GetQuietMoves(bitSquareClicked, false), 'm'); 
            Util::PopulateStringBoard(stringBoard, game.GetBoard().lock()->GetCaptures(bitSquareClicked, false), 'a');
            game.GetRenderer().lock()->ShowAvailableMoves(stringBoard);
            game.SetSelectedPiece(bitSquareClicked);
            game.SetState(BlackSelectingMoveState::GetInstance());
        } else {
            std::string stringBoard(64, '-');
            game.GetRenderer().lock()->ShowAvailableMoves(stringBoard);
            game.SetSelectedPiece(0);
            game.SetState(BlackSelectingPieceState::GetInstance());
        }
    }

}
void BlackSelectingMoveState::Exit(Game &game) {

}
GameState& BlackSelectingMoveState::GetInstance() {
    static BlackSelectingMoveState singleton;
    return singleton;
}