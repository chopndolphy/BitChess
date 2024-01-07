#include "WhiteSelectingPieceState.h"
#include "WhiteSelectingMoveState.h"
#include "Game.h"
#include "Renderer2D.h"
#include "Board.h"

void WhiteSelectingPieceState::Enter(Game &game) {
    std::cout << "Entering W select P" << std::endl;
}
void WhiteSelectingPieceState::ProcessClicks(Game &game) {
    uint64_t bitSquareClicked;
    if (!game.GetRenderer().lock()->GetLastSquareClicked(bitSquareClicked)) {
        return;
    }
    if (bitSquareClicked & game.GetBoard().lock()->white_bb) {
        std::string stringBoard(64, '-');
        Util::PopulateStringBoard(stringBoard, bitSquareClicked, 'c');
        Util::PopulateStringBoard(stringBoard, game.GetBoard().lock()->GetQuietMoves(bitSquareClicked, true), 'm'); 
        Util::PopulateStringBoard(stringBoard, game.GetBoard().lock()->GetCaptures(bitSquareClicked, true), 'a');
        game.GetRenderer().lock()->ShowAvailableMoves(stringBoard);
        game.SetSelectedPiece(bitSquareClicked);
        game.SetState(WhiteSelectingMoveState::GetInstance());
    } else {
        game.SetState(WhiteSelectingPieceState::GetInstance());
    }
}
void WhiteSelectingPieceState::Exit(Game &game) {

}
GameState& WhiteSelectingPieceState::GetInstance() {
    static WhiteSelectingPieceState singleton;
    return singleton;
}
