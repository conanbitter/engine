#pragma once

#include <gl/gl_core_3_2.hpp>

namespace mrm {

const GLuint VERTEX_POSITION_LOCATION = 0;
const GLuint VERTEX_UV_LOCATION = 1;
const GLuint VERTEX_COLOR_LOCATION = 2;

class SpriteBatch {
   private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    bool valid;

    void destroy();

   public:
    SpriteBatch() : valid{false}, vao{0}, vbo{0}, ebo{0} {};
    ~SpriteBatch();
    void init();
    void beginDraw();
    void endDraw();

    // Rule of five
    SpriteBatch(const SpriteBatch& prog) = delete;
    SpriteBatch& operator=(const SpriteBatch& prog) = delete;
    SpriteBatch(SpriteBatch&& prog);
    SpriteBatch& operator=(SpriteBatch&& prog);
};

}  // namespace mrm