#version 330
in vec3 ex_worldNormal;
in vec4 ex_worldPosition;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

out vec4 frag_colour;

void main() {
    float shininess = 32.0;
    vec3 lightColor = vec3(0.385, 0.647, 0.812);
    vec3 normal = normalize(ex_worldNormal);
    vec3 lightDir = normalize(lightPosition - vec3(ex_worldPosition));
    vec3 viewDir = normalize(viewPosition - vec3(ex_worldPosition));

    vec3 halfVector = normalize(lightDir + viewDir);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float spec = pow(max(dot(normal, halfVector), 0.0), shininess);
    vec3 specular = spec * lightColor;

    vec3 ambient = 0.1 * lightColor;

    vec3 result = ambient + diffuse + specular;
    frag_colour = vec4(result, 1.0) * vec4(0.385, 0.647, 0.812, 1.0);
}
