#include "BlackSelectingMoveState.h"
#include "BlackSelectingPieceState.h"
#include "WhiteSelectingPieceState.h"
#include "Application.h"
#include "Renderer2D.h"
#include "Position.h"

void BlackSelectingMoveState::Enter() {
    // std::cout << "Entering B select M" << std::endl;
}
void BlackSelectingMoveState::ProcessClicks() {
    uint64_t bitSquareClicked;
    if (!app.Renderer().lock()->GetLastSquareClicked(bitSquareClicked)) {
        return;
    }
    if (bitSquareClicked & (app.Board().lock()->GetQuietMoves(app.SelectedPiece(), false) | 
    app.Board().lock()->GetCaptures(app.SelectedPiece(), false))) {
        app.Board().lock()->MakeMove(app.SelectedPiece(), bitSquareClicked, false);
        app.Renderer().lock()->UpdateBoardState(app.Board().lock()->GetBoardString());
        app.Renderer().lock()->ShowAvailableMoves(std::string(64, '-'));
        std::string previousMoveString(64, '-');
        Util::PopulateStringBoard(previousMoveString, (app.SelectedPiece() | bitSquareClicked), 'm');
        app.Renderer().lock()->ShowPreviousMove(previousMoveString);
        // maybe flip board?
        app.CurrentState(app.WhiteSelectingPiece());
    } else {
        if (bitSquareClicked & app.Board().lock()->black_bb) {
            std::string stringBoard(64, '-');
            Util::PopulateStringBoard(stringBoard, bitSquareClicked, 'c');
            Util::PopulateStringBoard(stringBoard, app.Board().lock()->GetQuietMoves(bitSquareClicked, false), 'm'); 
            Util::PopulateStringBoard(stringBoard, app.Board().lock()->GetCaptures(bitSquareClicked, false), 'a');
            app.Renderer().lock()->ShowAvailableMoves(stringBoard);
            app.SelectedPiece(bitSquareClicked);
            app.CurrentState(app.BlackSelectingMove());
        } else {
            std::string stringBoard(64, '-');
            app.Renderer().lock()->ShowAvailableMoves(stringBoard);
            app.SelectedPiece(0);
            app.CurrentState(app.BlackSelectingPiece());
        }
    }
}
void BlackSelectingMoveState::Exit() {

}