#ifndef __LIGHT__
#define __LIGHT__

#include <GL/gl.h>

class Light {
 public:
   GLuint lightId;
   GLfloat position[4];
   GLfloat ambient[4];
   GLfloat diffuse[4];
   GLfloat specular[4];

   Light(GLuint lightId);

   void setPosition(GLfloat x, GLfloat y, GLfloat z);
   void transpose(GLfloat x, GLfloat y, GLfloat z);
   void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
   void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
   void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
   void apply();
};

#endif
