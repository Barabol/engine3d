#include "material.hpp"
#include <GL/gl.h>

Material::Material() {
   ambient[0] = 0.2f;
   ambient[1] = 0.2f;
   ambient[2] = 0.2f;
   ambient[3] = 1.0f;

   diffuse[0] = 0.8f;
   diffuse[1] = 0.8f;
   diffuse[2] = 0.8f;
   diffuse[3] = 1.0f;

   specular[0] = 1.0f;
   specular[1] = 1.0f;
   specular[2] = 1.0f;
   specular[3] = 1.0f;

   shininess = 32.0f;
}

void Material::setAmbient(float r, float g, float b, float a) {
   ambient[0] = r;
   ambient[1] = g;
   ambient[2] = b;
   ambient[3] = a;
}

void Material::setDiffuse(float r, float g, float b, float a) {
   diffuse[0] = r;
   diffuse[1] = g;
   diffuse[2] = b;
   diffuse[3] = a;
}

void Material::setSpecular(float r, float g, float b, float a) {
   specular[0] = r;
   specular[1] = g;
   specular[2] = b;
   specular[3] = a;
}

void Material::setShininess(float shininess) { this->shininess = shininess; }

void Material::apply() {
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}
