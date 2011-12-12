#define GLUT_DISABLE_ATEXIT_HACK
#include<Windows.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "image.h"
#include "draw_zone.h"
#include "Control.h"
#include <string>

using namespace std;

void rcmenu(int);
void createmenu();
void init();
void reshape(int, int);
int checkZone(int,int);
Control systemControl;
Messaging msg;
string password;

int checkZone(int mousex, int mousey){
	int curwin = glutGetWindow();
	if(curwin == window[1]){
		if(((mousex >= 36 && mousex <= 272) && (mousey >= 179 && mousey <= 482)) ||
		((mousex >= 36 && mousex <= 195) && (mousey >= 56 && mousey <=179))){
			return 1;
		}
		else if (((mousex >= 272 && mousex <= 567) && (mousey >= 179 && mousey <= 482)) ||
			       ((mousex >= 567 && mousex <= 662) && (mousey >= 295 && mousey <= 482)) ||
				   ((mousex >= 657 && mousex <= 605) && (mousey >= 179 && mousey <= 220))){
				return 2;
		}
		else if (((mousex >= 195 && mousex <= 662) && (mousey >= 56 && mousey <= 179)) ||
			       ((mousex >= 605 && mousex <= 662) && (mousey >= 179 && mousey <= 220)) ||
				   ((mousex >= 567 && mousex <= 662) && (mousey >= 220 && mousey <= 295))){
				return 3;
		}
		else{
			return 0;
		}
	}
	else if(curwin == window[2]){
		if(((mousex >= 36 && mousex <= 466) && (mousey >= 179 && mousey <= 482)) ||
		((mousex >= 36 && mousex <= 195) && (mousey >= 56 && mousey <= 179)) ||
		((mousex >= 466 && mousex <= 567) && (mousey >= 179 && mousey <= 359)) ||
		((mousex >= 567 && mousex <= 605) && (mousey >= 179 && mousey <= 220))){
			return 4;
		}
		else if (((mousex >= 195 && mousex <= 662) && (mousey >= 56 && mousey <= 179)) ||
			 ((mousex >= 605 && mousex <= 662) && (mousey >= 179 && mousey <= 220)) ||
			 ((mousex >= 567 && mousex <= 662) && (mousey >= 220 && mousey <= 359)) ||
			 ((mousex >= 466 && mousex <= 662) && (mousey >= 359 && mousey <= 482))){
				return 5;
		}
		else{
			return 0;
		}
	}
	else if(curwin == window[3]){
		if((mousex >= 36 && mousex <= 466) && (mousey >= 359 && mousey <= 482)){
			return 6;
		}
		else if(((mousex >= 36 && mousex <= 567) && (mousey >= 179 && mousey <= 359)) ||
			((mousex >= 36 && mousex <= 195) && (mousey >= 56 && mousey <= 179)) ||
			((mousex >= 567 && mousex <= 605) && (mousey >= 179 && mousey <= 220))){
				return 7;
		}
		else if (((mousex >= 195 && mousex <= 662) && (mousey >= 56 && mousey <= 179)) ||
	           ((mousex >= 605 && mousex <= 662) && (mousey >= 179 && mousey <= 220)) ||
	           ((mousex >= 567 && mousex <= 662) && (mousey >= 220 && mousey <= 359)) ||
	           ((mousex >= 466 && mousex <= 662) && (mousey >= 359 && mousey <= 482))){
				return 8;
		}
		else{
			return 0;
		}
	}
}
void mouse(int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN){
        globalZoneId=checkZone(x,y);
        cout << "You have selected Zone" << globalZoneId << endl;
        cout << "Use right click to set an action \n";
       if(glutGetModifiers() == GLUT_ACTIVE_CTRL){
                    glutPostRedisplay();
        }
        }
        break;

        default:
        break;
    }
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Set image size
	imagelocation(1,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
	glutPostRedisplay();
	glutSwapBuffers();
}
void Floor1redraw(void)
{
	glColor4f(1,1,1,1.0);
	if(systemControl.fire_alarm_active(1)||systemControl.fire_alarm_active(2)||systemControl.fire_alarm_active(3)){
	imagelocation(7,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
	imagelocation(6,0,0,1,0,1,1,0,1,-1.2,0.31,-0.07,-1.0,0.31,-0.07,-1.00,0.31,0.07,-1.2,0.31,0.07);
	}else{
		imagelocation(1,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
	}

	glColor4f(1,1,1,0.22);

	//Check Zone 1 Fire
	  if(systemControl.fire_alarm_active(1)){
		  cout << systemControl.fire_alarm_active(1) <<endl;
	  imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,-0.83,-0.617,0.31,-0.83,-0.617,0.31,-0.35,-1.21,0.31,-0.35);
          imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,-0.35,-0.3,0.31,-0.35,-0.3,0.31,0.82,-1.21,0.31,0.82);
	  }
	//Check Zone 1 Security
	  if(systemControl.security_alarm_active(1)){
	  imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,-0.83,-0.617,0.31,-0.83,-0.617,0.31,-0.35,-1.21,0.31,-0.35);
          imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,-0.35,-0.3,0.31,-0.35,-0.3,0.31,0.82,-1.21,0.31,0.82);
	  }
	//Check Zone 2 Fire
	  if(systemControl.fire_alarm_active(2)){
	  imagelocation(4,0,0,1,0,1,1,0,1,-0.3,0.31,-0.35,0.835,0.31,-0.35,0.835,0.31,0.82,-0.3,0.31,0.82);
	  imagelocation(4,0,0,1,0,1,1,0,1,0.835,0.31,-0.35,0.98,0.31,-0.35,0.98,0.31,-0.185,0.835,0.31,-0.185);
	  imagelocation(4,0,0,1,0,1,1,0,1,0.835,0.31,0.102,1.21,0.31,0.102,1.21,0.31,0.82,0.835,0.31,0.82);
	  }
	//Check Zone 2 Security
	  if(systemControl.security_alarm_active(2)){
	  imagelocation(5,0,0,1,0,1,1,0,1,-0.3,0.31,-0.35,0.835,0.31,-0.35,0.835,0.31,0.82,-0.3,0.31,0.82);
	  imagelocation(5,0,0,1,0,1,1,0,1,0.835,0.31,-0.35,0.98,0.31,-0.35,0.98,0.31,-0.185,0.835,0.31,-0.185);
	  imagelocation(5,0,0,1,0,1,1,0,1,0.835,0.31,0.102,1.21,0.31,0.102,1.21,0.31,0.82,0.835,0.31,0.82);
	  }
	//Check Zone 3 Fire
	  if(systemControl.fire_alarm_active(3)){
	imagelocation(4,0,0,1,0,1,1,0,1,-0.617,0.31,-0.83,1.21,0.31,-0.83,1.21,0.31,-0.35,-0.617,0.31,-0.35);
	imagelocation(4,0,0,1,0,1,1,0,1,0.98,0.31,-0.35,1.21,0.31,-0.35,1.21,0.31,-0.18,0.98,0.31,-0.18);
	imagelocation(4,0,0,1,0,1,1,0,1,0.835,0.31,-0.185,1.21,0.31,-0.185,1.21,0.31,0.102,0.835,0.31,0.102);
	}
	//Check Zone 3 Security
	if(systemControl.security_alarm_active(3)){
	imagelocation(5,0,0,1,0,1,1,0,1,-0.617,0.31,-0.83,1.21,0.31,-0.83,1.21,0.31,-0.35,-0.617,0.31,-0.35);
	imagelocation(5,0,0,1,0,1,1,0,1,0.98,0.31,-0.35,1.21,0.31,-0.35,1.21,0.31,-0.18,0.98,0.31,-0.18);
	imagelocation(5,0,0,1,0,1,1,0,1,0.835,0.31,-0.185,1.21,0.31,-0.185,1.21,0.31,0.102,0.835,0.31,0.102);
	}

	//glutPostRedisplay();
	glutSwapBuffers();
}
void Floor2redraw(void)
{
	glColor4f(1,1,1,1.0);
	if(systemControl.fire_alarm_active(4)||systemControl.fire_alarm_active(5)){
	imagelocation(8,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
	imagelocation(6,0,0,1,0,1,1,0,1,-1.2,0.31,0.07,-1.0,0.31,0.07,-1.00,0.31,-0.07,-1.2,0.31,-0.07);
	}else{
		imagelocation(2,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
	}
	glColor4f(1,1,1,0.22);	

	//Check Zone 4 Fire
	if(systemControl.fire_alarm_active(4)){
	imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,-0.83,-0.617,0.31,-0.83,-0.617,0.31,-0.35,-1.21,0.31,-0.35);
	imagelocation(4,0,0,1,0,1,1,0,1,0.83,0.31,-0.35,0.975,0.31,-0.35,0.975,0.31,-0.18,0.83,0.31,-0.18);
	imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,0.34,0.45,0.31,0.34,0.45,0.31,0.82,-1.21,0.31,0.82);
	imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,-0.35,0.83,0.31,-0.35,0.83,0.31,0.345,-1.21,0.31,0.345);
	}
	//Check Zone 4 Security
	if(systemControl.security_alarm_active(4)){
			imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,-0.83,-0.617,0.31,-0.83,-0.617,0.31,-0.35,-1.21,0.31,-0.35);
			imagelocation(5,0,0,1,0,1,1,0,1,0.83,0.31,-0.35,0.975,0.31,-0.35,0.975,0.31,-0.18,0.83,0.31,-0.18);
			imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,0.34,0.45,0.31,0.34,0.45,0.31,0.82,-1.21,0.31,0.82);
			imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,-0.35,0.83,0.31,-0.35,0.83,0.31,0.345,-1.21,0.31,0.345);
	}
	//Check Zone 5 Fire
	if(systemControl.fire_alarm_active(5)){
			imagelocation(4,0,0,1,0,1,1,0,1,-0.617,0.31,-0.83,1.2,0.31,-0.83,1.2,0.31,-0.35,-0.617,0.31,-0.35);
			imagelocation(4,0,0,1,0,1,1,0,1,0.976,0.31,-0.35,1.2,0.31,-0.35,1.2,0.31,-0.18,0.976,0.31,-0.18);
			imagelocation(4,0,0,1,0,1,1,0,1,0.83,0.31,-0.185,1.2,0.31,-0.185,1.2,0.31,0.35,0.83,0.31,0.35);
			imagelocation(4,0,0,1,0,1,1,0,1,0.45,0.31,0.35,1.2,0.31,0.35,1.2,0.31,0.825,0.45,0.31,0.825);
	}
	//Check Zone 5 Security
	if(systemControl.security_alarm_active(5)){
			imagelocation(5,0,0,1,0,1,1,0,1,-0.617,0.31,-0.83,1.2,0.31,-0.83,1.2,0.31,-0.35,-0.617,0.31,-0.35);
			imagelocation(5,0,0,1,0,1,1,0,1,0.976,0.31,-0.35,1.2,0.31,-0.35,1.2,0.31,-0.18,0.976,0.31,-0.18);
			imagelocation(5,0,0,1,0,1,1,0,1,0.83,0.31,-0.185,1.2,0.31,-0.185,1.2,0.31,0.35,0.83,0.31,0.35);
			imagelocation(5,0,0,1,0,1,1,0,1,0.45,0.31,0.35,1.2,0.31,0.35,1.2,0.31,0.825,0.45,0.31,0.825);
	}

	//glutPostRedisplay();
	glutSwapBuffers();
}
void Floor3redraw(void)
{
	glColor4f(1,1,1,1.0);
	if(systemControl.fire_alarm_active(6)||systemControl.fire_alarm_active(7)||systemControl.fire_alarm_active(8)){
	imagelocation(9,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
	imagelocation(6,0,0,1,0,1,1,0,1,-1.2,0.31,-0.07,-1.0,0.31,-0.07,-1.00,0.31,0.07,-1.2,0.31,0.07);
	}else{
		imagelocation(3,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
	}
	glColor4f(1,1,1,0.032);

	//Check Zone 6 Fire
	if(systemControl.fire_alarm_active(6)){
	imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,0.34,0.45,0.31,0.34,0.45,0.31,0.82,-1.21,0.31,0.82);
	}
	//Check Zone 6 Security
	if(systemControl.fire_alarm_active(6)){
	imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,0.34,0.45,0.31,0.34,0.45,0.31,0.82,-1.21,0.31,0.82);
	}

	//Check Zone 7 Fire
	if(systemControl.fire_alarm_active(7)){
	imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,-0.83,-0.617,0.31,-0.83,-0.617,0.31,-0.35,-1.21,0.31,-0.35);
	imagelocation(4,0,0,1,0,1,1,0,1,0.83,0.31,-0.35,0.975,0.31,-0.35,0.975,0.31,-0.18,0.83,0.31,-0.18);
	imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,-0.35,0.83,0.31,-0.35,0.83,0.31,0.345,-1.21,0.31,0.345);
	}
	//Check Zone 7 Security 
	if(systemControl.security_alarm_active(7)){     
	imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,-0.83,-0.617,0.31,-0.83,-0.617,0.31,-0.35,-1.21,0.31,-0.35);
	imagelocation(5,0,0,1,0,1,1,0,1,0.83,0.31,-0.35,0.975,0.31,-0.35,0.975,0.31,-0.18,0.83,0.31,-0.18);
	imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,-0.35,0.83,0.31,-0.35,0.83,0.31,0.345,-1.21,0.31,0.345);
	}
	//Check Zone 8 Fire
	if(systemControl.fire_alarm_active(8)){
	imagelocation(4,0,0,1,0,1,1,0,1,-0.617,0.31,-0.83,1.2,0.31,-0.83,1.2,0.31,-0.35,-0.617,0.31,-0.35);
    imagelocation(4,0,0,1,0,1,1,0,1,0.976,0.31,-0.35,1.2,0.31,-0.35,1.2,0.31,-0.18,0.976,0.31,-0.18);
	imagelocation(4,0,0,1,0,1,1,0,1,0.83,0.31,-0.185,1.2,0.31,-0.185,1.2,0.31,0.345,0.83,0.31,0.345);
    imagelocation(4,0,0,1,0,1,1,0,1,0.45,0.31,0.345,1.2,0.31,0.345,1.2,0.31,0.825,0.45,0.31,0.825);
	}
	//Check Zone 8 Security
	if(systemControl.security_alarm_active(8)){
	imagelocation(5,0,0,1,0,1,1,0,1,-0.617,0.31,-0.83,1.2,0.31,-0.83,1.2,0.31,-0.35,-0.617,0.31,-0.35);
    imagelocation(5,0,0,1,0,1,1,0,1,0.976,0.31,-0.35,1.2,0.31,-0.35,1.2,0.31,-0.18,0.976,0.31,-0.18);
	imagelocation(5,0,0,1,0,1,1,0,1,0.83,0.31,-0.185,1.2,0.31,-0.185,1.2,0.31,0.345,0.83,0.31,0.345);
    imagelocation(5,0,0,1,0,1,1,0,1,0.45,0.31,0.345,1.2,0.31,0.345,1.2,0.31,0.825,0.45,0.31,0.825);
	}
	//glutPostRedisplay();
	glutSwapBuffers();
}
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Set image size
	imagelocation(2,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
	glutPostRedisplay();
	glutSwapBuffers();
}

