#pragma once

#include <GL/glew.h>

namespace MyApp{
    class Model {
    public:
        Model(const float* vertices, int vertexCount, bool hasNormals);
        ~Model();

        GLuint getVAO();
        int getVertexCount();

    private:
        GLuint VBO;
        GLuint VAO;
        int vertexCount;
    };
}


