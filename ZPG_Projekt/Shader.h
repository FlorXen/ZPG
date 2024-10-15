#pragma once

#include <GL/glew.h>
#include <iostream>


class Shader {
public:
    Shader(GLenum shaderType, const char* shaderSource);
    void attachShader(GLuint shaderProgramID);
    ~Shader();

private:
    GLuint shaderID;
};
