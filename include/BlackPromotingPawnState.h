#pragma once
#include "AppState.h"

class BlackPromotingPawnState : public AppState {
    public:
        BlackPromotingPawnState(Application &application) : app(application) {};
        void Enter();
        void ProcessClicks();
        void Exit();
    private:
        Application &app;
};
