#ifndef __OBSERVER__
#define __OBSERVER__

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Observer {
 public:
   Observer();
   void updateLoc(float deltaX, float deltaY, float deltaZ);
   void updateCirc(float yaw, float pitch);
   void updatePosition(float deltaX, float deltaY, float deltaZ,
                       float deltaPitch, float deltaYaw);
   void setPosition(float deltaX, float deltaY, float deltaZ, float deltaPitch,
                    float deltaYaw);
   void transpose();

   glm::vec3 position;
   float pitch, yaw;
};

#endif
