#version 330

#define MAX_LIGHTS 5
struct light
{
    vec4 position;
    vec4 diffuse_colour;
    vec4 specular;
    vec3 attenuation;
    vec3 direction;
    float spotEffect;
    int lightType;
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

    for (int index = 0; index < numberOfLights; index++) 
    {
        vec3 lightDirection = vec3(lights[index].position) - vec3(worldPosition);
        vec3 camVector = normalize(cameraPosition - vec3(worldPosition));
        float distance = length(lightDirection);
        vec3 lightVector = normalize(lightDirection);
        vec3 reflectVector = reflect(-camVector, worldNormal);
        float specularFactor = pow(max(dot(reflectVector, lightVector), 0.0), shininess);

        float attenuation;
        float dot_product = max(dot(lightVector, worldNormal), 0.0);
        vec4 diffuse = vec4(0.0);
        vec4 specularReflection = vec4(0.0);

        switch (lights[index].lightType) {
            case 0: {
                // No lighting
            } break;

            case 1: {
                // Point light
                attenuation = 1.0 / (lights[index].attenuation.x + lights[index].attenuation.y * distance + lights[index].attenuation.z * distance * distance);
                diffuse = dot_product * lights[index].diffuse_colour * attenuation;
                
                if (dot(lightVector, worldNormal) > 0.0) {
                    specularReflection = specularFactor * lights[index].specular * attenuation;
                }

                frag_colour += diffuse + specularReflection;
            } break;

            case 2: {
                // Directional light

                lightVector = -normalize(lights[index].direction);
                dot_product = max(dot(worldNormal, lightVector), 0.0);
                diffuse = dot_product * lights[index].diffuse_colour;

                if (dot(lightVector, worldNormal) > 0.0) {
                    reflectVector = reflect(-camVector, worldNormal);
                    specularFactor = pow(max(dot(reflectVector, lightVector), 0.0), shininess);
                    specularReflection = specularFactor * lights[index].specular;
                }

                frag_colour += diffuse + specularReflection;
            } break;

            case 3: {
                // Spot light

                float spot = max(dot(-lightVector, normalize(lights[index].direction)), 0.0);
                attenuation = 1.0 / (lights[index].attenuation.x + lights[index].attenuation.y * distance + lights[index].attenuation.z * distance * distance);
                attenuation *= pow(spot, lights[index].spotEffect);

                diffuse = dot_product * lights[index].diffuse_colour * attenuation;

                if (spot < lights[index].spotEffect) {
                    specularReflection = vec4(0.0);
                    diffuse = vec4(0.0);
                } else {
                    if (dot(lightVector, worldNormal) > 0.0) {
                        specularReflection = specularFactor * lights[index].specular * attenuation;
                    }
                }
                
                if (lights[index].spotEffect >= 1.0) {
                    spot = 1.0;
                } else if (lights[index].spotEffect <= 0.0) {
                    spot = 0.0;
                } else {
                    spot = (spot - lights[index].spotEffect) / (1 - lights[index].spotEffect);
                }

                frag_colour += (diffuse + specularReflection) * spot;

            } break;
        }
    }

    frag_colour *= vec4(0.75, 0.26, 0.26, 1.0);
    
}