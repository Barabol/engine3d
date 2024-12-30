#include "shape.hpp"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <cstdio>
#include <cstdlib>
#include <glm/gtc/type_ptr.hpp>
Cube::Cube(float poz[3]) {
   for (int x = 0; x < 3; x++)
      this->poz[x] = poz[x];

   setColors(rand() % 256, rand() % 256, rand() % 256);
   transformMatrix = glm::mat4(1.0f);
}
Cube::Cube() {
   for (int x = 0; x < 3; x++)
      this->poz[x] = 0;

   setColors(rand() % 256, rand() % 256, rand() % 256);
   transformMatrix = glm::mat4(1.0f);
}

void Cube::setColors(unsigned char R, unsigned char G, unsigned char B) {
   for (int x = 0; x < 8; x++) {
      this->colors[x][0] = R;
      this->colors[x][1] = G;
      this->colors[x][2] = B;
   }
}
void Cube::draw() {
   glPushMatrix();
   glMultMatrixf(glm::value_ptr(transformMatrix));

   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, vertices);

   glEnableClientState(GL_NORMAL_ARRAY);
   glNormalPointer(3, GL_FLOAT, normals);

   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

   glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_BYTE, indices);

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
