#include "spritebatch.hpp"

namespace mrm {

const Color Color::Red{r : 255, g : 0, b : 0, a : 255};
const Color Color::Green{r : 0, g : 255, b : 0, a : 255};
const Color Color::Blue{r : 255, g : 0, b : 255, a : 255};
const Color Color::White{r : 255, g : 255, b : 255, a : 255};
const Color Color::Black{r : 0, g : 0, b : 0, a : 255};
const Color Color::Signature{r : 38, g : 38, b : 38, a : 255};

void SpriteBatch::init() {
    gl::GenVertexArrays(1, &vao);
    gl::BindVertexArray(vao);
    gl::GenBuffers(1, &vbo);
    gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
    gl::EnableVertexAttribArray(VERTEX_POSITION_LOCATION);
    gl::VertexAttribPointer(VERTEX_POSITION_LOCATION, 2, gl::FLOAT, false, sizeof(Vertex), nullptr);
    gl::EnableVertexAttribArray(VERTEX_UV_LOCATION);
    gl::VertexAttribPointer(VERTEX_UV_LOCATION, 2, gl::FLOAT, false, sizeof(Vertex), (const void*)(sizeof(Vec2)));
    gl::EnableVertexAttribArray(VERTEX_COLOR_LOCATION);
    gl::VertexAttribPointer(VERTEX_COLOR_LOCATION, 4, gl::UNSIGNED_BYTE, true, sizeof(Vertex), (const void*)(sizeof(Vec2) * 2));

    gl::GenBuffers(1, &ebo);
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ebo);
}

SpriteBatch::~SpriteBatch() {
    if (gl::IsBuffer(vbo)) {
        gl::DeleteBuffers(1, &vbo);
    }
    if (gl::IsBuffer(ebo)) {
        gl::DeleteBuffers(1, &ebo);
    }
    if (gl::IsVertexArray(vao)) {
        gl::DeleteVertexArrays(1, &vao);
    }
}

void SpriteBatch::begin() {
}

void SpriteBatch::end() {
    static Vertex quad[4] = {
        {Vec2{-0.5f, -0.5f}, Vec2{0, 0}, Color::Red},
        {Vec2{0.5f, -0.5f}, Vec2{1, 0}, Color::Blue},
        {Vec2{0.5f, 0.5f}, Vec2{1, 1}, Color::Green},
        {Vec2{-0.5f, 0.5f}, Vec2{0, 1}, Color::White}};

    static uint32_t elts[6] = {0, 1, 2, 0, 2, 3};

    gl::BindVertexArray(vao);
    gl::BufferData(gl::ARRAY_BUFFER, sizeof(Vertex) * 4, quad, gl::STATIC_DRAW);
    gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6, elts, gl::STATIC_DRAW);
    gl::DrawElements(gl::TRIANGLES, 6, gl::UNSIGNED_INT, nullptr);
}

}  // namespace mrm