#include "WhiteSelectingMoveState.h"
#include "WhiteSelectingPieceState.h"
#include "BlackSelectingPieceState.h"
#include "Application.h"
#include "Renderer2D.h"
#include "Position.h"

void WhiteSelectingMoveState::Enter() { 
    // std::cout << "Entering W select M" << std::endl;
}
void WhiteSelectingMoveState::ProcessClicks() { 
    uint64_t bitSquareClicked;
    if (!app.Renderer().lock()->GetLastSquareClicked(bitSquareClicked)) {
        return;
    }
    if (bitSquareClicked & (app.Board().lock()->GetQuietMoves(app.SelectedPiece(), true) |
    app.Board().lock()->GetCaptures(app.SelectedPiece(), true))) {
        app.Board().lock()->MakeMove(app.SelectedPiece(), bitSquareClicked, true);
        app.Renderer().lock()->UpdateBoardState(app.Board().lock()->GetBoardString());
        app.Renderer().lock()->ShowAvailableMoves(std::string(64, '-'));
        std::string previousMoveString(64, '-');
        Util::PopulateStringBoard(previousMoveString, (app.SelectedPiece() | bitSquareClicked), 'm');
        app.Renderer().lock()->ShowPreviousMove(previousMoveString);
        // maybe flip board?
        app.CurrentState(app.BlackSelectingPiece());
    } else {
        if (bitSquareClicked & app.Board().lock()->white_bb) {
            std::string stringBoard(64, '-');
            Util::PopulateStringBoard(stringBoard, bitSquareClicked, 'c');
            Util::PopulateStringBoard(stringBoard, app.Board().lock()->GetQuietMoves(bitSquareClicked, true), 'm'); 
            Util::PopulateStringBoard(stringBoard, app.Board().lock()->GetCaptures(bitSquareClicked, true), 'a');
            app.Renderer().lock()->ShowAvailableMoves(stringBoard);
            app.SelectedPiece(bitSquareClicked);
            app.CurrentState(app.WhiteSelectingMove());
        } else {
            std::string stringBoard(64, '-');
            app.Renderer().lock()->ShowAvailableMoves(stringBoard);
            app.SelectedPiece(0);
            app.CurrentState(app.WhiteSelectingPiece());
        }
    }
}
void WhiteSelectingMoveState::Exit() { 

}