#pragma once

//Include GLEW
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>
//Include SOIL 
#include <SOIL.h>

#include <string>

class Texture
{
public:
	Texture(const std::string filePath, GLenum texture_type, GLenum gl_texture, int gl_textureID);
	Texture(const std::string& right, const std::string& left, const std::string& top,
		const std::string& bottom, const std::string& front, const std::string& back,
		GLenum texture_type, GLenum gl_texture, int gl_textureID);

	void bind();
	void unbind();
	GLuint getID();
	int getGl_textureID();

private:
	GLuint ID;
	GLenum gl_texture;
	int gl_textureID;
	GLenum texture_type;


};

