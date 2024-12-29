#include "engine.hpp"
#include <GL/freeglut_std.h>
#include <GL/gl.h>

void reshapeHelper(int *w, int *h, int isInit) {
   static float *width;
   static float *height;
   if (isInit) {
      width = (float *)w;
      height = (float *)h;
      return;
   }
   *width = *w;
   *height = *h;
}
void changeSize(int w, int h) {
   glViewport(0, 0, w, h);
   reshapeHelper(&w, &h, 0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
   glMatrixMode(GL_MODELVIEW);
}

void relDraw(Engine *e) {
   static Engine *a = e;
   static int lastTime = 0;

   int time = glutGet(GLUT_ELAPSED_TIME);
   if (time - lastTime < (1000 / a->targetTFP))
      return;
   lastTime = time;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   a->deltaTime = (time - lastTime) / 1000.0f;
   glLoadIdentity();
   a->draw();
   glutSwapBuffers();
}

void display() { relDraw(nullptr); }

void Engine::initWindow(const unsigned width, const unsigned height,
                        const char *name) {

   this->windowWidth = width;
   this->windowHeight = height;
   reshapeHelper((int *)&windowWidth, (int *)&windowHeight, 1);

   int argv = 1;
   char argc[] = "app";
   char *a = argc;
   glutInit(&argv, &a);

   glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize(width, height);
   glutCreateWindow(name);

   relDraw(this);
   glutReshapeFunc(changeSize);
   glutDisplayFunc(display);
   glutIdleFunc(display);

   glMatrixMode(GL_MODELVIEW);
   glutMainLoop();
}

size_t len(const char *text) {
   size_t x = 0;
   for (; text[x]; x++)
      ;
   return x;
}
void Engine::logError(const char *msg) {
   static FILE *errorFile = fopen(LOG_FILE, "w+");
   static const size_t nlLen = len("\n");
   if (!errorFile) {
      fclose(errorFile);
      return;
   }
   fwrite(msg, sizeof(char), len(msg), errorFile);
   fwrite("\n", sizeof(char), nlLen, errorFile);
}

void Engine::clearToColor(const float r, const float g, const float b) {
   glClearColor(r, g, b, 1.0f);
}
void Engine::setProjection(const PROJECTION projection) {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   float aspect = (float)(windowWidth) / (float)(windowHeight);
   switch (projection) {
   case PERSPECTIVE:
      gluPerspective(45.0, windowWidth / windowHeight, 1.0, 100.0);
      break;
   case ORTOGRAPHIC:
      glOrtho(-aspect * 2, aspect * 2, -2, 2, -1, 100);
      break;
   }
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
void Engine::draw() {
   clearToColor(0, 0, 0);
   glTranslated(0, 0, -5);
   glutSolidTeapot(1);
}
void Engine::toggleFullScrean() {
   static int isFull = 0;
   if (isFull) {
      glutPositionWindow(0, 0);
      glutReshapeWindow(this->windowWidth, this->windowHeight);
      isFull = 0;
   } else {
      glutFullScreen();
      isFull = 1;
   }
}
