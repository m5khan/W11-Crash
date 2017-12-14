#include <windows.h>
#include <GL/glut.h>
#include "mesh.h"
#include "textures.h"

#include <stdlib.h>
#include <stdio.h>

#include <iostream>

#define PI 3.1415926535898
using namespace std;

//void animation (int t);
void busfront(void);
void busback(void);



//zNear and zFar values
float deformX  =  1;
float deformY = 1;


Mesh Bus;


void busfront(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[1]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0,1);
	glVertex3f(1,0,1.57075);
	glTexCoord2f(1,1);
	glVertex3f(0.000046326793,1,1.57075);
	glTexCoord2f(1,0);
	glVertex3f(-1,0.0000926535868,1.57075);
	glTexCoord2f(0,0);
	glVertex3f(-0.00013898038,-1,1.57075);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void busback(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[2]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1,1);
	glVertex3f(1.0 ,0.0,-6.28299999);
	glTexCoord2f(0,1);
	glVertex3f(0.0000463267934, 1.0 ,-6.28299999);
	glTexCoord2f(0,0);
	glVertex3f(-1.0,0.0000926535868,-6.28299999);
	glTexCoord2f(1,0);
	glVertex3f(-0.000138980380 ,-1.0,-6.28299999);
	//glVertex3f(1,0.000185307174,-2.14944744);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}