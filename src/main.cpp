#define SDL_MAIN_HANDLED

#include "app.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main() {
    try {
        ami::AppWindow window(SCREEN_WIDTH, SCREEN_HEIGHT);
        window.run();
    } catch (ami::AppException &e) {
        ami::AppWindow::messageBox(e.message);
    }
    return 0;
}