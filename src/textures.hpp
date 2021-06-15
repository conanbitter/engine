#pragma once

#include <gl/gl_core_3_2.hpp>
#include <string>

namespace mrm {

class Texture {
   private:
    int width;
    int height;
    GLuint handle;

   public:
    Texture();
    ~Texture();
    void loadFromFile(std::string filename);
    void loadFromMemory(int width, int height, const void* data);
    void bind();
    void getSize(int& w, int& h) {
        w = width;
        h = height;
    }

    // Rule of five
    Texture(const Texture& prog) = delete;
    Texture& operator=(const Texture& prog) = delete;
    Texture(Texture&& prog);
    Texture& operator=(Texture&& prog);
};
}  // namespace mrm
