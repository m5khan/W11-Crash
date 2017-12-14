#include <windows.h>
#include <GL/glut.h>
#include "mesh.h"
#include "textures.h"
#include "busCords.h"
#include <stdlib.h>
#include <stdio.h>

#include <iostream>

#define PI 3.1415926535898
using namespace std;

unsigned int texture[18];

//Mesh extrusion;
//Mesh smoothSurface;

Mesh gschool;
Mesh pschool;
Mesh kfc;
Mesh royal;
Mesh bus;
extern busCordinates busCords;


void drawFloor(void );
void drawBundukhan(void);
void drawkfc(void);
void drawnandos(void);
void drawroyal(void);
void drawpizza(void);
void drawbuilding(void);
void cylinderOneStack(int nslice,int nstack,double uMin,double uMax,double vMin,double vMax);
void cube (void);
void drawEnvironment();
void busfront(void);
void busback(void);
void keys(unsigned char key, int x, int y);
void cameraControl (void);
void skyBox(void);

void wall (void);
void animate (int t);
void busDeformation(void);
float getTime() ;
void moveBus();
void goUp(int t);

float ww=800.0, wh=800.0;

//zNear and zFar values
float f = 600.0;
float n = 1.0;
float fov = 89.0;

GLdouble fwwd = 0;
GLdouble altitude = 0;

float deformX =1;

// Camera Handling parameters for perspective view

   // eye  or Camera Position
//static GLdouble viewer[]={-8.0,5.0,4.0};
// GLdouble object[]={50.0,0.0,-40.0}; // look Position
GLdouble viewer[]={50,5,-150};
GLdouble object[]={10.0,5.0,10.0}; 
 GLdouble up[]={0.0,1.0,0.0};      

GLfloat ambient[] = {0.65,0.58,0.47,1};
GLfloat diffuse[] = {0.5,0.45,0.35,0.1};
GLfloat specular[] = {.10,.05,.09,1};
//GLfloat position[] = {20,10,-13,0};
GLfloat position[] = {50,10,-40,0};

GLfloat ambient1[] = {0.039,0.949,0.9648,1};

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
		glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
		glLightfv(GL_LIGHT0,GL_POSITION,position);
		glEnable(GL_LIGHT0);

		

		glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialf(GL_FRONT,GL_SHININESS,1);

	
		//GLdouble viewer[]={50.0,altitude,fwwd};
		//Define Viewing Volume with perspective geometry

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(fov,1.333,n,f);
		
		
		//Place the camera and set target
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(viewer[0],viewer[1],viewer[2],object[0],object[1],object[2],up[0],up[1],up[2]);	


		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		glPushMatrix();
		glRotatef(-90,1,0,0);
		gschool.drawMeshExtrusion();
		pschool.drawMeshExtrusion();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		
		/*glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[1]);*/
		glPushMatrix();
		glRotatef(-90,1,0,0);
		kfc.drawMeshExtrusion();
		glPopMatrix();
		//glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[1]);
		glPushMatrix();
		glRotatef(-90,1,0,0);
		royal.drawMeshExtrusion();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		
		
		drawBundukhan();
		drawkfc();
		drawnandos();
		drawroyal();
		drawpizza();
		drawbuilding();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[9]);
		glPushMatrix();//round about
		glTranslatef(50,0,-40);
		glScalef(8,1,8);
		cylinderOneStack(15,40,0,360,0,180);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glPushMatrix();
		glTranslatef(70,0,-50);
		glRotatef(180,0,1,0);
		wall();
		glPopMatrix();
		
		drawEnvironment();

		//bus
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[14]);
		glPushMatrix();
		glTranslatef(busCords.x,busCords.y,busCords.z);
		glRotatef(busCords.busAngle,0,1,0);
		glScalef(3,3,busCords.scalez);
		glRotatef(225,0,0,1);
		bus.drawMeshSmooth();
		busfront();
		busback();
		glPopMatrix();

		drawFloor();

		//skybox
		glMaterialfv(GL_FRONT,GL_AMBIENT,ambient1);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialf(GL_FRONT,GL_SHININESS,1);
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D,texture[17]);
		glPushMatrix();
		glScalef(200,100,200);
		skyBox();
		glPopMatrix();
		//glDisable(GL_TEXTURE_2D);
		

	//---------------------------Multiple viewports for front, left and side view -----------------
			glutSwapBuffers(); //Double Buffer
}

