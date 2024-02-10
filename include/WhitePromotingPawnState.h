#pragma once
#include "AppState.h"

class WhitePromotingPawnState : public AppState {
    public:
        WhitePromotingPawnState(Application &application) : app(application) {};
        void Enter();
        void ProcessClicks();
        void Exit();
    private:
        Application &app;
};

