#ifndef __3D_SHAPE__
#define __3D_SHAPE__
#include "../core/material.hpp"
#include <glm/ext/matrix_float4x4.hpp>
class Plane {
 public:
   Plane(float scale);
   Material material;
   float vertices[12] = {-1, 0, 2, 1, 0, 2, 1, 0, -30, -1, 0, -30};
   unsigned char indices[4] = {0, 1, 2, 3};
   float normals[6] = {0, 1, 0, 0, -1, 0};
   unsigned char colors[3];
   void setColors(unsigned char R, unsigned char G, unsigned char B);
   void draw();
};
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

   Material material[6] = {Material()};

 protected:
   glm::mat4 transformMatrix;
};
class Rect : public Cube {
 public:
   void makeRect(float xScale, float yScale);
};

class Skybox{
 public:
 GLfloat vertices[24] = {
    // Positions for the cube vertices
    -1.0f,  1.0f, -1.0f, // Front Top Left
     1.0f,  1.0f, -1.0f, // Front Top Right
     1.0f, -1.0f, -1.0f, // Front Bottom Right
    -1.0f, -1.0f, -1.0f, // Front Bottom Left
    -1.0f,  1.0f,  1.0f, // Back Top Left
     1.0f,  1.0f,  1.0f, // Back Top Right
     1.0f, -1.0f,  1.0f, // Back Bottom Right
    -1.0f, -1.0f,  1.0f  // Back Bottom Left
};
GLuint indices[36] = {
    // Front face
    0, 1, 2,
    2, 3, 0,
    // Back face
    4, 5, 6,
    6, 7, 4,
    // Left face
    0, 3, 7,
    7, 4, 0,
    // Right face
    1, 5, 6,
    6, 2, 1,
    // Top face
    0, 4, 5,
    5, 1, 0,
    // Bottom face
    3, 2, 6,
    6, 7, 3
};
GLuint textures[6];
void drawSkybox();
};

#endif
