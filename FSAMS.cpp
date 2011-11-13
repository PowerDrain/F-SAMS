#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

/////GLobal Declarations///////////////
GLfloat distance = 0.0;
GLuint tex_name[3];
int n;
/* data for two texture arrays */
unsigned char *tex_image[3] = {NULL, NULL};
int height[3];
int width[3];


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
		if (header[0]!='B' || header[1]!='M') { //must be ’BM’
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
		for (k = 0; k < numpadbytes; k++) //skip pad bytes at row’s end
			dum = fgetc(file);
	}
	fclose(file);
	*w = width;
	*h = height;
	return new_image;
}
//// End of loading image/////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

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


//////// Write message on to terminal ////////////////////////////////
//////////////////////////////////////////////////////////////////////
static void writemessage()
{
	printf("\n FSAMS \n");
}

///// right tab menu ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

void rcmenu(int id)
{
	switch (id) {
	case 27: /* exit the program */
		exit(0);
		break;
	default:
	break;
	}
}

/////////////// Setting up cameras, texturing the bmp file////////////////////
//////////////////////////////////////////////////////////////////////////////
void init(void)
{
	writemessage();
	glClearColor(0.0, 1.0, 0.0, 1.0);  //// background green colour 
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
	tex_image[1] = LoadBMP("floor.bmp", &width[1], &height[1]); //640*480
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, tex_name[1]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width[1], height[1],
	GL_RGB, GL_UNSIGNED_BYTE, tex_image[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glPopMatrix();
  	glutPostRedisplay();
}

/////////////Bitmaps cartesian coordinates and texture values/////////////////
void image(){
	glEnable(GL_BLEND);	
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, tex_name[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.81,0.31,0.62);
	glTexCoord2f(1, 0.0); glVertex3f(0.81,0.31,0.62);
	glTexCoord2f(1, 1); glVertex3f(0.81,0.31,-0.99);
	glTexCoord2f(0.0, 1); glVertex3f(-0.81,0.31,-0.99);
	glEnd();
	glDepthMask(GL_TRUE);
	glPopMatrix();
}


//////////////////////Window reshape//////////////////////////
void reshape(int w, int h)
{
	ww=w;
	hh=h;
	glViewport(0, 0, ww, hh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat) ww / (GLfloat) hh, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0*cos(alpha), 3.0*cos(alpha), 1.0, 0, 0, 0.0, 0.0, 1.0, 0.0);
}

//////////////camera position and light source position////////////////
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/* set current light source position */
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	image();
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
	glutAddMenuEntry("First Floor", 2);
	glutAddMenuEntry("Second Floor",3);
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
	glutAddSubMenu("Floors", 2);
	glutAddSubMenu("Fire", 2);
	glutAddSubMenu("Security", 3);
	glutAddMenuEntry("Cancel Alarm", 3);
	glutAddMenuEntry("Exit", 27);

	//attaching menu to mouse right click
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1020, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("FSAMS");
	createmenu();
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