void myinit()
{
glClearColor (0.0, 0.0, 0.0, 0.0);
glShadeModel(GL_FLAT);
texture[0] = LoadTexture("school.bmp");
texture[1] = LoadTexture("brick.bmp");
texture[2] = LoadTexture("kfc.bmp");
texture[3] = LoadTexture("bundukhan.bmp");
texture[4] = LoadTexture("road.bmp");
texture[5] = LoadTexture("nandos.bmp");
texture[6] = LoadTexture("royal.bmp");
texture[7] = LoadTexture("pizzaexperts.bmp");
texture[8] = LoadTexture("building.bmp");
texture[9] = LoadTexture("grass.bmp");
texture[10] = LoadTexture("building1.bmp");
texture[11] = LoadTexture("building2.bmp");
texture[12] = LoadTexture("building3.bmp");
texture[13] = LoadTexture("building4.bmp");
texture[14] = LoadTexture("bustexture1.bmp");
texture[15] = LoadTexture("busfront.bmp");
texture[16] = LoadTexture("busback.bmp");
texture[17] = LoadTexture("sky.bmp");

//glEnable(GL_TEXTURE_2D);

Point2 gschoolpoints[] = {Point2(0,0),Point2(0,30),Point2(25,0),Point2(25,30),Point2(30,0),Point2(30,20),Point2(40,0),Point2(40,15)};
gschool.extrudedPolygon(gschoolpoints,8,10);
Point2 pschoolpoints[] = {Point2(60,0),Point2(60,15),Point2(70,0),Point2(70,20),Point2(75,0),Point2(75,30),Point2(100,0),Point2(100,30)};
pschool.extrudedPolygon(pschoolpoints,8,12);
Point2 kfcpoints[] = {Point2(60,75),Point2(60,80),Point2(70,70),Point2(70,80),Point2(75,60),Point2(75,80),Point2(85,60),Point2(85,80),Point2(100,60),Point2(100,70)};
kfc.extrudedPolygon(kfcpoints,10,12);
Point2 royalpoints[] = {Point2(0,60),Point2(0,80),Point2(25,60),Point2(25,80),Point2(30,70),Point2(30,80),Point2(40,75),Point2(40,80)};
royal.extrudedPolygon(royalpoints,8,15);

bus.makeBus();
glutTimerFunc(1000,animate,1000);
busCords.x= 50;
busCords.y=1.9;
busCords.z=-100;
busCords.busAngle = 0;
busCords.scalez = 3;
busCords.movecheck = false;
}

void main(int argc, char** argv)
{
glutInit(&argc,argv);

//Set display parameters : double buffer, RGB color, depth buffer
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 

glutInitWindowSize(ww,wh);
glutCreateWindow("Basic Viewing System");
glutInitWindowPosition(300,300);

myinit();

glutDisplayFunc(display);
glutKeyboardFunc(keys);

//ENABLE DEPTH TEST
glEnable(GL_DEPTH_TEST);

//START PROGRAM
glutMainLoop();
}


void drawFloor()
{

GLfloat ambient[] = {0.234375,0.2382124,0.2382124,1};
GLfloat diffuse[] = {0.5,0.45,0.35,0.1};
GLfloat specular[] = {.10,.05,.09,1};

glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialf(GL_FRONT,GL_SHININESS,1);

	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[4]);
		glBegin(GL_QUADS);//floor
		glTexCoord2f(0,0);
		glVertex3f(-100,0,100);
		glTexCoord2f(20,0);
		glVertex3f(200,0,100);
		glTexCoord2f(20,20);
		glVertex3f(200,0,-180);
		glTexCoord2f(0,12);
		glVertex3f(-100,0,-180);
		glEnd();//floorend
		glDisable(GL_TEXTURE_2D);
}


void keys(unsigned char key, int x, int y)
{
if (key=='w' )   //Move to -x direction
fwwd = fwwd - 3;
if (key=='s' ) //Move to +y direction 
fwwd = fwwd+3;
if(key== 'a')
	altitude +=3;
if(key == 'd')
	altitude -=3;

glutPostRedisplay();
}

