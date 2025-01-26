#include "./src/core/engine.hpp"
#include "src/shape/shape.hpp"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <cstdio>
#define LOCS 4
class engine : public Engine {
   float locs[LOCS][2] = {{-1.7, 0}, {-.6, 0.5}, {.6, 1}, {1.7, 1.5}};
   Cube v = Cube();
   Plane p = Plane(2.5);
   Rect r = Rect();
   void draw() override {
      mainCamera->transpose();

      p.draw();
      for (int x = 0; x < LOCS; x++) {
         glTranslatef(locs[x][0], 0, locs[x][1]);
         v.draw();
         glTranslatef(locs[x][0] * -1, 0, locs[x][1] * -1);
      }
   }
   void preRender() override {
      glEnable(GL_DEPTH_TEST);
      mainCamera->pitch = 30;
      mainCamera->updateLoc(0, 5, 9);
      r.makeRect(5, 0.2);
      // toggleFullScrean();
   }
   void input(int x, int y, int c, int type) override {
      static int lastMx, lastMy;
      float offset;
      float dirs[2];
      float dirz[2];
      switch (type) {
      case KEYBOARD:
         offset = mainCamera->yaw / 180;

         switch (c) {
         case 'w':
						locs[0][0]+=1;
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
            mainCamera->updateLoc(0, 1, 0);
            break;
         case 'z':
            mainCamera->updateLoc(0, -1, 0);
            break;
         case 'v':
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
         printf("? %f\n", mainCamera->pitch);
         break;
      }
   }
} e;
int main() { e.initWindow(800, 600, "test"); }
