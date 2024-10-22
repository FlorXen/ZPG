#version 330
        in vec3 ex_worldNormal;
        in vec4 ex_worldPosition;

        out vec4 frag_colour;

        void main() {
        vec3 lightPosition = vec3(0.0, 0.2, 0.0);
        vec3 lightVector = normalize(lightPosition - vec3(ex_worldPosition));

        float dot_product = max(dot(lightVector, normalize(ex_worldNormal)), 0.0);
        vec4 diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);
        vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

        frag_colour =  vec4(0.75, 0.26, 0.26, 1.0) * (ambient + diffuse);
        }