void drawFireZone1(void)
{
        // If Zone 1, Fire alarm is activated
        // Set image size
          glColor4f(1,1,1,0.32);
          imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,-0.83,-0.617,0.31,-0.83,-0.617,0.31,-0.35,-1.21,0.31,-0.35);
          imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,-0.35,-0.3,0.31,-0.35,-0.3,0.31,0.82,-1.21,0.31,0.82);
          glColor4f(1,0,0,1.0);
          imagelocation(6,0,0,1,0,1,1,0,1,-1.2,0.31,-0.07,-1.0,0.31,-0.07,-1.00,0.31,0.07,-1.2,0.31,0.07);
           glColor4f(1,1,1,0.32);
		   glutPostRedisplay();
          glutSwapBuffers();
}

void drawFireZone2(void){
         // If Zone 2, Fire alarm is activated
        // Set image size
          imagelocation(4,0,0,1,0,1,1,0,1,-0.3,0.31,-0.35,0.835,0.31,-0.35,0.835,0.31,0.82,-0.3,0.31,0.82);
	  imagelocation(4,0,0,1,0,1,1,0,1,0.835,0.31,-0.35,0.98,0.31,-0.35,0.98,0.31,-0.185,0.835,0.31,-0.185);
	  imagelocation(4,0,0,1,0,1,1,0,1,0.835,0.31,0.102,1.21,0.31,0.102,1.21,0.31,0.82,0.835,0.31,0.82);
	  glutPostRedisplay();
          glutSwapBuffers();
}
void drawFireZone3(void){

         // If Zone 3, Fire alarm is activated
        // Set image size
        imagelocation(4,0,0,1,0,1,1,0,1,-0.617,0.31,-0.83,1.21,0.31,-0.83,1.21,0.31,-0.35,-0.617,0.31,-0.35);
	imagelocation(4,0,0,1,0,1,1,0,1,0.98,0.31,-0.35,1.21,0.31,-0.35,1.21,0.31,-0.18,0.98,0.31,-0.18);
	imagelocation(4,0,0,1,0,1,1,0,1,0.835,0.31,-0.185,1.21,0.31,-0.185,1.21,0.31,0.102,0.835,0.31,0.102);
	glutPostRedisplay();
          glutSwapBuffers();
}
void drawFireZone4(void){

         // If Zone 3, Fire alarm is activated
        // Set image size
			imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,-0.83,-0.617,0.31,-0.83,-0.617,0.31,-0.35,-1.21,0.31,-0.35);
			imagelocation(4,0,0,1,0,1,1,0,1,0.83,0.31,-0.35,0.975,0.31,-0.35,0.975,0.31,-0.18,0.83,0.31,-0.18);
			imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,0.34,0.45,0.31,0.34,0.45,0.31,0.82,-1.21,0.31,0.82);
			imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,-0.35,0.83,0.31,-0.35,0.83,0.31,0.345,-1.21,0.31,0.345);
			glutPostRedisplay();
          glutSwapBuffers();
}
void drawFireZone5(void){

         // If Zone 3, Fire alarm is activated
        // Set image size
			imagelocation(4,0,0,1,0,1,1,0,1,-0.617,0.31,-0.83,1.2,0.31,-0.83,1.2,0.31,-0.35,-0.617,0.31,-0.35);
			imagelocation(4,0,0,1,0,1,1,0,1,0.976,0.31,-0.35,1.2,0.31,-0.35,1.2,0.31,-0.18,0.976,0.31,-0.18);
			imagelocation(4,0,0,1,0,1,1,0,1,0.83,0.31,-0.185,1.2,0.31,-0.185,1.2,0.31,0.35,0.83,0.31,0.35);
			imagelocation(4,0,0,1,0,1,1,0,1,0.45,0.31,0.35,1.2,0.31,0.35,1.2,0.31,0.825,0.45,0.31,0.825);
			glutPostRedisplay();
          glutSwapBuffers();
}
void drawFireZone6(void){

         // If Zone 3, Fire alarm is activated
        // Set image size
          imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,0.34,0.45,0.31,0.34,0.45,0.31,0.82,-1.21,0.31,0.82);
		  glutPostRedisplay();
          glutSwapBuffers();
}
void drawFireZone7(void){

         // If Zone 3, Fire alarm is activated
        // Set image size
			imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,-0.83,-0.617,0.31,-0.83,-0.617,0.31,-0.35,-1.21,0.31,-0.35);
			imagelocation(4,0,0,1,0,1,1,0,1,0.83,0.31,-0.35,0.975,0.31,-0.35,0.975,0.31,-0.18,0.83,0.31,-0.18);
			imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,-0.35,0.83,0.31,-0.35,0.83,0.31,0.345,-1.21,0.31,0.345);
			glutPostRedisplay();
          glutSwapBuffers();
}

