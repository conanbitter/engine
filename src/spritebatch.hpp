#pragma once

#include <gl/gl_core_3_2.hpp>

namespace mrm {

const GLuint VERTEX_POSITION_LOCATION = 0;
const GLuint VERTEX_UV_LOCATION = 1;
const GLuint VERTEX_COLOR_LOCATION = 2;

#pragma pack(push, 1)
struct Vec2 {
    float x;
    float y;
};

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color White;
    static const Color Black;
    static const Color Signature;
};

struct Vertex {
    Vec2 pos;
    Vec2 uv;
    Color color;
};
#pragma pack(pop)

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
    void begin();
    void end();

    // Rule of five
    SpriteBatch(const SpriteBatch& prog) = delete;
    SpriteBatch& operator=(const SpriteBatch& prog) = delete;
    SpriteBatch(SpriteBatch&& prog);
    SpriteBatch& operator=(SpriteBatch&& prog);
};

}  // namespace mrm