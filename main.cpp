#include "./src/core/engine.hpp"
#include "src/shape/shape.hpp"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <cstdio>
class engine : public Engine {
   Cube c = Cube();
   void draw() override {
      mainCamera->transpose();
      glutSolidCube(1);
      c.draw();
      glTranslated(0, 1, 0.2);
      c.draw();
      // c.rotate(.1 * deltaTime, 0, 1, 0);
      //  c.rotate(0.5 * deltaTime, 1, 0, 1);
      //  c.translate(-0.001*deltaTime, 0, 0);
      //
      //  mainLight->transpose(0.2 * deltaTime, .2 * deltaTime, .2 * deltaTime);
      //

      // mainLight->apply();
   }
   void preRender() override {

      // glutSetCursor(GLUT_CURSOR_NONE);
      //  setProjection(ORTOGRAPHIC)//;
      c.translate(0, -1, -5);
      c.material.setAmbient(1, 1, 1, .1);
      c.material.setShininess(5);
      c.material.setDiffuse(0, 0, 0, 0);
      c.material.setSpecular(1, 0, 0, 1);

      mainLight->setPosition(0, 0, 0);
      mainLight->setAmbient(.5, .5, .5, 1);
      mainLight->setSpecular(.1, .1, .1, .0);
      mainLight->setDiffuse(.2, .2, .2, 1);
      glShadeModel(GL_SMOOTH);
      // toggleFullScrean();
   }
   void input(int x, int y, int c, int type) override {
      static int lastMx, lastMy;
      float offset;
      switch (type) {
      case KEYBOARD:
         // dodać transformacje ruchu na podstawie obrotu kamery
         //
         offset = mainCamera->yaw / 360;
         printf("%f\n", mainCamera->yaw);
         printf("> %f|%f\n", offset, 1 - offset);

         switch (c) {
         case 'w':
            mainCamera->updateLoc((offset) * (-.002 * deltaTime), 0,
                                  (1 - offset) * (-.002 * deltaTime));
            break;
         case 'a':
            mainCamera->updateLoc(-.002 * deltaTime, 0, 0);
            break;
         case 's':
            mainCamera->updateLoc(0, 0, .002 * deltaTime);
            break;
         case 'd':
            mainCamera->updateLoc(.002 * deltaTime, 0, 0);
            break;
         case 'x':
            mainCamera->updateCirc(10, 0);
            break;
         case 'z':
            mainCamera->updateCirc(-10, 0);
            break;
         }

         break;
      case MOUSE_MOVEMENT:
         if (x == lastMx && y == lastMy)
            return;
         offset = mainCamera->yaw / 360;
         printf("> %f\n", offset);
         mainCamera->updateCirc(.002 * deltaTime * (x - lastMx),
                                .002 * deltaTime * (y - lastMy));
         lastMy = y;
         lastMx = x;

         // glutWarpPointer(windowWidth / 2, windowHeight / 2);
         break;
      }
   }
} e;
int main() { e.initWindow(800, 600, "test"); }
