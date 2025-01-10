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
      c.draw("./texture.png");
      // c.draw();
      // c.rotate(.1 * deltaTime, 0, 1, 0);
      //   c.rotate(0.5 * deltaTime, 1, 0, 1);
      //   c.translate(-0.001*deltaTime, 0, 0);
      //
      //   mainLight->transpose(0.2 * deltaTime, .2 * deltaTime, .2 *
      //   deltaTime);
      //

      // mainLight->apply();
   }
   void preRender() override {

      // glutSetCursor(GLUT_CURSOR_NONE);
      //  setProjection(ORTOGRAPHIC)//;
      c.translate(0, -1, -5);
      // c.material.setAmbient(1, 1, 1, .1);
      // c.material.setShininess(5);
      // c.material.setDiffuse(0, 0, 0, 0);
      // c.material.setSpecular(1, 0, 0, 1);

      // mainLight->setPosition(0, 0, 0);
      // mainLight->setAmbient(1, 1, 1, 1);
      // mainLight->setSpecular(1, 1, 1, 1);
      // mainLight->setDiffuse(1, 1, 1, 1);
      glShadeModel(GL_SMOOTH);
      glEnable(GL_DEPTH_TEST);
      // toggleFullScrean();
   }
   void input(int x, int y, int c, int type) override {
      static int lastMx, lastMy;
      float offset;
      float dirs[2];
      float dirz[2];
      switch (type) {
      case KEYBOARD:
         // dodać transformacje ruchu na podstawie obrotu kamery
         //
         offset = mainCamera->yaw / 180;

         switch (c) {
         case 'w':
            dirs[0] = -0.002;
            break;
         case 'a':
            dirs[1] = -0.002;
            break;
         case 's':
            dirs[0] = 0.002;
            break;
         case 'd':
            dirs[1] = 0.002;
            break;
         case 'x':
            mainCamera->updateCirc(10, 0);
            break;
         case 'z':
            mainCamera->updateCirc(-10, 0);
            break;
         case 'v':

            this->c.rotate(.1 * deltaTime, 0, 1, 0);
            break;
         }
         dirz[0] = dirs[0];
         dirz[1] = dirs[1];

         dirz[0] *= offset - 1;
         dirz[1] *= 1 - offset - 1;
         dirz[0] += dirs[1] * (1 - offset - 1);
         dirz[1] += dirs[0] * (offset - 1);
         printf("> %f*\n|%f\n|%f\n\n|%f\n|%f\n\n", mainCamera->yaw, offset - 1,
                1 - offset - 1, dirz[1], dirz[0]);

         mainCamera->updateLoc(dirs[1] * deltaTime, 0, dirs[0] * deltaTime);
         break;
      case MOUSE_MOVEMENT:
         if (x == lastMx && y == lastMy)
            return;
         offset = mainCamera->yaw / 360;
         printf("> %f\n", offset);
         mainCamera->updateCirc(.002 * deltaTime * (x - lastMx),
                                .002 * deltaTime * (y - lastMy));

         //glutWarpPointer(lastMx, lastMy);
         lastMy = y;
         lastMx = x;

         break;
      }
   }
} e;
int main() { e.initWindow(800, 600, "test"); }
