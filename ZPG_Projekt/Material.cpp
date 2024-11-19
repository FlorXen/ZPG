#include "Material.h"

Material::Material(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& light_specular, float shininess)
    : ra(ambient), rd(diffuse), rs(light_specular), shininess(shininess) {}

glm::vec4 Material::getAmbient() const {
    return ra;
}

glm::vec4 Material::getDiffuse() const {
    return rd;
}

glm::vec4 Material::getSpecular() const {
    return rs;
}

float Material::getShininess() const {
    return shininess;
}


void Material::setAmbient(const glm::vec4& ambient) {
    ra = ambient;
}

void Material::setDiffuse(const glm::vec4& diffuse) {
    rd = diffuse;
}

void Material::setSpecular(const glm::vec4& light_specular) {
    rs = light_specular;
}

void Material::setShininess(float shininess) {
    this->shininess = shininess;
}
