#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "busCords.h"

#define PI 3.1415926535898
using namespace std;

float blockX[18] = {0,2,4,6,8,10,0,2,4,6,8,10,0,2,4,6,8,10};
float blockY[18] = {1,1,1,1,1,1,3,3,3,3,3,3,5,5,5,5,5,5};
float blockZ[18] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float gravity = 15.5;

//Mesh extrusion;
//Mesh smoothSurface;

void wall (void);
void cube (void);
void animate (int t);
void blockSimulation(void);
void busDeformation(void);
void moveBus();
float getTime() ;
void cameraControl (void);


busCordinates busCords;
//zNear and zFar values


float angle17z = 0;
float angle16x = 0;float angle16y = 0;
float angle15x = 0;float angle15y = 0;
float angle14x = 0;float angle14y = 0;
float angle13z = 0;
float angle12z = 0;
float angle11x = 0;float angle11y = 0;
float angle10x = 0;float angle10y = 0;
float angle9 = 0;
float angle8x = 0;float angle8y = 0;
float angle7x = 0;float angle7y = 0;
float angle6x = 0;float angle6y = 0;
float angle3y= 0;

int collisionCount = 0;
bool deformation = false;
bool breakwall = false;


void cube2 (void)
{
	//frontface
	glBegin(GL_QUADS);
	//glTexCoord2f(1,1);
	glVertex3f(-1,-1,1);
	glNormal3f(0,0,1);
	//glTexCoord2f(0,1);
	glVertex3f(1,-1,1);
	glNormal3f(0,0,1);
	//glTexCoord2f(0,0);
	glVertex3f(1,1,1);
	glNormal3f(0,0,1);
	//glTexCoord2f(1,0);
	glVertex3f(-1,1,1);
	glNormal3f(0,0,1);

	//rightface
	glBegin(GL_QUADS);
	//glTexCoord2f(1,1);
	glVertex3f(1,-1,1);
	glNormal3f(1,0,0);
	//glTexCoord2f(0,1);
	glVertex3f(1,-1,-1);
	glNormal3f(1,0,0);
	//glTexCoord2f(0,0);
	glVertex3f(1,1,-1);
	glNormal3f(1,0,0);
	//glTexCoord2f(1,0);
	glVertex3f(1,1,1);
	glNormal3f(1,0,0);

		//leftface
	glBegin(GL_QUADS);
	//glTexCoord2f(1,1);
	glVertex3f(-1,-1,-1);
	glNormal3f(-1,0,0);
	//glTexCoord2f(0,1);
	glVertex3f(-1,-1,1);
	glNormal3f(-1,0,0);
	//glTexCoord2f(0,0);
	glVertex3f(-1,1,1);
	glNormal3f(-1,0,0);
	//glTexCoord2f(1,0);
	glVertex3f(-1,1,-1);
	glNormal3f(-1,0,0);

	//backface
	glBegin(GL_QUADS);
	//glTexCoord2f(1,1);
	glVertex3f(1,-1,-1);
	glNormal3f(0,0,-1);
	//glTexCoord2f(0,1);
	glVertex3f(-1,-1,-1);
	glNormal3f(0,0,-1);
	//glTexCoord2f(0,0);
	glVertex3f(-1,1,-1);
	glNormal3f(0,0,-1);
	//glTexCoord2f(1,0);
	glVertex3f(1,1,-1);
	glNormal3f(0,0,-1);

	//topwall
	glBegin(GL_QUADS);
	//glTexCoord2f(0,0);
	glVertex3f(-1,1,1);
	glNormal3f(0,1,0);
	//glTexCoord2f(1,0);
	glVertex3f(1,1,1);
	glNormal3f(0,1,0);
	glVertex3f(1,1,-1);
	glNormal3f(0,1,0);
	glVertex3f(-1,1,-1);
	glNormal3f(0,1,-0);

	//bottomwall
	glBegin(GL_QUADS);
	glVertex3f(1,-1,1);
	glNormal3f(0,-1,0);
	glVertex3f(-1,-1,1);
	glNormal3f(0,-1,0);
	glVertex3f(-1,-1,-1);
	glNormal3f(0,-1,0);
	glVertex3f(1,-1,-1);
	glNormal3f(0,-1,0);

	glEnd();
}

