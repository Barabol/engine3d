#include "./src/core/engine.hpp"
#include "src/shape/shape.hpp"
class engine : public Engine {
   Cube c = Cube();
   void draw() override {
      glTranslated(0, 0, -5);
      glutWireCube(1);
      c.draw();
      c.rotate(2 * deltaTime, 0, 1, 0);
      // c.rotate(0.5 * deltaTime, 1, 0, 1);
      // c.translate(-0.001*deltaTime, 0, 0);
      //
   }
   void preRender() override {

      //setProjection(ORTOGRAPHIC);
      c.translate(0, -1, -5);
      // toggleFullScrean();
   }
} e;
int main() { e.initWindow(800, 600, "test"); }
