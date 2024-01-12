#include "BlackSelectingPieceState.h"
#include "BlackSelectingMoveState.h"
#include "Application.h"
#include "Renderer2D.h"
#include "Position.h"

void BlackSelectingPieceState::Enter() {
    std::cout << "Entering B select P" << std::endl;
}
void BlackSelectingPieceState::ProcessClicks() {
    uint64_t bitSquareClicked;
    if (!app.Renderer().lock()->GetLastSquareClicked(bitSquareClicked)) {
        return;
    }
    if (bitSquareClicked & app.Board().lock()->black_bb) {
        std::string stringBoard(64, '-');
        Util::PopulateStringBoard(stringBoard, bitSquareClicked, 'c');
        Util::PopulateStringBoard(stringBoard, app.Board().lock()->GetQuietMoves(bitSquareClicked, false), 'm'); 
        Util::PopulateStringBoard(stringBoard, app.Board().lock()->GetCaptures(bitSquareClicked, false), 'a');
        app.Renderer().lock()->ShowAvailableMoves(stringBoard);
        app.SelectedPiece(bitSquareClicked);
        app.CurrentState(app.BlackSelectingMove());
    } else {
        app.CurrentState(app.BlackSelectingPiece());
    }
}
void BlackSelectingPieceState::Exit() {

}