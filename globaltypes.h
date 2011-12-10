#ifndef globaltypes_ // if not defined
#define globaltypes_

static GLint window[4]; //// Number of windows
int mousex,mousey;
int zone;
int ww, hh;
int globalZoneId;
bool cancelalarm;
/* vectors to specify material properties */
static GLfloat none[] = {0.0, 0.0, 0.0, 1.0};
static GLfloat white[] = {1.0, 1.0, 1.0, 0.5};
static GLfloat red[] = {1.0, 0.0, 0.0, 1};
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLuint tex_name[12];
/* data for two texture arrays */
unsigned char *tex_image[12] = {NULL, NULL};
int height[12];
int width[12];
#endif
