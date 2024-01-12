#include "WhiteSelectingPieceState.h"
#include "WhiteSelectingMoveState.h"
#include "Application.h"
#include "Renderer2D.h"
#include "Position.h"

void WhiteSelectingPieceState::Enter() {
    std::cout << "Entering W select P" << std::endl;
}
void WhiteSelectingPieceState::ProcessClicks() {
    uint64_t bitSquareClicked;
    if (!app.Renderer().lock()->GetLastSquareClicked(bitSquareClicked)) {
        return;
    }
    if (bitSquareClicked & app.Board().lock()->white_bb) {
        std::string stringBoard(64, '-');
        Util::PopulateStringBoard(stringBoard, bitSquareClicked, 'c');
        Util::PopulateStringBoard(stringBoard, app.Board().lock()->GetQuietMoves(bitSquareClicked, true), 'm'); 
        Util::PopulateStringBoard(stringBoard, app.Board().lock()->GetCaptures(bitSquareClicked, true), 'a');
        app.Renderer().lock()->ShowAvailableMoves(stringBoard);
        app.SelectedPiece(bitSquareClicked);
        app.CurrentState(app.WhiteSelectingMove());
    } else {
        app.CurrentState(app.WhiteSelectingPiece());
    }
}
void WhiteSelectingPieceState::Exit() {

}