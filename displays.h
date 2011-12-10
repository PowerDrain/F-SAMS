//////////////camera position and light source position////////////////
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Set image size
	imagelocation(1,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
        //glPopMatrix();
	glutPostRedisplay();
 	//glFlush();
	glutSwapBuffers();
}
void redraw_window1(void)
{
        //get the floor number
    if(cancelalarm==1){
	imagelocation(1,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
    }if(cancelalarm==0){
        imagelocation(7,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
    }
        // Check for Type of alarm
        glColor4f(1,1,1,0.0032);
        imagelocation(4,0,0,1,0,1,1,0,1,-0.617,0.31,-0.83,1.21,0.31,-0.83,1.21,0.31,-0.35,-0.617,0.31,-0.35);
	imagelocation(4,0,0,1,0,1,1,0,1,0.98,0.31,-0.35,1.21,0.31,-0.35,1.21,0.31,-0.18,0.98,0.31,-0.18);
	imagelocation(4,0,0,1,0,1,1,0,1,0.835,0.31,-0.185,1.21,0.31,-0.185,1.21,0.31,0.102,0.835,0.31,0.102);

      //  extern void drawSecZone2();
        glutPostRedisplay();
	glutSwapBuffers();

}
void redraw_window2(void)
{
        if(cancelalarm==1){
	imagelocation(2,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
    }if(cancelalarm==0){
        imagelocation(8,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
    }
        // Check for Type of alarm
        glColor4f(1,1,1,0.0032);
        imagelocation(5,0,0,1,0,1,1,0,1,-0.617,0.31,-0.83,1.21,0.31,-0.83,1.21,0.31,-0.35,-0.617,0.31,-0.35);
	imagelocation(5,0,0,1,0,1,1,0,1,0.98,0.31,-0.35,1.21,0.31,-0.35,1.21,0.31,-0.18,0.98,0.31,-0.18);
	imagelocation(5,0,0,1,0,1,1,0,1,0.835,0.31,-0.185,1.21,0.31,-0.185,1.21,0.31,0.102,0.835,0.31,0.102);
      //  glColor4f(1,1,1,1.0);
        glutPostRedisplay();
	glutSwapBuffers();
}
void redraw_window3(void)
{
    if(cancelalarm==1){
	imagelocation(3,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
    }if(cancelalarm==0){
        imagelocation(8,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
    }
        // Check for Type of alarm
        glColor4f(1,1,1,0.0032);
        imagelocation(5,0,0,1,0,1,1,0,1,-0.617,0.31,-0.83,1.21,0.31,-0.83,1.21,0.31,-0.35,-0.617,0.31,-0.35);
	imagelocation(5,0,0,1,0,1,1,0,1,0.98,0.31,-0.35,1.21,0.31,-0.35,1.21,0.31,-0.18,0.98,0.31,-0.18);
	imagelocation(5,0,0,1,0,1,1,0,1,0.835,0.31,-0.185,1.21,0.31,-0.185,1.21,0.31,0.102,0.835,0.31,0.102);
      //  glColor4f(1,1,1,1.0);
        glutPostRedisplay();
	glutSwapBuffers();
}
void Display(void)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Set image size
	imagelocation(2,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
	//imagelocation(2,0,0,1,0,1,1,0,1,-1.51,-0.09,1.51,1.51,-0.09,1.51,1.51,0.11,1.51,-1.51,0.11,1.51);
	//glPopMatrix();
	glutPostRedisplay();
//	glFlush();
	glutSwapBuffers();
}

void drawFireZone1(void)
{
        // If Zone 1, Fire alarm is activated
        // Set image size
          //glColor4f(1,1,1,0.0032);
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
			imagelocation(4,0,0,1,0,1,1,0,1,-1.21,0.31,-0.35,0.83,0.31,-0.35,0.83,0.31,0.345,-1.21,0.31,0.345);;
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
			imagelocation(5,0,0,1,0,1,1,0,1,-1.21,0.31,-0.35,0.83,0.31,-0.35,0.83,0.31,0.345,-1.21,0.31,0.345);;
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
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set image size
	imagelocation(3,0,0,1,0,1,1,0,1,-1.45,0.31,1.099,1.45,0.31,1.099,1.45,0.31,-1.099,-1.45,0.31,-1.099);
	//imagelocation(2,0,0,1,0,1,1,0,1,-1.51,-0.09,1.51,1.51,-0.09,1.51,1.51,0.11,1.51,-1.51,0.11,1.51);
	glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
}