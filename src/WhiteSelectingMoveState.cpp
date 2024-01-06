#include "WhiteSelectingMoveState.h"
#include "Game.h"

void WhiteSelectingMoveState::Enter(Game &game) const {

}
void WhiteSelectingMoveState::ProcessClicks(Game &game) const {

}
void WhiteSelectingMoveState::Exit(Game &game) const {

}
GameState& WhiteSelectingMoveState::GetInstance() {
    static WhiteSelectingMoveState singleton;
    return singleton;
}