void drawFireZone8(void){

         // If Zone 3, Fire alarm is activated
        // Set image size
	imagelocation(4,0,0,1,0,1,1,0,1,-0.617,0.31,-0.83,1.2,0.31,-0.83,1.2,0.31,-0.35,-0.617,0.31,-0.35);
        imagelocation(4,0,0,1,0,1,1,0,1,0.976,0.31,-0.35,1.2,0.31,-0.35,1.2,0.31,-0.18,0.976,0.31,-0.18);
	imagelocation(4,0,0,1,0,1,1,0,1,0.83,0.31,-0.185,1.2,0.31,-0.185,1.2,0.31,0.345,0.83,0.31,0.345);
        imagelocation(4,0,0,1,0,1,1,0,1,0.45,0.31,0.345,1.2,0.31,0.345,1.2,0.31,0.825,0.45,0.31,0.825);
		glutPostRedisplay();
          glutSwapBuffers();
}
void drawSecZone1(void)
{
        // If Zone 1, Fire alarm is activated
        // Set image size
          imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,-0.83,-0.617,0.31,-0.83,-0.617,0.31,-0.35,-1.21,0.31,-0.35);
          imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,-0.35,-0.3,0.31,-0.35,-0.3,0.31,0.82,-1.21,0.31,0.82);
		  glutPostRedisplay();
          glutSwapBuffers();
}

