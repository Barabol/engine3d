#include "engine.hpp"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <cstdio>
#include <string>
void projectionHolder(Engine *e, int w, int h) {
   static Engine *a = e;
   a->windowHeight = h;
   a->windowWidth = w;
   a->setProjection(a->projection);
}
void changeSize(int w, int h) {
   glViewport(0, 0, w, h);
   projectionHolder(nullptr, w, h);
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

   a->deltaTime = (time - lastTime);
   lastTime = time;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   a->setProjection(Engine::PROJECTION::PERSPECTIVE);
   a->draw();

   glLoadIdentity(); 
   a->setProjection(Engine::PROJECTION::ORTOGRAPHIC);
   glDisable(GL_DEPTH_TEST);
   a->renderHUD(std::to_string(a->score), a->lives);
   glEnable(GL_DEPTH_TEST);
   glutSwapBuffers();
}
void relInput(Engine *e, unsigned char c, int x, int y, int type) {
   static Engine *a = e;
   a->input(x, y, c, type);
}
void display() { relDraw(nullptr); }
void input_(unsigned char c, int x, int y) {
   relInput(nullptr, (int)c, x, y, 0);
}
void motion(int x, int y) { relInput(nullptr, 0, x, y, 1); }



void Engine::initWindow(const unsigned width, const unsigned height,
                        const char *name) {

   this->windowWidth = width;
   this->windowHeight = height;

   this->score = 0;
   this->lives = 8;

   int argv = 1;
   char argc[] = "app";
   char *a = argc;
   glutInit(&argv, &a);

   glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize(width, height);
   glutCreateWindow(name);

   relInput(this, 0, 0, 0, -1);
   relDraw(this);
   projectionHolder(this, width, height);

   glutReshapeFunc(changeSize);
   glutDisplayFunc(display);
   glutIdleFunc(display);

   glutKeyboardFunc(input_);
   glutPassiveMotionFunc(motion);

	glEnable(GL_DEPTH_TEST);

   mainCamera = new Observer();
   mainLight = new Light(GL_LIGHT0);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_COLOR_MATERIAL);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

   glMatrixMode(GL_MODELVIEW);
   this->preRender();
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
   this->projection = projection;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //float aspect = (float)(windowWidth) / (float)(windowHeight);
   //printf("%f,%f\n", windowWidth, windowHeight);
   switch (projection) {
   case PERSPECTIVE:
      gluPerspective(45.0, windowWidth / windowHeight, 1.0, 100.0);
      break;
   case ORTOGRAPHIC:
      glOrtho(0, windowWidth, windowHeight, 0, -1, 1);
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
void Engine::renderText(float x, float y, const char* text) {
    glRasterPos2f(x, y); // Ustawienie pozycji tekstu
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text); // Rysowanie każdego znaku
        text++;
    }
}
void Engine::renderHUD(const std::string &score, int lives){
   glDisable(GL_DEPTH_TEST);
   glColor3f(0.824, 0.706, 0.549); // Kolor tekstu i platformy o dziwo
    // Rysowanie prostokąta lub innych elementów HUD
   //glBegin(GL_QUADS);
   //   glVertex2i(20, 20);
   //   glVertex2i(220, 20);
   //   glVertex2i(220, 50);
   //   glVertex2i(20, 50);
   //glEnd();

// Rysowanie napisu z wynikiem
   renderText(30, 30, ("Score: " + score).c_str()); // Wyświetlenie wyniku
   renderText(30, 60, ("Lives: " + std::to_string(lives)).c_str()); // Wyświetlenie liczby żyć
   glEnable(GL_DEPTH_TEST);
}
void Engine::updateScore(int points) {
   score += points; // Dodaj punkty do wyniku
}

void Engine::decreaseLife() {
    if (lives > 0) {
        lives--; // Zmniejsz liczbę żyć
    }
}
void Engine::input(int x, int y, int c, int type) {}
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
void Engine::preRender() { puts("Start"); }
