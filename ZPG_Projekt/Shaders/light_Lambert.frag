#version 330

#define MAX_LIGHTS 5
struct light
{
    vec4 position;
    vec4 diffuse;
    vec4 specular;
    vec4 ambient;
    vec3 attenuation;
    vec3 direction;
    float spotEffect;
    int lightType;
};

struct Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

in vec3 worldNormal;
in vec4 worldPosition;
in vec2 uvc;

uniform Material material;
uniform light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform vec3 cameraPosition;
uniform sampler2D textureUnitID;

out vec4 frag_colour;

void main() {
    
   frag_colour = vec4(0.1, 0.1, 0.1, 1.0); // global ambient

    for (int index = 0; index < numberOfLights; index++) 
    {

        vec3 lightDirection = vec3(lights[index].position) - vec3(worldPosition);
        float distance = length(lightDirection);
        vec3 lightVector = normalize(lightDirection);

        float attenuation;
        vec4 diffuse = vec4(0.0);
        float dot_product;

        switch (lights[index].lightType) {
            case 0: {
                // No lighting
            } break;

            case 1: {
                // Point light
                attenuation = 1.0 / (lights[index].attenuation.x + lights[index].attenuation.y * distance + lights[index].attenuation.z * distance * distance);
                dot_product = max(dot(lightVector, worldNormal), 0.0);
                diffuse = dot_product * lights[index].diffuse * material.diffuse * attenuation;

                frag_colour += diffuse;
            } break;

            case 2: {
                // Directional light

                lightVector = -normalize(lights[index].direction);
                dot_product = max(dot(worldNormal, lightVector), 0.0);
                diffuse = dot_product * lights[index].diffuse * material.diffuse;

                frag_colour += diffuse;
            } break;

            case 3: {
                // Spot light

                float spot = max(dot(-lightVector, normalize(lights[index].direction)), 0.0);
                attenuation = 1.0 / (lights[index].attenuation.x + lights[index].attenuation.y * distance + lights[index].attenuation.z * distance * distance);
                attenuation *= pow(spot, lights[index].spotEffect);

                dot_product = max(dot(lightVector, worldNormal), 0.0);
                diffuse = dot_product * lights[index].diffuse * material.diffuse * attenuation;

                if (spot < lights[index].spotEffect) {
                    diffuse = vec4(0.0);
                }
                
                if (lights[index].spotEffect >= 1.0) {
                    spot = 1.0;
                } else if (lights[index].spotEffect <= 0.0) {
                    spot = 0.0;
                } else {
                    spot = (spot - lights[index].spotEffect) / (1 - lights[index].spotEffect);
                }

                frag_colour += diffuse * spot;

            } break;
        }
    }

    frag_colour *= vec4(0.385, 0.647, 0.812, 1.0);
}