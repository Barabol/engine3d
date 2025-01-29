#include "./src/core/engine.hpp"
#include "src/shape/shape.hpp"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <array>
#include <cstdlib>
#define LOCS 5

class engine : public Engine {
   float locs[LOCS][2] = {{-2, -70}, {-1, -70}, {0, -70}, {1, -70}, {2, -70}};
   std::vector<std::array<float, 2>> cubes;
   std::vector<std::array<int, 3>> cubes_colours;
   int ladne_kolory[4][3] = {{255,181,0},
                             {255, 218, 19},
                             {95, 124, 161},
                             {39, 53, 80}};
   float player_axis[3] = {0,0,4}; // x,y,z
   float cubes_speed = 0.4;
   int life = 8;
   int score = 0;
   Cube v = Cube();
   Cube player = Cube();
   Plane p = Plane(2.5);
   Rect r = Rect();
   int cubes_gap_counter = 0;
   void cubes_move(){
      for(int x = 0; x<LOCS; x++){
         locs[x][1] += cubes_speed;
      }
      for(int x = 0; x<cubes.size(); x++){
         cubes[x][1] += cubes_speed;
      }
   }

   void remove_cube(){
      if(cubes[0][1]>=4 && cubes[0][1]<=5 && cubes[0][0] == player_axis[0]){
         cubes.erase(cubes.begin());
         cubes_colours.erase(cubes_colours.begin());
         updateScore(25);
         score += 25;
         //printf("dziala\n");
      }   
      if(cubes[0][1]>6){
         cubes.erase(cubes.begin());
         cubes_colours.erase(cubes_colours.begin());
         decreaseLife();
         life -= 1;
         if(life==0){
            printf("Twoj wynik: %d", score);
            exit(0);
         }
         
      }
   }

   void draw() override {
      //printf("%d\n", cubes_gap_counter);
      if(cubes_gap_counter==0){
         float row = rand()%5-2;
         cubes.push_back({row,-70});
         cubes_gap_counter = -20;

         int colour = rand()%4;
         cubes_colours.push_back({ladne_kolory[colour][0],ladne_kolory[colour][1], ladne_kolory[colour][2]});
      }
      cubes_gap_counter++;
      mainCamera->transpose();
      p.draw();

      
      // MUR - niedokonczony 
      //for (int x = 0; x < LOCS; x++) {
      //   glTranslatef(locs[x][0], 0, locs[x][1]);
      //   v.draw();
      //   glTranslatef(locs[x][0] * -1, 0, locs[x][1] * -1);
      //}

      for(int x = 0; x<cubes.size(); x++){
         glTranslatef(cubes[x][0], 0, cubes[x][1]);
         v.setColors(cubes_colours[x][0], cubes_colours[x][1], cubes_colours[x][2]);
         v.draw();
         glTranslatef(cubes[x][0] * -1, 0, cubes[x][1] * -1);
      }
      

      glTranslatef(player_axis[0],player_axis[1],player_axis[2]);
      player.draw();
      //locs[1][1] += cubes_speed;
      cubes_move();
      for(int x = 0; x < LOCS; x++){
         if(locs[x][1] > 6){
            locs[x][1] = -70;
         }
      }
      remove_cube();
      
      //v.draw("texture.png");
   }
   void preRender() override {
      //p.setColors(0,255,0);
      player.setColors(255,0,0);
      glEnable(GL_DEPTH_TEST);
      mainCamera->pitch = 25;
      mainCamera->updateLoc(0, 6, 10);
      r.makeRect(5, 0.2);
      //locs[0][1] += 3;
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
				dirs[0] = -0.002;
            break;
         case 'a':
            //dirs[1] = -0.002;
            //locs[0][0]-=1;
            if(player_axis[0]>-2)
               player_axis[0] -= 1;
               break;
         case 's':
            dirs[0] = 0.002;
            break;
         case 'd':
            //dirs[1] = 0.002;
            //locs[0][0]+=1;
            if(player_axis[0]<2)
               player_axis[0] += 1;
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
         //printf("> %f*\n|%f\n|%f\n\n|%f\n|%f\n\n", mainCamera->yaw, offset - 1,
          //      1 - offset - 1, dirz[1], dirz[0]);

         mainCamera->updateLoc(dirs[1] * deltaTime, 0, dirs[0] * deltaTime);
         printf("? %f\n", mainCamera->pitch);
         break;
      }
   }
} e;
int main() { 
   e.initWindow(800, 600, "test");
    }