void drawSecZone2(void){
         // If Zone 2, Fire alarm is activated
        // Set image size
          imagelocation(5,0,0,1,0,1,1,0,1,-0.3,0.31,-0.35,0.835,0.31,-0.35,0.835,0.31,0.82,-0.3,0.31,0.82);
	  imagelocation(5,0,0,1,0,1,1,0,1,0.835,0.31,-0.35,0.98,0.31,-0.35,0.98,0.31,-0.185,0.835,0.31,-0.185);
	  imagelocation(5,0,0,1,0,1,1,0,1,0.835,0.31,0.102,1.21,0.31,0.102,1.21,0.31,0.82,0.835,0.31,0.82);
	  glutPostRedisplay();
          glutSwapBuffers();
}
void drawSecZone3(void){

         // If Zone 3, Fire alarm is activated
        // Set image size
        imagelocation(5,0,0,1,0,1,1,0,1,-0.617,0.31,-0.83,1.21,0.31,-0.83,1.21,0.31,-0.35,-0.617,0.31,-0.35);
	imagelocation(5,0,0,1,0,1,1,0,1,0.98,0.31,-0.35,1.21,0.31,-0.35,1.21,0.31,-0.18,0.98,0.31,-0.18);
	imagelocation(5,0,0,1,0,1,1,0,1,0.835,0.31,-0.185,1.21,0.31,-0.185,1.21,0.31,0.102,0.835,0.31,0.102);
	glutPostRedisplay();
          glutSwapBuffers();
}
void drawSecZone4(void){

         // If Zone 3, Fire alarm is activated
        // Set image size
			imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,-0.83,-0.617,0.31,-0.83,-0.617,0.31,-0.35,-1.21,0.31,-0.35);
			imagelocation(5,0,0,1,0,1,1,0,1,0.83,0.31,-0.35,0.975,0.31,-0.35,0.975,0.31,-0.18,0.83,0.31,-0.18);
			imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,0.34,0.45,0.31,0.34,0.45,0.31,0.82,-1.21,0.31,0.82);
			imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,-0.35,0.83,0.31,-0.35,0.83,0.31,0.345,-1.21,0.31,0.345);
			glutPostRedisplay();
          glutSwapBuffers();
}
void drawSecZone5(void){

         // If Zone 3, Fire alarm is activated
        // Set image size
			imagelocation(5,0,0,1,0,1,1,0,1,-0.617,0.31,-0.83,1.2,0.31,-0.83,1.2,0.31,-0.35,-0.617,0.31,-0.35);
			imagelocation(5,0,0,1,0,1,1,0,1,0.976,0.31,-0.35,1.2,0.31,-0.35,1.2,0.31,-0.18,0.976,0.31,-0.18);
			imagelocation(5,0,0,1,0,1,1,0,1,0.83,0.31,-0.185,1.2,0.31,-0.185,1.2,0.31,0.35,0.83,0.31,0.35);
			imagelocation(5,0,0,1,0,1,1,0,1,0.45,0.31,0.35,1.2,0.31,0.35,1.2,0.31,0.825,0.45,0.31,0.825);
			glutPostRedisplay();
          glutSwapBuffers();
}
void drawSecZone6(void){

         // If Zone 3, Fire alarm is activated
        // Set image size
          imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,0.34,0.45,0.31,0.34,0.45,0.31,0.82,-1.21,0.31,0.82);
		  glutPostRedisplay();
          glutSwapBuffers();
}
void drawSecZone7(void){

         // If Zone 3, Fire alarm is activated
        // Set image size
			imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,-0.83,-0.617,0.31,-0.83,-0.617,0.31,-0.35,-1.21,0.31,-0.35);
			imagelocation(5,0,0,1,0,1,1,0,1,0.83,0.31,-0.35,0.975,0.31,-0.35,0.975,0.31,-0.18,0.83,0.31,-0.18);
			imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,-0.35,0.83,0.31,-0.35,0.83,0.31,0.345,-1.21,0.31,0.345);
			glutPostRedisplay();
          glutSwapBuffers();
}

