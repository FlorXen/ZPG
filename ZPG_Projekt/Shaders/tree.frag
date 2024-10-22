#version 330
        in vec3 fragNormal;
        in vec3 fragPos;

        out vec4 frag_colour;

        void main () {
        frag_colour = vec4(fragNormal, 1.0);
        }