void drawBundukhan(void)
{
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[3]);
		glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(60,0,-74.8);
		glTexCoord2f(1,1);
		glVertex3f(70,0,-69.8);
		glTexCoord2f(1,0);
		glVertex3f(70,12,-69.8);
		glTexCoord2f(0,0);
		glVertex3f(60,12,-74.8);
		glEnd();
		glDisable(GL_TEXTURE_2D);
}

void drawkfc() 
{
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[2]);
		glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(70,0,-69.8);
		glTexCoord2f(1,1);
		glVertex3f(75,0,-59.8);
		glTexCoord2f(1,0);
		glVertex3f(75,12,-59.8);
		glTexCoord2f(0,0);
		glVertex3f(70,12,-69.8);
		glEnd();
		glDisable(GL_TEXTURE_2D);
}

void drawnandos(void)
{
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[5]);
		glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(75,0,-59.8);
		glTexCoord2f(1,1);
		glVertex3f(100,0,-59.8);
		glTexCoord2f(1,0);
		glVertex3f(100,12,-59.8);
		glTexCoord2f(0,0);
		glVertex3f(75,12,-59.8);
		glEnd();
		glDisable(GL_TEXTURE_2D);
}

void drawroyal(void)
{
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[6]);
		glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(30,0,-69.8);
		glTexCoord2f(1,1);
		glVertex3f(40,0,-74.8);
		glTexCoord2f(1,0);
		glVertex3f(40,15,-74.8);
		glTexCoord2f(0,0);
		glVertex3f(30,15,-69.8);
		glEnd();
		glDisable(GL_TEXTURE_2D);
}

void drawpizza(void)
{
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[7]);
		glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(25,0,-59.8);
		glTexCoord2f(1,1);
		glVertex3f(30,0,-69.8);
		glTexCoord2f(1,0);
		glVertex3f(30,15,-69.8);
		glTexCoord2f(0,0);
		glVertex3f(25,15,-59.8);
		glEnd();
		glDisable(GL_TEXTURE_2D);
}

void drawbuilding(void)
{
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[8]);
		glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex3f(0,0,-59.8);
		glTexCoord2f(1,1);
		glVertex3f(25,0,-59.8);
		glTexCoord2f(1,0);
		glVertex3f(25,15,-59.8);
		glTexCoord2f(0,0);
		glVertex3f(0,15,-59.8);
		glEnd();
		glDisable(GL_TEXTURE_2D);
}

void cylinderOneStack(int nslice,int nstack,double uMin,double uMax,double vMin,double vMax)
{
	double delv,delu,uangle;
	double y1,y2,r1,r2,ct,st;
	int i ,j;

	//delv = ((vMax *(PI/180))-(vMin *(PI/180)))/nstack;
	delu = ((uMax*(PI/180))-(uMin*(PI/180)))/nslice;


	//y1 = vMin;
	y1 = 0;
	r1 = sin(45);
	nstack = 1;
	for (i = 0; i <= nstack ; i++)
	{
		//vMax = vMin + delv;
		//y2 = vMax;
		y2=1;
		r2 = sin(45);
		
		

		glBegin(GL_QUAD_STRIP);
		uangle = 0;
		for(j = 0 ; j <= nslice ; j++)
		{
			ct = cos(uangle);
			st = sin(uangle);

			glColor3f(fabs(ct/2+.5),fabs((y1+y2)/4+0.5),fabs(st/2+0.5));
			glVertex3f(r1*ct,y1,-r1*st);
			glVertex3f(r2*ct,y2,-r2*st);
			glNormal3f(r1*ct,y1,-r1*st);
			glNormal3f(r2*ct,y2,-r2*st);

			uangle+=delu;
		}
		glEnd();
		float textureX , textureY;

		glBegin(GL_POLYGON);
		uangle = 0;
		for(j = 0 ; j <= nslice ; j++)
		{
			ct = cos(uangle);
			st = sin(uangle);

			glColor3f(fabs(ct/2+.5),fabs((y1+y2)/4+0.5),fabs(st/2+0.5));
			textureX = (1+ct) *0.5;
			textureY = ( 1+st)*0.5;
			glTexCoord2f(textureX,textureY);
			glVertex3f(r2*ct,y2,-r2*st);
			glNormal3f(r2*ct,y2,-r2*st);

			uangle+=delu;
		}
		glEnd();
		//vMin = vMax;
		y1 = y2;
		r1 = r2;
	}
}

