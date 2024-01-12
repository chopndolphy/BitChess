#pragma once
#include <memory>
#include <iostream>

class Application;
class AppState {
    public:
        virtual void Enter() = 0;
        virtual void ProcessClicks() = 0;
        virtual void Exit() = 0; 
        virtual ~AppState() {}
};