void wall (void)
{
	//row0
	glPushMatrix(); //01
	glTranslatef(blockX[0],blockY[0],blockZ[0]);
		cube2();
	glPopMatrix();

	glPushMatrix(); //02
		glTranslatef(blockX[1],blockY[1],blockZ[1]);
		cube2();
	glPopMatrix();

	glPushMatrix(); //03
		glTranslatef(blockX[2],blockY[2],blockZ[2]);
		cube2();
	glPopMatrix();

	glPushMatrix();  //04
		glTranslatef(blockX[3],blockY[3],blockZ[3]);
		glRotatef(angle3y,0,1,0);
		cube2();
	glPopMatrix();

	glPushMatrix(); //05
		glTranslatef(blockX[4],blockY[4],blockZ[4]);
		cube2();
	glPopMatrix();

	glPushMatrix(); //06
		glTranslatef(blockX[5],blockY[5],blockZ[5]);
		cube2();
	glPopMatrix();

	//row 1

	glPushMatrix(); //11
		glTranslatef(blockX[6],blockY[6],blockZ[6]);
		glRotatef(angle6y,0,1,0);
		glRotatef(angle6x,1,0,0);
		cube2();
	glPopMatrix();

	glPushMatrix(); //12
		glTranslatef(blockX[7],blockY[7],blockZ[7]);
		glRotatef(angle7y,0,1,0);
		glRotatef(angle7x,1,0,0);
		cube2();
	glPopMatrix();

	glPushMatrix(); //13
		glTranslatef(blockX[8],blockY[8],blockZ[8]);
		glRotatef(angle8y,0,1,0);
		glRotatef(angle8x,1,0,0);
		cube2();
	glPopMatrix();

	glPushMatrix(); //14
		glTranslatef(blockX[9],blockY[9],blockZ[9]);
		glRotatef(angle9,1,0,0);
		cube2();
	glPopMatrix();

	glPushMatrix(); //15
		glTranslatef(blockX[10],blockY[10],blockZ[10]);
		glRotatef(angle10y,0,1,0);
		glRotatef(angle10x,1,0,0);
		cube2();
	glPopMatrix();

	glPushMatrix(); //16
		glTranslatef(blockX[11],blockY[11],blockZ[11]);
		glRotatef(angle11y,0,1,0);
		glRotatef(angle11x,1,0,0);
		cube2();
	glPopMatrix();

	//row 2
	glPushMatrix(); //21
		glTranslatef(blockX[12],blockY[12],blockZ[12]);
		glRotatef(angle12z,0,0,1);
		cube2();
	glPopMatrix();

	glPushMatrix(); //22
		glTranslatef(blockX[13],blockY[13],blockZ[13]);
		glRotatef(angle13z,0,0,1);
		cube2();
	glPopMatrix();

	glPushMatrix(); //23
		glTranslatef(blockX[14],blockY[14],blockZ[14]);
		glRotatef(angle14y,0,1,0);
		glRotatef(angle14x,1,0,0);
		cube2();
	glPopMatrix();

	glPushMatrix(); //24
		glTranslatef(blockX[15],blockY[15],blockZ[15]);
		glRotatef(angle15y,0,1,0);
		glRotatef(angle15x,1,0,0);
		cube2();
	glPopMatrix();

	glPushMatrix(); //25
		glTranslatef(blockX[16],blockY[16],blockZ[16]);
		glRotatef(angle16y,0,1,0);
		glRotatef(angle16x,1,0,0);
		cube2();
	glPopMatrix();

	glPushMatrix(); //26
		glTranslatef(blockX[17],blockY[17],blockZ[17]);
		glRotatef(angle17z,0,0,1);
		cube2();
	glPopMatrix();
}

float currentTime;
float prevtime = 0.0f;
float elapsedTime;
float deltaY9 , deltaZ9;
int block2count = 0;
bool block17 = true;
bool block16 = true;
bool block15 = true;
bool block14 = true;
bool block13 = true;
bool block12 = true;
bool block11 = true;
bool block10 = true;
bool block9 = true;
bool block8 = true;
bool block7 = true;
bool block6 = true;
bool block3 = true;
bool block2 = true;


void animate (int t)
{
	currentTime = getTime();
	//currentTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = currentTime - prevtime;

	cameraControl();

	if(busCords.movecheck == true)
	moveBus();

	if(breakwall == true)
	blockSimulation();

	if(deformation == true)
	busDeformation();


	glutTimerFunc(100,animate,1000);
	prevtime = currentTime;
	glutPostRedisplay();
}

