#ifndef __3D_SHAPE_
#define __3D_SHAPE_
#include <glm/ext/matrix_float4x4.hpp>
class Cube {
 public:
   float normals[6][3] = {{0.0f, 0.0f, -1.0f}, //
                          {0.0f, 0.0f, 1.0f},  //
                          {-1.0f, 0.0f, 0.0f}, //
                          {1.0f, 0.0f, 0.0f},  //
                          {0.0f, -1.0f, 0.0f}, //
                          {0.0f, 1.0f, 0.0f}};

   float vertices[8][3] = {{0.0f, 0.0f, 0.0f}, //
                           {1.0f, 0.0f, 0.0f}, //
                           {1.0f, 1.0f, 0.0f}, //
                           {0.0f, 1.0f, 0.0f}, //
                           {0.0f, 0.0f, 1.0f}, //
                           {1.0f, 0.0f, 1.0f}, //
                           {1.0f, 1.0f, 1.0f}, //
                           {0.0f, 1.0f, 1.0f}};
   unsigned char indices[12][3] = {
       {0, 1, 3}, {1, 2, 3}, //
       {0, 4, 7}, {7, 3, 0}, //
       {4, 5, 6}, {6, 7, 4}, //
       {2, 1, 5}, {2, 6, 5}, //
       {3, 7, 6}, {6, 2, 3}, //
       {0, 1, 5}, {0, 4, 5}, //

   };
   float poz[3];
   double size;
   unsigned char colors[8][3];
   Cube(float poz[3]);
	Cube();
   void draw();
   void setColors(unsigned char R, unsigned char G, unsigned char B);

   void translate(float tx, float ty, float tz);
   void rotate(float angle, float rx, float ry, float rz);
   void scale(float x);
   void resetTransform();

 protected:
   glm::mat4 transformMatrix;
};
#endif
