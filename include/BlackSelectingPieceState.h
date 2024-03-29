#pragma once
#include "AppState.h"

class BlackSelectingPieceState : public AppState {
    public:
        BlackSelectingPieceState(Application &application) : app(application) {};
        void Enter();
        void ProcessClicks();
        void Exit();
    private:
        Application &app;
};