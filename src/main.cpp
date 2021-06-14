#define SDL_MAIN_HANDLED

#include "app.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main() {
    ami::AppWindowOptions opts{
        width : SCREEN_WIDTH,
        height : SCREEN_HEIGHT,
        vsync : true,
        mode : ami::WindowMode::Windowed
    };

    try {
        ami::AppWindow window(opts);
        window.run();
    } catch (ami::AppException &e) {
        ami::AppWindow::messageBox(e.message);
    }
    return 0;
}