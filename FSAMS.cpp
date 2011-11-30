#define GLUT_DISABLE_ATEXIT_HACK
#include <Windows.h>  // Donot need this if we compile through LINUX
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
/////GLobal Declarations///////////////
GLfloat distance = 0.0;
GLuint tex_name[3];
int n;
/* data for two texture arrays */
unsigned char *tex_image[3] = {NULL, NULL};
int height[3];
int width[3];
int images;

static GLint window[2]; //// Number of windows

/////Setting up camera location and colour variables/////////////////
#define PI 3.14159265
static float alpha = 0.0;
int board[3][3];
static float beta = PI/24.0;;
/* position of camera */
static GLdouble cpos[3];
int ww, hh;
/* position of light source */
static GLfloat lpos[] = {-1.0, 0.5, -1.0, 1.0};
/* vectors to specify material properties */
static GLfloat none[] = {0.0, 0.0, 0.0, 1.0};
static GLfloat white[] = {1.0, 1.0, 1.0, 0.5};

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
		if (header[0]!='B' || header[1]!='M') { //must be BM
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
		for (k = 0; k < numpadbytes; k++) //skip pad bytes at rows end
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

void  Firealarm (int PositionX, int PositionY, int Floor,bool status){ // status 1=> ON    ; 0=>OFF
	if(status==false){
		//load FireBMP
	}
}

void Securityalarm (int  PositionX,int PositionY,int  Floor, bool status) {   //status 1=> ON    ; 0=> OFF
	if(status==true){
		//load SecurityBMP
	}

}

void exitmap (int  Floor, bool status) 		{	                            //status 1=> ON   ; 0=> OFF
	if(status==true){
		//load ExitBMP
	}
}



///// right tab menu ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

void rcmenu(int id)
{
	switch (id) {

        case 1:
        // Load FLOOR 1

        case 2:
            // Load FLOOR 2


        case 3:
              // Load FLOOR 3



	case 27: /* exit the program */
		exit(0);
		break;
	default:
        // Load FLOOR 1


	break;
	}
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
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_LIGHT0);
	glPushMatrix();
/*** generate textures *****/
	glGenTextures(3, tex_name);
/* read *.bmp files */
	generatetex("floor.bmp",1);
	generatetex("firealert.bmp",0);
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
	glutSetWindow(window[0]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /* set current light source position */
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
        // Set image size
	imagelocation(1,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
	imagelocation(1,0,0,1,0,1,1,0,1,-1.51,-0.09,1.51,1.51,-0.09,1.51,1.51,0.11,1.51,-1.51,0.11,1.51);
	glPopMatrix();
	glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
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
	glutAddMenuEntry("Fire Alarm", 3);
	glutAddMenuEntry("Fire Drill", 2);

	//adding menu items to security sub menu
	securitymenu = glutCreateMenu(rcmenu);
	glutAddMenuEntry("Security Alarm", 2);
	glutAddMenuEntry("Security Drill", 3);

	//adding menu items to main menu
	glutCreateMenu(rcmenu);
	glutAddSubMenu("Floors", 1);
	glutAddSubMenu("Fire", 2);
	glutAddSubMenu("Security", 3);
	glutAddMenuEntry("Cancel Alarm", 3);
	glutAddMenuEntry("Exit", 27);

	//attaching menu to mouse right click
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouse(int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN){
        printf("Mouse position is %d,  %d\n", x,y);
        if(glutGetModifiers() == GLUT_ACTIVE_CTRL){
                    glutPostRedisplay();}
        }
        break;

        default:
        break;
    }
}

//Final rcmenu(){
  //switch(id){
    //case:1 Floor1
        //Add Floor1
        //imagelocation(imageid, location..................................)

    //case:2 SecurityDrill Floor1
        //if SecurityAlarm==1
        //get Zone location
        //Add Security Alarm
        //imagelocation(imageid, location..................................)

    //case:3 FireDrill Floor1
        //if FireDrill==1
        //get Zone location
        //Add Fire Drill
        //imagelocation(imageid, location..................................)

    //case:4 FireAlarm Floor1
        //if Firealarm==1
        //Add  Fire Alarm
        //imagelocation(imageid, location..................................)

    //case:5 SecurityAlarm Floor1
        //if Security Drill==1
        //get Zone Location
        //imagelocation(imageid, location..................................) //Add Security Drill

    //case:6 Exitmap Floor1
        //if FireAlarm==1
        //get Zone location
        //Add Exitmap
        //imagelocation(imageid, location..................................)

    //case:7 Floor2
        // Run this if Floor 2 is selected from right menu
        //Floor 2
        //Add Floor
        //imagelocation(imageid, location..................................)

    //case:8 SecurityDrill Floor 2
        //if Security Drill==1
        //get zonelocation
        //Add Security Drill
        //imagelocation(imageid, location..................................)

    //case:9 FireDrill Floor 2
        //if FireDrill==1
        //get Zone location
        //Add Fire Drill
        //imagelocation(imageid, location..................................)

    //case:10 FireAlarm Floor2
        //if Firealarm==1
        //get Zone location
        //Add  Fire Alarm
        //imagelocation(imageid, location..................................)

    //case:11 SecurityAlarm Floor2
        //if SecurityAlarm==1
        //get Zone location
        //Add Security Alarm
        //imagelocation(imageid, location..................................)

    //case:12 Exitmap Floor2
        //if FireAlarm==1
        //get zone location
        //Add Exitmap
        //imagelocation(imageid, location..................................)

    //case:13 Floor3
        // Run this if Floor 3 is selected from right menu
        //Floor 3
        //Add Floor
        //imagelocation(imageid, location..................................)

    //case:14 SecurityDrill Floor3
        //if Security Drill==1
        //get zone location
        //Add Security Drill
        //imagelocation(imageid, location..................................)

    //case:15 FireDrill Floor3
        //if FireDrill==1
        //get zone location
        //Add Fire Drill
        //imagelocation(imageid, location..................................)

    //case:16 FireAlarm Floor1
        //if Firealarm==1
        //get zonelocation
        //Add  Fire Alarm
        //imagelocation(imageid, location..................................)

    //case:17 SecurityAlarm Floor1
        //if SecurityAlarm==1
        //get zonelocation
        //Add Security Alarm
        //imagelocation(imageid, location..................................)

    //case:18 Exitmap Floor1
        //if FireAlarm==1
        //get zone location
        //Add Exitmap
        //imagelocation(imageid, location..................................)

    //default:
        //Floor 1             //Default Floor
        //Add Floor1
        //imagelocation(imageid, location..................................)
    //}
//}


int main(int argc, char** argv)
{
    writemessage();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(650, 500);
	glutInitWindowPosition(700, 0);
	window[0]=glutCreateWindow("FSAMS");
	init();
	createmenu();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}