#pragma once
#include "AppState.h"

class WhiteSelectingMoveState : public AppState {
    public:
        WhiteSelectingMoveState(Application &application) : app(application) {};
        void Enter();
        void ProcessClicks();
        void Exit();
    private:
        Application &app;
};