#pragma once
#include "AppState.h"

class StartState : public AppState {
    public:
        StartState(Application &application) : app(application) {};
        void Enter();
        void ProcessClicks();
        void Exit();
    private:
        Application &app;
};