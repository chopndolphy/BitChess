#include "Application.h"

int main() {
    Application app;
    while (app.IsRunning()) {
        app.ExecuteFrame();
    }
    app.ShutDown();
    return 0;
}