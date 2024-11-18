#include "Model.h"
#include <iostream>

using namespace MyApp;

Model::Model(const float* vertices, int vertexCount, bool hasNormals, bool hasUV)
    : vertexCount(vertexCount)
{

    // Generate and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Initialize buffer data
    if(hasUV && hasNormals)
    {
        glBufferData(GL_ARRAY_BUFFER, vertexCount * 8 * sizeof(float), vertices, GL_STATIC_DRAW);

        // Set position attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
        // Set normal attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
        // Set texture attribute
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));
    }
    else if(hasNormals)
    {
        glBufferData(GL_ARRAY_BUFFER, vertexCount * 6 * sizeof(float), vertices, GL_STATIC_DRAW);

        // Set position attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
        // Set normal attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    }
    else if(hasUV)
    {
        glBufferData(GL_ARRAY_BUFFER, vertexCount * 5 * sizeof(float), vertices, GL_STATIC_DRAW);

        // Set position attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)0);
        // Set texture attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    }
    else
    {
        glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

        // Set position attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
    }


    // Unbind VAO and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}



GLuint Model::getVAO() {
    return this->VAO;
}

int Model::getVertexCount() {
    return this->vertexCount;
}

Model::~Model() {
    glDeleteBuffers(1, &VBO);
}
