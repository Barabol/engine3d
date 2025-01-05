#include "observer.hpp"

Observer::Observer() {
   position.x = 0;
   position.y = 0;
   position.z = 0;
   pitch = 0;
   yaw = 0;
}

void Observer::updatePosition(float deltaX, float deltaY, float deltaZ,
                              float deltaPitch, float deltaYaw) {
   position.x += deltaX;
   position.y += deltaY;
   position.z += deltaZ;

   pitch += deltaPitch;
   yaw += deltaYaw;
}
void Observer::setPosition(float deltaX, float deltaY, float deltaZ,
                           float deltaPitch, float deltaYaw) {
   position.x = deltaX;
   position.y = deltaY;
   position.z = deltaZ;

   pitch = deltaPitch;
   yaw = deltaYaw;
}

void Observer::transpose() {
   glm::mat4 view = glm::mat4(1.0f);
   view = glm::rotate(view, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
   view = glm::rotate(view, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
   view = glm::translate(view, -position);
   glLoadMatrixf(&view[0][0]);
}

void Observer::updateLoc(float deltaX, float deltaY, float deltaZ) {
   position.x += deltaX;
   position.y += deltaY;
   position.z += deltaZ;
}
void Observer::updateCirc(float yaw, float pitch) {
   this->pitch += pitch;
   this->yaw += yaw;

   if (this->yaw >= 360)
      this->yaw -= 360;

   if (this->pitch >= 360)
      this->pitch -= 360;

   if (this->yaw < 0)
      this->yaw += 360;

   if (this->pitch < 0)
      this->pitch += 360;
}
