#include "WhitePromotingPawnState.h"
#include "WhiteSelectingMoveState.h"
#include "WhiteSelectingPieceState.h"
#include "BlackSelectingPieceState.h"
#include "Application.h"
#include "Renderer2D.h"
#include "Position.h"
#include "EndState.h"

void WhitePromotingPawnState::Enter() { 
    // std::cout << "Entering White promoting pawn" << std::endl;
}
void WhitePromotingPawnState::ProcessClicks() { 
    uint64_t bitSquareClicked;
    if (!app.Renderer().lock()->GetLastSquareClicked(bitSquareClicked)) {
        return;
    }
    if (bitSquareClicked & (app.Board().lock()->GetPromotionOptions(app.PromotionSquare(), true))) {
        app.Board().lock()->PromotePawn(app.SelectedPiece(), app.PromotionSquare(), bitSquareClicked, true);
        app.Renderer().lock()->UpdateBoardState(app.Board().lock()->GetBoardString());
        app.Renderer().lock()->ShowAvailableMoves(std::string(64, '-'));
        app.Renderer().lock()->ShowPromotionMenu(std::string(64, '-'));
        std::string previousMoveString(64, '-');
        Util::PopulateStringBoard(previousMoveString, (app.SelectedPiece() | app.PromotionSquare()), 'm');
        app.Renderer().lock()->ShowPreviousMove(previousMoveString);

        uint64_t checkedKing = app.Board().lock()->IsInCheck(false);
        std::string checkedKingBoard(64, '-'); 
        if (checkedKing) {
            Util::PopulateStringBoard(checkedKingBoard, checkedKing, 'x');
            app.Renderer().lock()->ShowCheckedKing(checkedKingBoard);
            switch (app.Board().lock()->IsGameOver(false)) {
                case GameOver::None:
                    break;
                case GameOver::Checkmate:
                    std::cout << "White wins by checkmate!" << std::endl;
                    app.AppEndDisplay = EndDisplay::White;
                    app.CurrentState(app.End());
                    return;
                    break;
                default:
                    std::cout << "default triggered in black selecting move state" << std::endl;
                    break;
            }
        } else {
            app.Renderer().lock()->ShowCheckedKing(checkedKingBoard);
        }
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
void WhitePromotingPawnState::Exit() { 

}