#pragma once

#include <GL/glew.h>

namespace MyApp{
    class Model {
    public:
        Model();
        Model(const float* vertices, int vertexCount, bool hasNormals, bool hasUV);
        ~Model();

        GLuint getVAO();
        int getVertexCount();
        int getIndicesCount();

    protected:
        GLuint VBO;
        GLuint VAO;
        int vertexCount;
        int indicesCount;
    };
}


