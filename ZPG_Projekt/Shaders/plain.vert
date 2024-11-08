#version 330
        layout(location = 0) in vec3 vp;
        layout(location = 1) in vec3 vn;

        uniform mat4 modelMatrix;
        uniform mat4 viewMatrix;
        uniform mat4 projectionMatrix;
        uniform mat3 normalMatrix;

        out vec3 worldNormal;
        out vec4 worldPosition;

        void main() {
            worldPosition = modelMatrix * vec4(vp, 1.0);
            worldNormal= normalize(transpose(inverse(mat3(modelMatrix))) * vn);
            gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(vp, 1.0);
        }