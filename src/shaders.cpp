#include "shaders.hpp"
#include "app.hpp"

#include <gl/gl_core_3_2.hpp>
#include <string>

namespace mrm {

string ShaderProgram::getShaderLog(GLuint shader) {
    if (gl::IsShader(shader)) {
        string message = "";

        int infoLogLength = 0;
        int maxLength = infoLogLength;

        gl::GetShaderiv(shader, gl::INFO_LOG_LENGTH, &maxLength);
        char *infoLog = new char[maxLength];

        gl::GetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) {
            message = infoLog;
        }

        delete[] infoLog;

        return message;
    } else {
        return "Wrong shader handle";
    }
}

string ShaderProgram::getProgramLog(GLuint shaderProgram) {
    if (gl::IsProgram(shaderProgram)) {
        string message = "";

        int infoLogLength = 0;
        int maxLength = infoLogLength;

        gl::GetProgramiv(shaderProgram, gl::INFO_LOG_LENGTH, &maxLength);
        char *infoLog = new char[maxLength];

        gl::GetProgramInfoLog(shaderProgram, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) {
            message = infoLog;
        }

        delete[] infoLog;
        return message;
    } else {
        return "Wrong shader program handle";
    }
}

GLuint ShaderProgram::compileShader(const string &source, GLenum shaderType) {
    GLuint shader = gl::CreateShader(shaderType);
    const GLchar *lines[] = {
        source.c_str()};
    gl::ShaderSource(shader, 1, lines, NULL);
    gl::CompileShader(shader);
    GLint isCompiled = false;
    gl::GetShaderiv(shader, gl::COMPILE_STATUS, &isCompiled);
    if (isCompiled != true) {
        throw AppException("OpenGL", "Shader compile error", getShaderLog(shader));
    }
    return shader;
}

ShaderProgram::ShaderProgram(const string &vertexShader, const string &fragmentShader) {
    load(vertexShader, fragmentShader);
};

ShaderProgram::~ShaderProgram() {
    if (gl::IsProgram(program)) {
        gl::DeleteProgram(program);
    }
}

ShaderProgram::ShaderProgram(ShaderProgram &&prog) : program{prog} {
    prog.program = 0;
}

ShaderProgram &ShaderProgram::operator=(ShaderProgram &&prog) {
    if (gl::IsProgram(program)) {
        gl::DeleteProgram(program);
    }
    program = prog.program;
    prog.program = 0;
    return *this;
}

bool ShaderProgram::isValid() {
    return gl::IsProgram(program);
}

void ShaderProgram::bind() {
    if (gl::IsProgram(program)) {
        gl::UseProgram(program);
    }
}

void ShaderProgram::load(const string &vertexShader, const string &fragmentShader) {
    program = gl::CreateProgram();

    GLuint compiledVertexShader = compileShader(vertexShader, gl::VERTEX_SHADER);
    GLuint compiledFragmentShader = compileShader(fragmentShader, gl::FRAGMENT_SHADER);

    gl::AttachShader(program, compiledVertexShader);
    gl::AttachShader(program, compiledFragmentShader);
    gl::LinkProgram(program);
    GLint result = true;
    gl::GetProgramiv(program, gl::LINK_STATUS, &result);
    if (result != true) {
        throw AppException("OpenGL", "Shader link error", getProgramLog(program));
    }
}

GLint ShaderProgram::getUniformHandle(string name) {
    return gl::GetUniformLocation(program, name.c_str());
}

void ShaderProgram::setUniform(GLint uniform, GLint value) {
    if (uniform != -1) {
        gl::UseProgram(program);
        gl::Uniform1i(uniform, value);
    }
}

void ShaderProgram::setUniform(GLint uniform, GLfloat value) {
    if (uniform != -1) {
        gl::UseProgram(program);
        gl::Uniform1f(uniform, value);
    }
}

void ShaderProgram::setUniform(GLint uniform, GLfloat a, GLfloat b) {
    if (uniform != -1) {
        gl::UseProgram(program);
        gl::Uniform2f(uniform, a, b);
    }
}

void ShaderProgram::setUniform(string uniform, GLint value) {
    GLint handle = gl::GetUniformLocation(program, uniform.c_str());
    if (handle == -1) {
        throw AppException("OpenGL", "Shader error", "Uniform \"" + uniform + "\" is not found in shader program");
    }
    gl::UseProgram(program);
    gl::Uniform1i(handle, value);
}

void ShaderProgram::setUniform(string uniform, GLfloat value) {
    GLint handle = gl::GetUniformLocation(program, uniform.c_str());
    if (handle == -1) {
        throw AppException("OpenGL", "Shader error", "Uniform \"" + uniform + "\" is not found in shader program");
    }
    gl::UseProgram(program);
    gl::Uniform1f(handle, value);
}

void ShaderProgram::setUniform(string uniform, GLfloat a, GLfloat b) {
    GLint handle = gl::GetUniformLocation(program, uniform.c_str());
    if (handle == -1) {
        throw AppException("OpenGL", "Shader error", "Uniform \"" + uniform + "\" is not found in shader program");
    }
    gl::UseProgram(program);
    gl::Uniform2f(handle, a, b);
}

}  // namespace mrm