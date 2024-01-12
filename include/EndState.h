#pragma once
#include "AppState.h"

class EndState : public AppState {
    public:
        EndState(Application &application) : app(application) {};
        void Enter();
        void ProcessClicks();
        void Exit();
    private:
        Application &app;
};