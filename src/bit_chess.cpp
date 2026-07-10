#include "Application.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int main() {
    Application app;
    while (app.IsRunning()) {
        app.ExecuteFrame();
    }
    app.ShutDown();
    return 0;
}