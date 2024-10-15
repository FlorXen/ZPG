#include "Shader.h"
#include "ShaderProgram.h"

Shader::Shader(GLenum shaderType, const char* shaderSource) {
	// Create and compile shader
	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderSource, nullptr);
	glCompileShader(shaderID);

	// Check for compilation errors
	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		std::cerr << "ERROR: Shader Compilation Failed\n" << infoLog << std::endl;
	}
}

void Shader::attachShader(GLuint shaderProgramID) {
	glAttachShader(shaderProgramID, shaderID);
}

Shader::~Shader() {
	glDeleteShader(shaderID);
}
