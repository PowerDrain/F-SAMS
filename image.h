#include <stdio.h>
#include  "globaltypes.h"

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
