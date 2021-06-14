#define SDL_MAIN_HANDLED

#include "app.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main() {
    mrm::AppWindowOptions opts{
        width : SCREEN_WIDTH,
        height : SCREEN_HEIGHT,
        vsync : true,
        mode : mrm::WindowMode::Windowed
    };

    try {
        mrm::AppWindow window(opts);
        window.run();
    } catch (mrm::AppException &e) {
        mrm::AppWindow::messageBox(e.message);
    }
    return 0;
}