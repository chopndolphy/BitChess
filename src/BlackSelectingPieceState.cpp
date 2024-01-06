#include "BlackSelectingPieceState.h"
#include "Game.h"

void BlackSelectingPieceState::Enter(Game &game) const {

}
void BlackSelectingPieceState::ProcessClicks(Game &game) const {

}
void BlackSelectingPieceState::Exit(Game &game) const {

}
GameState& BlackSelectingPieceState::GetInstance() {
    static BlackSelectingPieceState singleton;
    return singleton;
}