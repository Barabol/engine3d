#include "shape.hpp"
#include "stb_image.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <cstdio>
#include <cstdlib>
#include <glm/gtc/type_ptr.hpp>
Cube::Cube(float poz[3]) {
   for (int x = 0; x < 3; x++)
      this->poz[x] = poz[x];

   transformMatrix = glm::mat4(1.0f);
}
Cube::Cube() {
   for (int x = 0; x < 3; x++)
      this->poz[x] = 0;
   setColors(rand() % 256, rand() % 256, rand() % 256);
   transformMatrix = glm::mat4(1.0f);
   material.setAmbient(0.2f, 0.2f, 0.2f, 1.0f);
   material.setDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
   material.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
   material.setShininess(32.0f);
}

void Cube::setColors(unsigned char R, unsigned char G, unsigned char B) {
   for (int x = 0; x < 8; x++) {
      this->colors[x][0] = R;
      this->colors[x][1] = G;
      this->colors[x][2] = B;
   }
}
GLuint loadTexture(const char *filename) {
   int width, height, nrChannels;
   unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
   if (!data) {
      printf("unable to load texture: %s\n", filename);
      return 0;
   }

   GLuint textureID;
   glGenTextures(1, &textureID);
   glBindTexture(GL_TEXTURE_2D, textureID);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   if (nrChannels == 3) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
   } else if (nrChannels == 4) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, data);
   }

   stbi_image_free(data);
   return textureID;
}
void Cube::draw(const char *texturename) {
   GLuint texture = loadTexture(texturename);
   glPushMatrix();
   glMultMatrixf(glm::value_ptr(transformMatrix));
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texture);

   glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   glEnableClientState(GL_VERTEX_ARRAY);

   glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
   glVertexPointer(3, GL_FLOAT, 0, vertices);
   for (int x = 0; x < 6; x++) {
      material.apply();
      glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &indices[x << 2]);
   }
   glDisableClientState(GL_VERTEX_ARRAY);
   // glDisableClientState(GL_COLOR_ARRAY);
   glDisable(GL_TEXTURE_2D);
}
void Cube::draw() {
   material.apply();
   glMultMatrixf(glm::value_ptr(transformMatrix));

   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, vertices);

   glEnableClientState(GL_NORMAL_ARRAY);
   glNormalPointer(3, GL_FLOAT, normals);

   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

   glDrawElements(GL_QUADS, sizeof(indices), GL_UNSIGNED_BYTE, indices);

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);

   glPopMatrix();
}

void Cube::translate(float tx, float ty, float tz) {
   poz[0] += tx;
   poz[1] += ty;
   poz[2] += tz;
   transformMatrix = glm::translate(transformMatrix, glm::vec3(tx, ty, tz));
}

void Cube::rotate(float angle, float rx, float ry, float rz) {
   transformMatrix =
       glm::rotate(transformMatrix, glm::radians(angle), glm::vec3(rx, ry, rz));
}

void Cube::scale(float x) {
   transformMatrix = glm::scale(transformMatrix, glm::vec3(x, x, x));
}

void Cube::resetTransform() {
   transformMatrix = glm::mat4(1.0f);
   transformMatrix =
       glm::translate(transformMatrix, glm::vec3(-0.3f, -0.1f, -5.0f));
   transformMatrix = glm::rotate(transformMatrix, glm::radians(29.0f),
                                 glm::vec3(1.0f, 0.0f, 0.0f));
   transformMatrix = glm::rotate(transformMatrix, glm::radians(-26.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));
}
