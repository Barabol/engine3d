#include "light.hpp"
#include <GL/gl.h>

Light::Light(GLuint lightId) {
   this->lightId = lightId;

   // Domyślne ustawienia światła
   position[0] = 3.0f;
   position[1] = 0.2f;
   position[2] = 3.0f;
   position[3] = 0.5f;

   ambient[0] = .2f;
   ambient[1] = .2f;
   ambient[2] = .2f;
   ambient[3] = 1.0f;

   diffuse[0] = 1.0f;
   diffuse[1] = 1.0f;
   diffuse[2] = 1.0f;
   diffuse[3] = 1.0f;

   specular[0] = 1.0f;
   specular[1] = 1.0f;
   specular[2] = 1.0f;
   specular[3] = 1.0f;
}

void Light::setPosition(GLfloat x, GLfloat y, GLfloat z) {
   position[0] = x;
   position[1] = y;
   position[2] = z;
}
void Light::transpose(GLfloat x, GLfloat y, GLfloat z) {
   position[0] += x;
   position[1] += y;
   position[2] += z;
}

void Light::setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
   ambient[0] = r;
   ambient[1] = g;
   ambient[2] = b;
   ambient[3] = a;
}

void Light::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
   diffuse[0] = r;
   diffuse[1] = g;
   diffuse[2] = b;
   diffuse[3] = a;
}

void Light::setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
   specular[0] = r;
   specular[1] = g;
   specular[2] = b;
   specular[3] = a;
}

void Light::apply() {
   glLightfv(lightId, GL_POSITION, position);
   glLightf(lightId, GL_CONSTANT_ATTENUATION, 1.0);
   glLightf(lightId, GL_LINEAR_ATTENUATION, 1.0);
   glLightf(lightId, GL_QUADRATIC_ATTENUATION, 1.0);
   glLightfv(lightId, GL_AMBIENT, ambient);
   glLightfv(lightId, GL_DIFFUSE, diffuse);
   glLightfv(lightId, GL_SPECULAR, specular);
}
