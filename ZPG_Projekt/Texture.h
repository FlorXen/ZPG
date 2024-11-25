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
	Texture(const std::string filePath, GLenum texture_type, int textureUnit);
	Texture(const std::string& right, const std::string& left, const std::string& top,
		const std::string& bottom, const std::string& front, const std::string& back,
		GLenum texture_type, int textureUnit);
	void activate();
	void deactivate();

	GLuint getID();
	int getTextureUnit();

private:
	GLuint ID;
	int textureUnit;
	GLenum texture_type;


};

