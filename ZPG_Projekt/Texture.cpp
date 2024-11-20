#include "Texture.h"

Texture::Texture(const std::string filePath, GLenum texture_type, GLenum gl_texture, int gl_textureID) : texture_type(texture_type), gl_texture(gl_texture), gl_textureID(gl_textureID){

    glGenTextures(1, &ID);
    glActiveTexture(gl_texture);
    ID = SOIL_load_OGL_texture(filePath.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (ID == NULL) {
        printf("An error occurred while loading image.\n");
        exit(EXIT_FAILURE);
    }

}

Texture::Texture(const std::string& right, const std::string& left, const std::string& top,
    const std::string& bottom, const std::string& front, const std::string& back,
    GLenum texture_type, GLenum gl_texture, int gl_textureID)
    : texture_type(texture_type), gl_texture(gl_texture), gl_textureID(gl_textureID) {
    glGenTextures(1, &ID);
    glActiveTexture(gl_texture);
    glBindTexture(texture_type, ID);

    // Naètení každé strany cube mapy
    if (!SOIL_load_OGL_cubemap(
        right.c_str(), left.c_str(), top.c_str(), bottom.c_str(), front.c_str(), back.c_str(),
        SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS)) {
        printf("An error occurred while loading cube map textures.\n");
        exit(EXIT_FAILURE);
    }

    glBindTexture(texture_type, 0);
}

void Texture::bind() {
    glActiveTexture(gl_texture);
    glBindTexture(texture_type, ID);
}

void Texture::unbind() {
    glBindTexture(texture_type, 0);
}

GLuint Texture::getID() {
    return ID;
}

int Texture::getGl_textureID() {
    return gl_textureID;
}