float getTime() 
{
	static __int64 i64Frequency = 0;
	static __int64 i64BeginCount = 0;
	if(i64Frequency == 0) 
	{
		QueryPerformanceFrequency((LARGE_INTEGER*)&i64Frequency);
		QueryPerformanceCounter((LARGE_INTEGER*)&i64BeginCount);
	}
	__int64 i64CurrentCount;
	QueryPerformanceCounter((LARGE_INTEGER*)&i64CurrentCount);
	return (float)(i64CurrentCount - i64BeginCount)/i64Frequency;
}


void blockSimulation(void)
{
		if(block17 == true)
	{
		blockY[17] = blockY[17] + (2*elapsedTime - (0.5*gravity*(elapsedTime*elapsedTime)));
		blockX[17] = blockX[17] + (0.5*elapsedTime);
		angle17z = angle17z - 17* elapsedTime;
		if(blockY[17]< 1)
		{
			blockY[17] =1;
			blockZ[17] = blockZ[17] - (0.1*elapsedTime);
			
			if(angle17z <-270)
			{
				block17 = false;
				angle17z = 360;
			}
			
		}
	}

	if(block16 == true)
	{
		blockY[16] = blockY[16] + (2*elapsedTime - (0.5*gravity*(elapsedTime*elapsedTime)));
		blockZ[16] = blockZ[16] + (0.15*elapsedTime);
		angle16x = angle16x - 11* elapsedTime;
		angle16y = angle16y - 5*elapsedTime;
		if(blockY[16] < 1)
		{
			block16 = false;
			angle16x = 0;
		}
	}

	if(block15 == true)
	{
		blockY[15] = blockY[15] + (2*elapsedTime - (0.5*gravity*(elapsedTime*elapsedTime)));
		blockZ[15] = blockZ[15] - (0.2*elapsedTime);
		angle15x = angle15x - 11* elapsedTime;
		angle15y = angle15y + 5*elapsedTime;
		if(blockY[15] < 1)
		{
			block15 = false;
			angle15x = 0;
		}
	}

	if(block14 == true)
	{
		blockY[14] = blockY[14] + (2*elapsedTime - (0.5*gravity*(elapsedTime*elapsedTime)));
		blockZ[14] = blockZ[14] - (0.3*elapsedTime);
		angle14x = angle14x - 11* elapsedTime;
		angle14y = angle14y + 5*elapsedTime;
		if(blockY[14] < 1)
		{
			block14 = false;
			angle14x = 0;
		}
	}


	if(block13 == true)
	{
		blockY[13] = blockY[13] + (2*elapsedTime - (0.5*gravity*(elapsedTime*elapsedTime)));
		blockZ[13] = blockZ[13] - (0.2*elapsedTime);
		angle13z = angle13z - 15* elapsedTime;
		if(blockY[13] < 1)
		{
			blockY[13] = 1;
			blockZ[13] = blockZ[13] - (0.1*elapsedTime);
			if(angle13z <-270)
			{
				block13 = false;
				angle13z = 360;
			}	
		}
	}

	if(block12 == true)
	{
		blockY[12] = blockY[12] + (2*elapsedTime - (0.5*gravity*(elapsedTime*elapsedTime)));
		blockX[12] = blockX[12] - (0.4*elapsedTime);
		angle12z = angle12z + 15* elapsedTime;
		//if(blockY[12] < 4)
		//{
		//	//blockY[12] = blockY[12] + (3.2*elapsedTime - (0.5*9.5*(elapsedTime*elapsedTime)));;
		//	blockX[12] = blockX[12] - (0.25*elapsedTime);
		//	blockZ[12] = blockZ[12] - (0.1*elapsedTime);
			if(blockY[12]< 1)
			{
				blockY[12] =1;
				blockZ[12] = blockZ[12] - (0.1*elapsedTime);
			
				if(angle12z >270)
				{
					block12 = false;
					angle12z = 360;
				}
			//}
		}
	}

	if(block11 == true)
	{
		blockY[11] = blockY[11] + (2*elapsedTime - (0.5*gravity*(elapsedTime*elapsedTime)));
		blockZ[11] = blockZ[11] - (0.2*elapsedTime);
		blockX[11] = blockX[11] + (0.4*elapsedTime);
		angle11x = angle11x - 15* elapsedTime;
		angle11y = angle11y - 7*elapsedTime;
		if(blockY[11] < 1)
		{
			blockY[11] = 1;
			blockZ[11] = blockZ[11] - (0.1*elapsedTime);
			if(angle11x <-270)
			{
				block11 = false;
				angle11x = 360;
			}	
		}
	}

	if(block10 == true)
	{
		blockY[10] = blockY[10] + (2*elapsedTime - (0.5*gravity*(elapsedTime*elapsedTime)));
		blockZ[10] = blockZ[10] - (0.5*elapsedTime);
		angle10x = angle10x - 15* elapsedTime;
		angle10y = angle10y - 7*elapsedTime;
		if(blockY[10] < 1)
		{
			blockY[10] = 1;
			blockZ[10] = blockZ[10] - (0.1*elapsedTime);
			if(angle10x <-270)
			{
				block10 = false;
				angle10x = 360;
			}	
		}
	}

	if(block9 == true)
	{
		deltaY9 = 2*elapsedTime - (0.5*gravity*(elapsedTime*elapsedTime));
		deltaZ9 = 1.4* elapsedTime;
		blockY[9] = blockY[9] + deltaY9;
		blockZ[9] = blockZ[9] - deltaZ9;
		angle9 = angle9 - 9*elapsedTime;
		if(blockY[9] < 1)
		{
			block9 = false;
			angle9 = 0;
		}

	}

	if(block8 == true)
	{
		blockY[8] = blockY[8] + (2*elapsedTime - (0.5*gravity*(elapsedTime*elapsedTime)));
		blockZ[8] = blockZ[8] - (1.1*elapsedTime);
		angle8x = angle8x - 11* elapsedTime;
		angle8y = angle8y + 5*elapsedTime;
		if(blockY[8] < 1)
		{
			block8 = false;
			angle8x = 0;
		}
	}

	if(block7 == true)
	{
		blockY[7] = blockY[7] + (2*elapsedTime - (0.5*gravity*(elapsedTime*elapsedTime)));
		blockZ[7] = blockZ[7] - (0.3*elapsedTime);
		angle7x = angle7x - 15* elapsedTime;
		angle7y = angle7y + 15*elapsedTime;
		if(blockY[7] < 1)
		{
			blockY[7] = 1;
			blockZ[7] = blockZ[7] - (0.1*elapsedTime);
			if(angle7x <-270)
			{
				block7 = false;
				angle7x = 360;
			}	
		}
	}

	if(block6 == true)
	{
		blockY[6] = blockY[6] + (2*elapsedTime - (0.5*gravity*(elapsedTime*elapsedTime)));
		blockZ[6] = blockZ[6] - (0.2*elapsedTime);
		blockX[6] = blockX[6] - (0.2*elapsedTime);
		angle6x = angle6x - 15* elapsedTime;
		angle6y = angle6y + 12*elapsedTime;
		if(blockY[6] < 1)
		{
			blockY[6] = 1;
			blockZ[6] = blockZ[6] - (0.1*elapsedTime);
			if(angle6x <-270)
			{
				block6 = false;
				angle6x = 360;
			}	
		}
	}

	if(block3 == true)
	{
		if(block2count <2)
		blockZ[3] = blockZ[3] + (0*elapsedTime - (0.5*19.5*(elapsedTime*elapsedTime)));
		angle3y -= 5*elapsedTime;
		if(angle3y <-45)
			block3 = false;
	}

	if(block2 == true)
	{
		block2count++;
		blockZ[2] = blockZ[2] + (0*elapsedTime - (0.5*19.5*(elapsedTime*elapsedTime)));
		if(block2count > 2)
			block2 = false;
	}
}

bool anglecheckbus = true;
void moveBus()
{
	if(anglecheckbus == true)
	{
		busCords.z = busCords.z + 1.5;
		busCords.busAngle++;
		busCords.x = busCords.x + 0.5;
	}
	if(busCords.busAngle > 25)
	{
		anglecheckbus = false;
	}
	if(anglecheckbus == false)
	{
		busCords.z = busCords.z + 1;
		busCords.busAngle = busCords.busAngle - 0.5 ;
		busCords.x = busCords.x - 0.1;
		collisionCount++;
		if(collisionCount > 7)
			busCords.movecheck = false;
			deformation = true;
			breakwall = true;
	}
}

