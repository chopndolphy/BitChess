#include "BlackSelectingPieceState.h"
#include "BlackSelectingMoveState.h"
#include "Game.h"
#include "Renderer2D.h"
#include "Board.h"

void BlackSelectingPieceState::Enter(Game &game) {
    std::cout << "Entering B select P" << std::endl;
}
void BlackSelectingPieceState::ProcessClicks(Game &game) {
    uint64_t bitSquareClicked;
    if (!game.GetRenderer().lock()->GetLastSquareClicked(bitSquareClicked)) {
        return;
    }
    if (bitSquareClicked & game.GetBoard().lock()->black_bb) {
        std::string stringBoard(64, '-');
        Util::PopulateStringBoard(stringBoard, bitSquareClicked, 'c');
        Util::PopulateStringBoard(stringBoard, game.GetBoard().lock()->GetQuietMoves(bitSquareClicked, false), 'm'); 
        Util::PopulateStringBoard(stringBoard, game.GetBoard().lock()->GetCaptures(bitSquareClicked, false), 'a');
        game.GetRenderer().lock()->ShowAvailableMoves(stringBoard);
        game.SetSelectedPiece(bitSquareClicked);
        game.SetState(BlackSelectingMoveState::GetInstance());
    } else {
        game.SetState(BlackSelectingPieceState::GetInstance());
    }
}
void BlackSelectingPieceState::Exit(Game &game) {

}
GameState& BlackSelectingPieceState::GetInstance() {
    static BlackSelectingPieceState singleton;
    return singleton;
}