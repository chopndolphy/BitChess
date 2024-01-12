#pragma once
#include "AppState.h"


class WhiteSelectingPieceState : public AppState {
    public:
        WhiteSelectingPieceState(Application &application) : app(application) {};
        void Enter();
        void ProcessClicks();
        void Exit();
    private:
        Application &app;
};