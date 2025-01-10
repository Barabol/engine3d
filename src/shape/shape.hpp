#ifndef __3D_SHAPE__
#define __3D_SHAPE__
#include "../core/material.hpp"
#include <glm/ext/matrix_float4x4.hpp>
class Cube {
 public:
   float vertices[48] = {-0.5f, 0.0f,  0.5f,  0.5f, 0.0f,  0.5f,  0.5f,  1.0f,
                         0.5f,  -0.5f, 1.0f,  0.5f, -0.5f, 1.0f,  -0.5f, 0.5f,
                         1.0f,  -0.5f, 0.5f,  0.0f, -0.5f, -0.5f, 0.0f,  -0.5f,
                         0.5f,  0.0f,  0.5f,  0.5f, 0.0f,  -0.5f, 0.5f,  1.0f,
                         -0.5f, 0.5f,  1.0f,  0.5f, -0.5f, 0.0f,  -0.5f, -0.5f,
                         0.0f,  0.5f,  -0.5f, 1.0f, 0.5f,  -0.5f, 1.0f,  -0.5f};

   float texcoords[32] = {0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0,
                          0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
                          0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0};

   unsigned char indices[24] = {0, 1, 2, 3, 4, 5, 6,  7,  3,  2,  5,  4,
                                7, 6, 1, 0, 8, 9, 10, 11, 12, 13, 14, 15};
   float normals[6][3] = {{0.0f, 0.0f, -1.0f}, //
                          {0.0f, 0.0f, 1.0f},  //
                          {-1.0f, 0.0f, 0.0f}, //
                          {1.0f, 0.0f, 0.0f},  //
                          {0.0f, -1.0f, 0.0f}, //
                          {0.0f, 1.0f, 0.0f}};
   float poz[3];
   double size;
   unsigned char colors[8][3];
   Cube(float poz[3]);
   Cube();
   void draw();
   void draw(const char *texturename);
   void setColors(unsigned char R, unsigned char G, unsigned char B);

   void translate(float tx, float ty, float tz);
   void rotate(float angle, float rx, float ry, float rz);
   void scale(float x);
   void resetTransform();

   Material material = Material();

 protected:
   glm::mat4 transformMatrix;
};
#endif