void drawSecZone8(void){

         // If Zone 3, Fire alarm is activated
        // Set image size
	imagelocation(5,0,0,1,0,1,1,0,1,-0.617,0.31,-0.83,1.2,0.31,-0.83,1.2,0.31,-0.35,-0.617,0.31,-0.35);
        imagelocation(5,0,0,1,0,1,1,0,1,0.976,0.31,-0.35,1.2,0.31,-0.35,1.2,0.31,-0.18,0.976,0.31,-0.18);
	imagelocation(5,0,0,1,0,1,1,0,1,0.83,0.31,-0.185,1.2,0.31,-0.185,1.2,0.31,0.345,0.83,0.31,0.345);
        imagelocation(5,0,0,1,0,1,1,0,1,0.45,0.31,0.345,1.2,0.31,0.345,1.2,0.31,0.825,0.45,0.31,0.825);
		glutPostRedisplay();
          glutSwapBuffers();
}

void Display1(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set image size
	imagelocation(3,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
	glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
}
void rcmenu( int id)
{
	switch (id) {

        case 1:
				glutSetWindow(window[1]);
				glutPopWindow();
				glutPopWindow();
                                break;

        case 2:
			        glutSetWindow(window[2]);
				glutPopWindow();
				glutPopWindow();
                                break;


        case 3:
                        glutSetWindow(window[3]);
			glutPopWindow();
			glutPopWindow();
			break;

	case 4:

                   if(globalZoneId!=0){
                        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                        glColor4f(1,1,1,0.0032);
                        drawZone(globalZoneId,1);
			//call fire control function, wait for a min to show no people window
                        systemControl.fire_event(globalZoneId);
                        // There should be a 2 min gap between changing window
			//switch floor plan to no people
                        glColor4f(1,1,1,1);
                        if(globalZoneId==1 ||globalZoneId==2 ||globalZoneId==3){
                        glutDisplayFunc(Floor1redraw);
                        // Turn back previous alarms
                        }
                        if(globalZoneId==4 ||globalZoneId==5){
                        glutDisplayFunc(Floor2redraw);
                        // Turn back previous alarms
                        }
                        if(globalZoneId==6 ||globalZoneId==7 ||globalZoneId==8){
                        glutDisplayFunc(Floor3redraw);
                        // Turn back previous alarms
                        }
                        
                    }else{
                             cout << "You have to selected the Zone First, use mouse left click to select \n";
                        }
                        
			break;
		case 5:
			//get mousex, mousey
                    systemControl.fire_test_event(globalZoneId);
                        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                        glColor4f(1,1,1,0.0032);
                        drawZone(globalZoneId,1);
			//call fire drill function
			break;
		case 6:
                    cout << "Please enter the password" << endl;
					cin >> password;
		   systemControl.turn_off(globalZoneId,password,msg.ALARM_TYPE_FIRE);
                    if(globalZoneId!=0){
                        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                        glColor4f(1,1,1,1);
                        if(globalZoneId==1 ||globalZoneId==2 ||globalZoneId==3){
                        glutDisplayFunc(Floor1redraw);
                        // Turn back previous alarms
                        }
                        if(globalZoneId==4 ||globalZoneId==5){
                        glutDisplayFunc(Floor2redraw);
                        // Turn back previous alarms
                        }
                        if(globalZoneId==6 ||globalZoneId==7 ||globalZoneId==8){
                        glutDisplayFunc(Floor3redraw);
                        // Turn back previous alarms
                        }
                     }

			break;
		case 7:
                        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                        glColor4f(1,1,1,0.0032);
                        drawZone(globalZoneId,2);
			//call security control function
                        systemControl.security_event(globalZoneId);
			break;
                case 8:
                        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                        glColor4f(1,1,1,0.0032);
                        drawZone(globalZoneId,2);
			//call security drill function
                        systemControl.security_test_event(globalZoneId);
			break;
                case 9:
                        cout << "Please enter the password" << endl;
					   cin >> password;
                        systemControl.turn_off(globalZoneId,password,msg.ALARM_TYPE_SECURITY);
			if(globalZoneId!=0){
                        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

                        glColor4f(1,1,1,1);
                        if(globalZoneId==1 ||globalZoneId==2 ||globalZoneId==3){
                        glutDisplayFunc(Floor1redraw);
                        // Turn back previous alarms
                        }
                        if(globalZoneId==4 ||globalZoneId==5){
                        glutDisplayFunc(Floor2redraw);
                        // Turn back previous alarms
                        }
                        if(globalZoneId==6 ||globalZoneId==7 ||globalZoneId==8){
                        glutDisplayFunc(Floor3redraw);
                        // Turn back previous alarms
                        }
                     }

		//call cancel alarm function using zone, password, security
		//reset floor plan
		break;
		case 10:
                        cout << "Enter password to cancel alarms"<< endl;
						cin >> password;
						systemControl.turn_off(password);
						glutSetWindow(window[1]);
						glutPopWindow();
						glutPopWindow();
						glColor4f(1,1,1,1);
						glutDisplayFunc(display);

						glutSetWindow(window[2]);
						glutPopWindow();
						glutPopWindow();
						glColor4f(1,1,1,1);
						glutDisplayFunc(Display);

						glutSetWindow(window[3]);
						glutPopWindow();
						glutPopWindow();
						glColor4f(1,1,1,1);
						glutDisplayFunc(Display1);
                       
			//call cancel all
			//reset all floor plans
			break;

	case 27: /* exit the program */
		exit(0);
		break;
	default:
                glutSetWindow(window[1]);
		glutPopWindow();
		glutPopWindow();
		break;
	}
}

//////////////Right click menu /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void createmenu(void){
	int floormenu;  //floor sub menu
	int firemenu;  //fire sub menu
	int securitymenu;  //security sub menu

	//adding menu items to floor sub menu
	floormenu = glutCreateMenu(rcmenu);
	glutAddMenuEntry("First Floor", 1);
	glutAddMenuEntry("Second Floor",2);
	glutAddMenuEntry("Third Floor", 3);

	//adding menu items to fire sub menu
	firemenu = glutCreateMenu(rcmenu);
	glutAddMenuEntry("Fire Alarm", 4);
	glutAddMenuEntry("Fire Drill", 5);
	glutAddMenuEntry("Off",6);

	//adding menu items to security sub menu
	securitymenu = glutCreateMenu(rcmenu);
	glutAddMenuEntry("Security Alarm", 7);
	glutAddMenuEntry("Security Drill", 8);
	glutAddMenuEntry("Off",9);

	//adding menu items to main menu
	glutCreateMenu(rcmenu);
	glutAddSubMenu("Floors", floormenu);
	glutAddSubMenu("Fire", firemenu);
	glutAddSubMenu("Security", securitymenu);
	glutAddMenuEntry("Cancel Alarm", 10);
	glutAddMenuEntry("Exit", 27);

	//attaching menu to mouse right click
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


//////// Write message on to terminal ////////////////////////////////
//////////////////////////////////////////////////////////////////////
static void writemessage()
{
    cout<<"---------------------------------------------------------------\n";
    cout <<"      *****        ~~~~~      *      *       *  ~~~~~        \n";
    cout <<"      *           (          * *     * *   * * (            \n";
    cout <<"      *****        ~~~~~    *****    *   *   *  ~~~~~        \n";
    cout <<"      *                 )  *     *   *       *       )        \n";
    cout <<"      *            ~~~~~  *       *  *       *  ~~~~~        \n";
    cout<<"---------------------------------------------------------------\n";
    cout <<" USE MOUSE LEFT CLICK TO SELECT A ZONE \n";
    cout <<" USE MOUSE RIGHT CLICK TO TURN ON/OFF ALARMS \n ";
    cout <<"___________________________________________________________________________\n"<< endl;
}

/////////////// Setting up cameras, texturing the bmp file////////////////////
//////////////////////////////////////////////////////////////////////////////
void init(void)
{
	glClearColor(0.97, 0.97, 0.97, 1.0);  //// background white colour
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
        glEnable(GL_BLEND); //enable the blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //
	glPushMatrix();
/*** generate textures *****/
	glGenTextures(12, tex_name);
/* read *.bmp files */
	generatetex("FirstFloorPeople.bmp",1);
	generatetex("SecondFloorPeople.bmp",2);
	generatetex("ThirdFloorPeople.bmp",3);
        generatetex("red.bmp",4);
        generatetex("sec.bmp",5);
        generatetex("exit.bmp",6);
        generatetex("FirstFloorNoPeople.bmp",7);
        generatetex("SecondFloorNoPeople.bmp",8);
        generatetex("ThirdFloorNoPeople.bmp",9);
        glPopMatrix();
  	glutPostRedisplay();
}


//////////////////////Window reshape//////////////////////////
void reshape(int w, int h)
{
	ww=w;
	hh=h;
	glViewport(0, 0, ww, hh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (GLfloat) ww / (GLfloat) hh, 1.0, 4.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0, 1.35, 0.001, 0, 0, 0.0, 0.0, 1.0, 0.0);


}


int main(int argc, char** argv)
{
	systemControl.turn_off("fsams");
    writemessage();
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(650, 500);
	glutInitWindowPosition(700, 0);
	window[0]=glutCreateWindow("FSAMS");
	window[1] = glutCreateSubWindow(window[0],0,0,650,500);
		init();
		createmenu();
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		glutMouseFunc(mouse);
	window[2] = glutCreateSubWindow(window[0],0,0,650,500);
	init();
	createmenu();
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	window[3] = glutCreateSubWindow(window[0],0,0,650,500);
	init();
	createmenu();
	glutDisplayFunc(Display1);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}