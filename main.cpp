#define GLUT_DISABLE_ATEXIT_HACK
//#include <Windows.h>  // Donot need this if we compile through LINUX
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include "Control.h"
using namespace std;

void drawZone(int, int);
void Display();
void rcmenu(int);
int checkZone(int,int);
void contactControl();
/////GLobal Declarations///////////////
GLfloat distance = 0.0;
GLuint tex_name[12];
int globalZoneID;
char *alarmType;
Control ctrl;
int n;
/* data for two texture arrays */
unsigned char *tex_image[12] = {NULL, NULL};
int height[12];
int width[12];
int images;

static GLint window[4]; //// Number of windows

int mousex,mousey;
int zone;
int ww, hh;
/* vectors to specify material properties */
static GLfloat none[] = {0.0, 0.0, 0.0, 1.0};
static GLfloat white[] = {1.0, 1.0, 1.0, 0.5};
static GLfloat red[] = {1.0, 0.0, 0.0, 1};
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };

class set_reset_ui{
    bool Fire;
    bool Security;
    bool Exit;
public:
    void setFire(bool);
    void setSecurity(bool);
    void setexit(bool);
}zone1,zone2,zone3,zone4,zone5,zone6,zone7,zone8;

void set_reset_ui::setFire(bool fire){
    Fire=fire;
}
void set_reset_ui::setSecurity(bool security){
    Security=security;
}
void set_reset_ui::setexit(bool exit){
    Exit=exit;
}

////Load bitmap image function////////////////////////
/////////////////////////////////////////////////////
unsigned char *LoadBMP(char file_name[], int *w, int *h)
{
	unsigned char *new_image;
	GLubyte header[514]; // 54-byte header
	int numbytesinrow, numpadbytes;
	int width, height, bitsperpixel, compression;
	long count = 0;
	int i, j, k;
	unsigned char r, g, b, dum;
	FILE *file = fopen(file_name,"rb");
		if (file == NULL) {
			printf("cannot open file %s\n",file_name);
			exit(1);
		};
		if (fread(header,1,54,file) != 54) { //must read 54 bytes
			printf("cannot read 54-byte header\n");
			fclose(file);
			exit(1);
		};
		if (header[0]!='B' || header[1]!='M') { //must be Â’BMÂ’
			printf("not a bmp file\n");
			fclose(file);
			exit(1);
		};

// 4-byte and 2-byte little-endian integers
	width = ((header[21]*256+header[20])*256+header[19])*256+header[18];
	height = ((header[25]*256+header[24])*256+header[23])*256+header[22];
	bitsperpixel= header[29]*256+header[28];
	compression = ((header[33]*256+header[32])*256+header[31])*256+header[30];
		if (compression != 0) {
			printf("file is compressed\n");
			fclose(file);
			exit(1);
		};
		if (bitsperpixel != 24) {
			printf("not a 24-bit pixel image\n");
			fclose(file);
			exit(1);
		};
	new_image = (unsigned char *) malloc((height)*(width)*3);
	numbytesinrow = ((3 * width + 3)/4) * 4;
	numpadbytes = numbytesinrow - 3 * width; //need this many
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			b = fgetc(file);
			g = fgetc(file);
			r = fgetc(file);
			new_image[count++] = r;
			new_image[count++] = g;
			new_image[count++] = b;
		}
		for (k = 0; k < numpadbytes; k++) //skip pad bytes at rowÂ’s end
			dum = fgetc(file);
	}
	fclose(file);
	*w = width;
	*h = height;
	return new_image;
}
//// End of loading image/////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////// Write message on to terminal ////////////////////////////////
//////////////////////////////////////////////////////////////////////
static void writemessage()
{
    printf("######################################################\n");
	printf("FSAMS Session Log\n");
    printf("######################################################\n");
	printf("Fire alarm at Floor X and Room Y is Turned on\n");
	printf("Security alarm at Floor X and Room Y is Turned on\n");
	printf("FSAMS will be transferred to auto mode in 2 min\n");

}

