#version 330
        layout(location = 0) in vec3 vp;
        layout(location = 1) in vec3 vn;

        uniform mat4 modelMatrix;
        uniform mat4 viewMatrix;
        uniform mat4 projectionMatrix;
        uniform mat3 normalMatrix;

        out vec3 ex_worldNormal;
        out vec4 ex_worldPosition;

        void main() {
        ex_worldPosition = modelMatrix * vec4(vp, 1.0);
        ex_worldNormal = normalMatrix * vn;
        gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(vp, 1.0);
        }