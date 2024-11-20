#version 330

layout(location = 0) in vec3 vp;

uniform mat4 modelMatrix;

out vec3 fragmentLocalPosition;

void main () {
	
	 gl_Position = modelMatrix * vec4(vp, 1.0);
	 fragmentLocalPosition = vp;
}