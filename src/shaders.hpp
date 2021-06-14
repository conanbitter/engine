#pragma once

#include <gl/gl_core_3_2.hpp>
#include <string>

namespace mrm {

using namespace std;

class ShaderProgram {
   private:
    static string getShaderLog(GLuint shader);
    static string getProgramLog(GLuint shaderProgram);

    static GLuint compileShader(const string& source, GLenum shaderType);

    GLuint program;

   public:
    ShaderProgram(const string& vertexShader, const string& fragmentShader);
    ~ShaderProgram();
    void bind();

    operator GLuint() const {
        return program;
    };

    GLint getUniformHandle(string name);
    void setUniform(GLint uniform, GLint value);
    void setUniform(GLint uniform, GLfloat value);
    void setUniform(GLint uniform, GLfloat a, GLfloat b);
    void setUniform(string uniform, GLint value);
    void setUniform(string uniform, GLfloat value);
    void setUniform(string uniform, GLfloat a, GLfloat b);
};

}  // namespace mrm