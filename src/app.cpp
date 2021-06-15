#include "app.hpp"
#include "shaders.hpp"
#include "spritebatch.hpp"

#include <sstream>
#include <gl/gl_core_3_2.hpp>

namespace mrm {

const string vertexShaderCode = R"(
    #version 410

	layout(location = 0) in vec2 vert;
	layout(location = 1) in vec2 vertUV;
	layout(location = 2) in vec4 vertColor;

	out vec2 fragUV;
	out vec4 fragColor;

    void main() {
		gl_Position = vec4(vert.x, vert.y, 0.0, 1.0);
		fragUV = vertUV;
		fragColor = vertColor;
    }
)";

const string fragmentShaderCode = R"(
    #version 410
    uniform sampler2D tex;

    in vec2 fragUV;
    in vec4 fragColor;

    layout(location = 0) out vec4 outputColor;

    void main() {
        outputColor = vec4(0.5, 0.5, 0.0, 1.0); //texture(tex, fragUV)*fragColor;
    }
)";

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

string AppWindow::getSDLError() {
    const char* error = SDL_GetError();
    if (error != nullptr) {
        return string(error);
    } else {
        return "unknown";
    }
}

AppWindow::AppWindow(const AppWindowOptions& options)
    : windowWidth{options.width},
      windowHeight{options.height} {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    uint32_t flags = SDL_WINDOW_OPENGL;
    if (options.mode == WindowMode::Fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    } else if (options.mode == WindowMode::FullscreenBorderless) {
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    window = SDL_CreateWindow(
        "Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        flags);
    context = SDL_GL_CreateContext(window);
    if (context == NULL) {
        throw AppException("SDL", "Error creating context", getSDLError());
    }

    SDL_GL_SetSwapInterval(options.vsync ? 1 : 0);

    gl::exts::LoadTest glLoadResult = gl::sys::LoadFunctions();
    if (!glLoadResult) {
        throw AppException("OpenGL", "Error in glLoad");
    }

    // OpenGL stuff
    gl::Enable(gl::BLEND);
    gl::Disable(gl::DEPTH_TEST);
    gl::PixelStorei(gl::UNPACK_ALIGNMENT, 1);
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
    ShaderProgram defaultShader(vertexShaderCode, fragmentShaderCode);
    SpriteBatch batch;
    batch.init();
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
        defaultShader.bind();
        batch.end();

        SDL_GL_SwapWindow(window);
        SDL_Delay(5);
    }
}

void AppWindow::messageBox(const string& message) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Application error", message.c_str(), NULL);
}

}  // namespace mrm