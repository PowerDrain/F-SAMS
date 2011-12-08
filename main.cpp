#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "image.h"
#include "draw_zone.h"
#include "UIprevlog.h"
using namespace std;

void rcmenu(int);
int checkZone(int,int);

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
                        printf("FIRE ALARM TURNED ON\n" );
                        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                        glColor4f(1,1,1,0.0032);
                        drawZone(globalZoneId,1);}else{
                             cout << "You have to selected the Zone First, use mouse left click to select \n";
                        }
			//call fire control function
			//switch floor plan to no people
			//call no people function
			break;
		case 5:
			//get mousex, mousey
                        printf("FIRE ALARM TURNED ON\n" );
                        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                        glColor4f(1,1,1,0.0032);
                        drawZone(globalZoneId,1);
			//call fire drill function
			break;
		case 6:

			//get mousex, mousey
			//zone = checkZone(mousex,mousey);
                        printf("FIRE ALARM TURNED OFF\n" );
                     //   glColor4f(1,0,0,0.02);
                        //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                        //drawZone(1,1);
                        //glutPostRedisplay();
			//call cancel alarm function using zone, password, and fire
			//reset floor plan
			break;
		case 7:
                        printf("SECURITY Alarm TURNED ON\n" );
                        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                        glColor4f(1,1,1,0.004);
                        
                        // wait for mouse left click
                        // get globalZoneId from mouse left click
                        // replace drawZone(1,1) with
                        // drawZone(globalZoneId,1);
                        drawZone(globalZoneId,2);
			//call security control function
			break;
                case 8:
			//get mousex, mousey
			zone = checkZone(mousex,mousey);
			drawZone(globalZoneId, 2);
			//call security drill function
			break;
                case 9:
			//get mousex, mousey
                        printf("SECURITY Alarm TURNED ON\n" );
                        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                        glColor4f(1,1,1,0.004);
                        drawZone(globalZoneId,2);
			//call cancel alarm function using zone, password, security
			//reset floor plan
			break;
		case 10:
                        //glColor4f(1,0,0,1.0);
                        printf("ALL ALARMS TURNED OFF\n" );
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