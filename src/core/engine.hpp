#ifndef __3D_ENGINE__
#define __3D_ENGINE__

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdio>

/**
 * File name and location relative to main file
 * of log file
 */
#define LOG_FILE "./log.txt"

/**
 * @class Main class used for rendering
 */
class Engine {
 public:
   float deltaTime;
   unsigned targetTFP = 30;

   /**
    * Enum used for limiting user input
    * in setProjection method
    */
   typedef enum { PERSPECTIVE, ORTOGRAPHIC } PROJECTION;

   /**
    *	Method responsible for creating window
    *
    * @param width initial width of window
    *
    * @param height initial height of window
    *
    * @param name displayed name of window
    *
    */
   void initWindow(const unsigned width, const unsigned height,
                   const char *name);

   /**
    * Method used for logging errors to file
    *
    * @param msg message to log
    *
    * if set to NULL it will close file
    */
   void logError(const char *msg);

   /**
    * Method used for clearing screan to set color
    *
    * @param r: red saturation
    * @param g: blue saturation
    * @param b: green saturation
    */
   void clearToColor(const float r, const float g, const float b);

   /**
    *	Sets projection mode to chosen type
    *
    *	@param projection type of projection
    */
   void setProjection(const PROJECTION projection);

   /**
    * turns on full screan mode
    */
   void toggleFullScrean();

   /**
    * Virtual method responsible for screan updating
    *
    */
   virtual void draw();

 protected:
   /**
    *	Initial window size casted to double
    */
   double windowWidth, windowHeight;

 private:
};

#endif