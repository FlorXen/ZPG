#version 330
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

out vec3 worldNormal;
out vec4 worldPosition;
out vec2 uvc;
    
void main () {
    worldPosition = modelMatrix * vec4(vp, 1.0);
    worldNormal= normalize(transpose(inverse(mat3(modelMatrix))) * vn);
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(vp, 1.0);
    uvc=uv;
};