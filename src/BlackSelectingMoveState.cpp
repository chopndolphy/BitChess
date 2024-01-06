#include "BlackSelectingMoveState.h"
#include "Game.h"

void BlackSelectingMoveState::Enter(Game &game) const {

}
void BlackSelectingMoveState::ProcessClicks(Game &game) const {

}
void BlackSelectingMoveState::Exit(Game &game) const {

}
GameState& BlackSelectingMoveState::GetInstance() {
    static BlackSelectingMoveState singleton;
    return singleton;
}