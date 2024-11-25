#include "Texture.h"

Texture::Texture(const std::string filePath, GLenum texture_type, int textureUnit) : texture_type(texture_type), textureUnit(textureUnit){

    glActiveTexture(GL_TEXTURE0 + textureUnit);
    ID = SOIL_load_OGL_texture(filePath.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (ID == NULL) {
        printf("An error occurred while loading image.\n");
        exit(EXIT_FAILURE);
    }

    glBindTexture(texture_type, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glActiveTexture(GL_TEXTURE0);

}

Texture::Texture(const std::string& right, const std::string& left, const std::string& top,
    const std::string& bottom, const std::string& front, const std::string& back,
    GLenum texture_type, int textureUnit) : texture_type(texture_type), textureUnit(textureUnit) {

    glActiveTexture(GL_TEXTURE0 + textureUnit);
    ID = SOIL_load_OGL_cubemap(
        right.c_str(), left.c_str(), top.c_str(), bottom.c_str(), front.c_str(), back.c_str(),
        SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

    if (ID == NULL) {
        printf("An error occurred while loading cube map textures.\n");
        exit(EXIT_FAILURE);
    }

    glBindTexture(texture_type, ID);

    glActiveTexture(GL_TEXTURE0);
}

void Texture::activate() {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
}

void Texture::deactivate() {
    glActiveTexture(GL_TEXTURE0);
}

GLuint Texture::getID() {
    return ID;
}

int Texture::getTextureUnit() {
    return textureUnit;
}
