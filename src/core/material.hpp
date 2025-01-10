#ifndef __MATERIAL__
#define __MATERIAL__

#include <GL/gl.h>

class Material {
 public:
   float ambient[4];
   float diffuse[4];
   float specular[4];
   float shininess;

   Material();

   void setAmbient(float r, float g, float b, float a);
   void setDiffuse(float r, float g, float b, float a);
   void setSpecular(float r, float g, float b, float a);
   void setShininess(float shininess);
   void apply();
};

#endif
