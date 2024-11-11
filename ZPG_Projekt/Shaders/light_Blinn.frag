#version 330

#define MAX_LIGHTS 5
struct light
{
    vec4 position;
    vec4 diffuse_colour;
    vec4 specular;
    vec3 attenuation;
};

in vec3 worldNormal;
in vec4 worldPosition;

uniform light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform vec3 cameraPosition;

out vec4 frag_colour;

void main() {
    
    float shininess = 32.0;
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    frag_colour = ambient;

    for (int index = 0; index < numberOfLights; index++) // for all light sources
    {
        vec3 lightDirection = vec3(lights[index].position) - vec3(worldPosition);
        float distance = length(lightDirection);
        vec3 lightVector = normalize(lightDirection);

        float attenuation = 1.0 / (lights[index].attenuation.x + lights[index].attenuation.y * distance + lights[index].attenuation.z * distance * distance);

        float dot_product = max(dot(lightVector, worldNormal), 0.0);
        vec4 diffuse = dot_product * lights[index].diffuse_colour * attenuation;

        vec4 specularReflection = vec4(0.0);
        if (dot(lightVector, worldNormal) > 0.0) {
            vec3 viewDirection = normalize(cameraPosition - vec3(worldPosition));
            vec3 halfVector = normalize(lightVector + viewDirection);

            float specularFactor = pow(max(dot(halfVector, worldNormal), 0.0), shininess);
            specularReflection = specularFactor * lights[index].specular * attenuation;
        }

        frag_colour += diffuse + specularReflection;
    }

    frag_colour *= vec4(0.385, 0.647, 0.812, 1.0);
}