/// Generate texture
void generatetex(char* Filename,int imageid){
    tex_image[imageid] = LoadBMP(Filename, &width[1],&height[1]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, tex_name[imageid]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width[1], height[1],
	GL_RGB, GL_UNSIGNED_BYTE, tex_image[imageid]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	}

//Setimage location
void imagelocation(int imageid, float T11,float T12,float T21,float T22,float T31,float T32,float T41,float T42,
	float V11,float V12,float V13,float V21,float V22,float V23,float V31,float V32,float V33,float V41,float V42,float V43)
{
	glEnable(GL_BLEND);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, tex_name[imageid]);
	glBegin(GL_QUADS);
	glTexCoord2f(T11, T12); glVertex3f(V11,V12,V13);
	glTexCoord2f(T21, T22); glVertex3f(V21,V22,V23);
	glTexCoord2f(T31, T32); glVertex3f(V31,V32,V33);
	glTexCoord2f(T41, T42); glVertex3f(V41,V42,V43);
	glEnd();
	glDepthMask(GL_TRUE);
	glPopMatrix();
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
        //glEnable(GL_LIGHTING);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
        glEnable(GL_LIGHT0);
	glPushMatrix();
/*** generate textures *****/
	glGenTextures(3, tex_name);
/* read *.bmp files */
	generatetex("FirstFloorPeople.bmp",1);
	generatetex("SecondFloorPeople.bmp",2);
	generatetex("ThirdFloorPeople.bmp",3);
      //  generatetex("floor.bmp",4);
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

//////////////camera position and light source position////////////////
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Set image size
	imagelocation(1,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
        glPopMatrix();
	glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Set image size
	imagelocation(2,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
	//imagelocation(2,0,0,1,0,1,1,0,1,-1.51,-0.09,1.51,1.51,-0.09,1.51,1.51,0.11,1.51,-1.51,0.11,1.51);
	glPopMatrix();
	glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
}

void drawrect(void)
{
    glutSolidCube(0.25);
        // Set image size
//	imagelocation(3,0,0,1,0,1,1,0,1,-0.145,0.031,0.1099,0.145,0.031,0.1099,0.145,0.031,-0.1099,-0.1045,0.031,-0.1099);
	glFlush();
	glutSwapBuffers();

}
void Display1(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set image size
	imagelocation(3,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
	//imagelocation(2,0,0,1,0,1,1,0,1,-1.51,-0.09,1.51,1.51,-0.09,1.51,1.51,0.11,1.51,-1.51,0.11,1.51);
	glPopMatrix();
	glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
}
void mouse(int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN){
        //printf("Mouse position is %d,  %d\n", x,y);
		globalZoneID = checkZone(x,y);
		contactControl();
        if(glutGetModifiers() == GLUT_ACTIVE_CTRL){
                    glutPostRedisplay();}
        }
		
        break;

        default:
        break;
    }
}

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

void drawZone(int zoneId, int alarmtype){
	
	switch (zoneId){
	case 1:
                
            glutDisplayFunc(drawrect);
	    break;
	case 2:
		 glutSolidCube(1);
                glutPostRedisplay();
                glutSwapBuffers();
		break;
	case 3:
		 glTranslatef(0,4,0);
                glutSolidCube(1.25);
                glutSwapBuffers();
		glFlush();
		break;
	case 4:
		 glTranslatef(0,4,0);
                glutSolidCube(1.25);
                glutSwapBuffers();
		glFlush();
		break;
	case 5:
		 glTranslatef(0,4,0);
                glutSolidCube(1.25);
                glutSwapBuffers();
		glFlush();
		break;
	case 6:
		 glTranslatef(0,4,0);
                glutSolidCube(1.25);
                glutSwapBuffers();
		glFlush();;
		break;
	case 7:
		 glTranslatef(0,4,0);
                glutSolidCube(1.25);
                glutSwapBuffers();
		glFlush();
		break;
	case 8:
		 glTranslatef(0,4,0);
                glutSolidCube(1.25);
                glutSwapBuffers();
		glFlush();
		break;
	default:
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

			//get mousex, mousey
			zone = checkZone(mousex,mousey);
                        //zone = checkZone(1,1);
                        //printf("FIRE ALARM TURNED ON\n" );
						alarmType = "FA";
                        glColor4f(1,0,0,0.3);
                        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                        drawZone(1,1);
                        glutPostRedisplay();
			//call fire control function
			//switch floor plan to no people
			//call no people function
			break;
		case 5:
			//get mousex, mousey
			zone = checkZone(mousex,mousey);
			drawZone(zone,1);
			//call fire drill function
			break;
		case 6:
    
			//get mousex, mousey
			zone = checkZone(mousex,mousey);
                        printf("FIRE ALARM TURNED OFF\n" );
                        glColor4f(1,0,0,1.0);
                        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                        //drawZone(1,1);
                         glutPostRedisplay();
			//call cancel alarm function using zone, password, and fire
			//reset floor plan
			break;
		case 7:
			//get mousex, mousey
			zone = checkZone(mousex,mousey);
			//drawZone(zone, 2);
                        glColor4f(1,1,1,0.7);
                        //printf("SECURITY Alarm TURNED ON\n" );
						alarmType = "SA";
			//call security control function
			break;
		case 8:
			//get mousex, mousey
			zone = checkZone(mousex,mousey);
			drawZone(zone, 2);
			//call security drill function
			break;
		case 9:
			//get mousex, mousey
			zone = checkZone(mousex,mousey);
                        glColor4f(1,0,0,1.0);
                        printf("Security Alarm TURNED OFF\n" );
			//call cancel alarm function using zone, password, security
			//reset floor plan
			break;
		case 10:
                        glColor4f(1,0,0,1.0);
                        printf("ALL ALARMS TURNED OFF\n" );
			//call cancel all
			//reset all floor plans
			break;

	case 27: /* exit the program */
		printf("Current existing alarms:\n");
		ctrl.active_alarms();
		ctrl.dump_log();
		printf("Hit [Enter] to continue. . .\n");
		getchar();
		exit(0);
		break;
	default:
        glutSetWindow(window[1]);
		glutPopWindow();
		glutPopWindow();
		break;
	}
}

void contactControl(){
	if (globalZoneID != 0 && alarmType != ""){
		if (alarmType == "FA"){
			ctrl.fire_event(globalZoneID);
			globalZoneID = 0;
			alarmType = "";
		} else if (alarmType == "SA"){
			ctrl.security_event(globalZoneID);
			globalZoneID = 0;
			alarmType = "";
		}
	}
	//printf("Inside of contactControl\n");
}

int main(int argc, char** argv)
{
	//ctrl.initBldg();
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