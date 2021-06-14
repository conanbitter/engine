#include "app.hpp"

#include <sstream>
#include <gl/gl_core_3_2.hpp>

namespace ami {

AppException::AppException(const string& component, const string& error, const string& description) {
    stringstream buf;
    buf << "[" << component << "] " << error;
    if (description.length() > 0) {
        buf << " : " << description;
    }
    message = buf.str();
};

const char* AppException::what() const noexcept {
    return message.c_str();
}

const string vertexShaderCode = R"(
    #version 410

    layout(location = 0) in vec3 vert;
    layout(location = 1) in vec2 vertUV;

    out vec2 fragUV;

    uniform mat4 perspMat;
    uniform mat4 rotMat;

    void main() {
        gl_Position = perspMat * rotMat * vec4(vert.x, vert.y, vert.z, 1.0);
        fragUV = vertUV;
    }
)";

const string fragmentShaderCode = R"(
    #version 410
    uniform sampler2D tex;

    in vec2 fragUV;

    layout(location = 0) out vec4 outputColor;

    void main() {
        outputColor = texture(tex, vec2(fragUV.x/2,fragUV.y));
    }
)";

string AppWindow::getSDLError() {
    const char* error = SDL_GetError();
    if (error != nullptr) {
        return string(error);
    } else {
        return "unknown";
    }
}

AppWindow::AppWindow(int width, int height) : windowWidth{width}, windowHeight{height} {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(
        "Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);
    if (context == NULL) {
        throw AppException("SDL", "Error creating context", getSDLError());
    }

    gl::exts::LoadTest glLoadResult = gl::sys::LoadFunctions();
    if (!glLoadResult) {
        throw AppException("OpenGL", "Error in glLoad");
    }

    gl::ClearColor(0.15f, 0.15f, 0.15f, 1.0f);
}

AppWindow::~AppWindow() {
    if (context) {
        SDL_GL_DeleteContext(context);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void AppWindow::run() {
    SDL_Event event;
    bool working = true;
    while (working) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    working = false;
                    break;
            }
        }

        gl::ClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        gl::Clear(gl::COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
        SDL_Delay(5);
    }
}

void AppWindow::messageBox(string message) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Application error", message.c_str(), NULL);
}

}  // namespace ami