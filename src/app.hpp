#pragma once

#include <SDL.h>
#include <string>

namespace ami {

using namespace std;

struct AppException : public std::exception {
    string message;

    AppException(const string& component, const string& error, const string& description = "");

    const char* what() const noexcept override;
};

class AppWindow {
   private:
    SDL_Window* window;
    SDL_GLContext context;
    int windowWidth;
    int windowHeight;

    static string getSDLError();

   public:
    AppWindow(int width, int height);
    ~AppWindow();
    void run();
    static void messageBox(string message);
};

}  // namespace ami