#pragma once
#include "AppState.h"

class BlackSelectingMoveState : public AppState {
    public:
        BlackSelectingMoveState(Application &application) : app(application) {};
        void Enter();
        void ProcessClicks();
        void Exit();
    private:
        Application &app;
};
