#include "WhiteSelectingPieceState.h"
#include "Game.h"
#include "Renderer2D.h"

void WhiteSelectingPieceState::Enter(Game &game) const {

}
void WhiteSelectingPieceState::ProcessClicks(Game &game) const {
    uint64_t bitSquareClicked;
    if (!game.GetRenderer().lock()->GetLastSquareClicked(bitSquareClicked)) {
        return;
    }
    std::string stringBoard = "----------------------------------------------------------------";
    try {
        if (Util::PopulateStringBoard(stringBoard, bitSquareClicked, 'c')) {
            game.GetRenderer().lock()->ShowAvailableMoves(stringBoard);
        }
    } catch (std::exception &e) {
        std::cerr << "Mouse Click Error: " << e.what() << std::endl;
    }
}
void WhiteSelectingPieceState::Exit(Game &game) const {

}
GameState& WhiteSelectingPieceState::GetInstance() {
    static WhiteSelectingPieceState singleton;
    return singleton;
}
