#include "WhiteSelectingMoveState.h"
#include "WhiteSelectingPieceState.h"
#include "WhitePromotingPawnState.h"
#include "BlackSelectingPieceState.h"
#include "Application.h"
#include "Renderer2D.h"
#include "Position.h"
#include "EndState.h"

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
        if (bitSquareClicked & (app.Board().lock()->GetPromotionSquare(app.SelectedPiece(), true))) {
            // std::cout << "Trigged promotion condition" << std::endl;
            std::string promotionSquareString(64, '-');
            Util::PopulateStringBoard(promotionSquareString, bitSquareClicked, 'p');
            app.Renderer().lock()->ShowPromotionMenu(promotionSquareString);
            app.PromotionSquare(bitSquareClicked);
            app.CurrentState(app.WhitePromotingPawn());
            return;
        }
        app.Board().lock()->MakeMove(app.SelectedPiece(), bitSquareClicked, true);
        app.Renderer().lock()->UpdateBoardState(app.Board().lock()->GetBoardString());
        app.Renderer().lock()->ShowAvailableMoves(std::string(64, '-'));
        std::string previousMoveString(64, '-');
        Util::PopulateStringBoard(previousMoveString, (app.SelectedPiece() | bitSquareClicked), 'm');
        app.Renderer().lock()->ShowPreviousMove(previousMoveString);

        uint64_t checkedKing = app.Board().lock()->IsInCheck(false);
        std::string checkedKingBoard(64, '-'); 
        if (checkedKing) {
            Util::PopulateStringBoard(checkedKingBoard, checkedKing, 'x');
            app.Renderer().lock()->ShowCheckedKing(checkedKingBoard);
            if (app.Board().lock()->CheckForNoMoves(false)) {
                std::cout << "White wins by checkmate!" << std::endl;
                app.AppEndDisplay = EndDisplay::White;
                app.CurrentState(app.End());
                return;
            }
        } else {
            app.Renderer().lock()->ShowCheckedKing(checkedKingBoard);
        }

        // maybe flip board?
        switch (app.Board().lock()->IsDraw(true)) {
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
                app.CurrentState(app.BlackSelectingPiece());
                break;
        }
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