void cube (void)
{
	//frontface
	glBegin(GL_QUADS);
	glTexCoord2f(1,1);
	glVertex3f(-1,-1,1);
	glNormal3f(0,0,1);
	glTexCoord2f(0,1);
	glVertex3f(1,-1,1);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0);
	glVertex3f(1,1,1);
	glNormal3f(0,0,1);
	glTexCoord2f(1,0);
	glVertex3f(-1,1,1);
	glNormal3f(0,0,1);

	//rightface
	glBegin(GL_QUADS);
	glTexCoord2f(1,1);
	glVertex3f(1,-1,1);
	glNormal3f(1,0,0);
	glTexCoord2f(0,1);
	glVertex3f(1,-1,-1);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0);
	glVertex3f(1,1,-1);
	glNormal3f(1,0,0);
	glTexCoord2f(1,0);
	glVertex3f(1,1,1);
	glNormal3f(1,0,0);

		//leftface
	glBegin(GL_QUADS);
	glTexCoord2f(1,1);
	glVertex3f(-1,-1,-1);
	glNormal3f(-1,0,0);
	glTexCoord2f(0,1);
	glVertex3f(-1,-1,1);
	glNormal3f(-1,0,0);
	glTexCoord2f(0,0);
	glVertex3f(-1,1,1);
	glNormal3f(-1,0,0);
	glTexCoord2f(1,0);
	glVertex3f(-1,1,-1);
	glNormal3f(-1,0,0);

	//backface
	glBegin(GL_QUADS);
	glTexCoord2f(1,1);
	glVertex3f(1,-1,-1);
	glNormal3f(0,0,-1);
	glTexCoord2f(0,1);
	glVertex3f(-1,-1,-1);
	glNormal3f(0,0,-1);
	glTexCoord2f(0,0);
	glVertex3f(-1,1,-1);
	glNormal3f(0,0,-1);
	glTexCoord2f(1,0);
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
	//glTexCoord2f(1,1);
	glVertex3f(1,1,-1);
	glNormal3f(0,1,0);
	//glTexCoord2f(0,1);
	glVertex3f(-1,1,-1);
	glNormal3f(0,1,-0);

	//bottomwall
	/*glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(1,-1,1);
	glNormal3f(0,-1,0);
	glTexCoord2f(1,0);
	glVertex3f(-1,-1,1);
	glNormal3f(0,-1,0);
	glTexCoord2f(1,1);
	glVertex3f(-1,-1,-1);
	glNormal3f(0,-1,0);
	glTexCoord2f(0,1);
	glVertex3f(1,-1,-1);
	glNormal3f(0,-1,-0);*/

	glEnd();
}

void skyBox(void)
{
	//frontface
	glBegin(GL_QUADS);
	glTexCoord2f(1,1);
	glVertex3f(-1,-1,1);
	glNormal3f(0,0,1);
	glTexCoord2f(0,1);
	glVertex3f(1,-1,1);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0);
	glVertex3f(1,1,1);
	glNormal3f(0,0,1);
	glTexCoord2f(1,0);
	glVertex3f(-1,1,1);
	glNormal3f(0,0,1);

	//rightface
	glBegin(GL_QUADS);
	glTexCoord2f(1,1);
	glVertex3f(1,-1,1);
	glNormal3f(1,0,0);
	glTexCoord2f(0,1);
	glVertex3f(1,-1,-1);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0);
	glVertex3f(1,1,-1);
	glNormal3f(1,0,0);
	glTexCoord2f(1,0);
	glVertex3f(1,1,1);
	glNormal3f(1,0,0);

		//leftface
	glBegin(GL_QUADS);
	glTexCoord2f(1,1);
	glVertex3f(-1,-1,-1);
	glNormal3f(-1,0,0);
	glTexCoord2f(0,1);
	glVertex3f(-1,-1,1);
	glNormal3f(-1,0,0);
	glTexCoord2f(0,0);
	glVertex3f(-1,1,1);
	glNormal3f(-1,0,0);
	glTexCoord2f(1,0);
	glVertex3f(-1,1,-1);
	glNormal3f(-1,0,0);

	//backface
	glBegin(GL_QUADS);
	glTexCoord2f(1,1);
	glVertex3f(1,-1,-1);
	glNormal3f(0,0,-1);
	glTexCoord2f(0,1);
	glVertex3f(-1,-1,-1);
	glNormal3f(0,0,-1);
	glTexCoord2f(0,0);
	glVertex3f(-1,1,-1);
	glNormal3f(0,0,-1);
	glTexCoord2f(1,0);
	glVertex3f(1,1,-1);
	glNormal3f(0,0,-1);

	//topwall
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(-1,1,1);
	glNormal3f(0,1,0);
	glTexCoord2f(1,0);
	glVertex3f(1,1,1);
	glNormal3f(0,1,0);
	glTexCoord2f(1,1);
	glVertex3f(1,1,-1);
	glNormal3f(0,1,0);
	glTexCoord2f(0,1);
	glVertex3f(-1,1,-1);
	glNormal3f(0,1,-0);

	//bottomwall
	/*glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex3f(1,-1,1);
	glNormal3f(0,-1,0);
	glTexCoord2f(1,0);
	glVertex3f(-1,-1,1);
	glNormal3f(0,-1,0);
	glTexCoord2f(1,1);
	glVertex3f(-1,-1,-1);
	glNormal3f(0,-1,0);
	glTexCoord2f(0,1);
	glVertex3f(1,-1,-1);
	glNormal3f(0,-1,-0);*/

	glEnd();
}


