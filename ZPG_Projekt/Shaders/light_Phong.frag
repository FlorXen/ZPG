#version 330
in vec3 ex_worldNormal;
in vec4 ex_worldPosition;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

out vec4 frag_colour;

void main() {
    float shininess = 32.0;
    vec3 lightVector = normalize(lightPosition - vec3(ex_worldPosition));
    vec3 viewVector = normalize(viewPosition - vec3(ex_worldPosition));
    vec3 reflectVector = reflect(-lightVector, normalize(ex_worldNormal));

    float diffuseStrength = max(dot(lightVector, normalize(ex_worldNormal)), 0.0);
    vec4 diffuse = diffuseStrength * vec4(0.385, 0.647, 0.812, 1.0);

    float specularStrength = pow(max(dot(viewVector, reflectVector), 0.0), shininess);
    vec4 specular = specularStrength * vec4(1.0);

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    frag_colour = (ambient + diffuse + specular) * vec4(0.385, 0.647, 0.812, 1.0);
}