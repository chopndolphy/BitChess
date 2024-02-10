#include "BlackSelectingMoveState.h"
#include "BlackPromotingPawnState.h"
#include "BlackSelectingPieceState.h"
#include "WhiteSelectingPieceState.h"
#include "EndState.h"
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
        if (bitSquareClicked & (app.Board().lock()->GetPromotionSquare(app.SelectedPiece(), false))) {
            // std::cout << "triggered promotion square" << std::endl;
            std::string promotionSquareString(64, '-');
            Util::PopulateStringBoard(promotionSquareString, bitSquareClicked, 'p');
            app.Renderer().lock()->ShowPromotionMenu(promotionSquareString);
            app.PromotionSquare(bitSquareClicked);
            app.CurrentState(app.BlackPromotingPawn());
            return;
        }
        app.Board().lock()->MakeMove(app.SelectedPiece(), bitSquareClicked, false);
        app.Renderer().lock()->UpdateBoardState(app.Board().lock()->GetBoardString());
        app.Renderer().lock()->ShowAvailableMoves(std::string(64, '-'));
        std::string previousMoveString(64, '-');
        Util::PopulateStringBoard(previousMoveString, (app.SelectedPiece() | bitSquareClicked), 'm');
        app.Renderer().lock()->ShowPreviousMove(previousMoveString);

        uint64_t checkedKing = app.Board().lock()->IsInCheck(true);
        std::string checkedKingBoard(64, '-'); 
        if (checkedKing) {
            Util::PopulateStringBoard(checkedKingBoard, checkedKing, 'x');
            app.Renderer().lock()->ShowCheckedKing(checkedKingBoard);
            if (app.Board().lock()->CheckForNoMoves(true)) {
                std::cout << "Black wins by checkmate!" << std::endl;
                app.AppEndDisplay = EndDisplay::Black;
                app.CurrentState(app.End());
                return;
            }
        } else {
            app.Renderer().lock()->ShowCheckedKing(checkedKingBoard);
        }
        // maybe flip board?
        switch (app.Board().lock()->IsDraw(false)) {
            case GameOver::FiftyNothingMoves:
                app.AppEndDisplay = EndDisplay::Draw;
                app.CurrentState(app.End());
                break;
            case GameOver::Stalemate:
                app.AppEndDisplay = EndDisplay::Draw;
                app.CurrentState(app.End());
                break;
            case GameOver::ThreeRepetition:
                app.AppEndDisplay = EndDisplay::Draw;
                app.CurrentState(app.End());
                break;
            case GameOver::DeadPosition:
                app.AppEndDisplay = EndDisplay::Draw;
                app.CurrentState(app.End());
                break;
            case GameOver::None:
                app.CurrentState(app.WhiteSelectingPiece());
                break;
        }
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