void drawEnvironment()
{
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[10]);
	glPushMatrix();
	glTranslatef(20,10,25);
	glScalef(15,10,15);
	cube();
		glPushMatrix();
		glTranslatef(4.2,0,1);
		glScalef(1.5,1,1.6);
		cube();
		glPopMatrix();
	glPopMatrix();


	glBindTexture(GL_TEXTURE_2D,texture[8]);
	glPushMatrix();
	glTranslatef(140,7,25);
	glScalef(15,7,15);
	cube();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D,texture[12]);
	glPushMatrix();
	glTranslatef(140,7,-20);
	glScalef(15,7,15);
	cube();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D,texture[13]);
	glPushMatrix();
	glTranslatef(140,16,-70);
	glScalef(16,16,17);
	cube();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D,texture[10]);
	glPushMatrix();
	glTranslatef(90,14,-110);
	glScalef(26,14,17);
	cube();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D,texture[11]);
	glPushMatrix();
	glTranslatef(15,11,-104);
	glScalef(26,11,15);
	cube();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D,texture[12]);
	glPushMatrix();
	glTranslatef(-32,6,-70);
	glScalef(13,6,16);
	cube();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D,texture[11]);
	glPushMatrix();
	glTranslatef(-32,23,-109);
	glScalef(13,23,16);
	cube();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D,texture[13]);
	glPushMatrix();
	glTranslatef(-26,7,0);
	glScalef(13,7,25);
	cube();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


void busfront(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[15]);
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
	glBindTexture(GL_TEXTURE_2D,texture[16]);
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

void busDeformation(void)
{
	if(deformX<20)
	{
		for(int i = 0; i < bus.numVerts ; i++)
		{
			if(i < 50 || i > 85)
			if(i%2 == 0){
				bus.pt[i].x =bus.pt[i].x * sin(deformX);
			}
			//if(i%2 ==0)
				//smoothSurface.pt[i].y =smoothSurface.pt[i].y +sin(deformX);
		}
	}
	deformX+=0.1;
	if(busCords.scalez > 1)
		busCords.scalez -= 0.5;
	glutTimerFunc(10000,goUp,300);
}


bool cam1 = true;
bool cam2 = false;
bool cam3 = false;
float aaa = 0;

void cameraControl()
{
	if(cam1 == true)
	{
		viewer[2]+=3;
		if(viewer[2] > -40)
		{
			cam1 = false;
			cam2 = true;
		}
	}

	else if (cam2 == true)
	{
		object[2] -= 2;
		if(object[2] < -69)
		{
			cam2 = false;
			cam3 = true;
		}
	}

	else if(cam3 == true)
	{
		object[0] += 2;
		if (object[0] >60)
		{
			viewer[1] ++;
			viewer[0] --;
			viewer[2] ++;
			if(viewer[1] >10)
			{
				cam3 = false;
				busCords.movecheck = true;
			}
		}
	}
}


void goUp(int t)
{
	object[0] = 50;
	object[2] = -40;
	for(float i = 0 ; i < 100 ; i += 1)
		viewer[1] = i;
}