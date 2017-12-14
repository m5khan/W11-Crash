

#include "mesh.h"
#include "camera.h"
#include <GL/glut.h>

Camera cam;
Mesh barn;

//<<<<<<<<<<<<<<<<<<<<<<<< mySpecialKeys >>>>>>>>>>>>>>>>>>>>>>
void mySpecialKeys(int key, int x, int y)
{
  switch(key)
  {	
    // controls for camera
  case GLUT_KEY_UP:  cam.pitch(30.0); break; // pitch camera down
  case GLUT_KEY_DOWN: cam.pitch(-30.0); break; // pitch camera up	
  case GLUT_KEY_RIGHT: cam.yaw(-30.0); break; // yaw camera left
  case GLUT_KEY_LEFT: cam.yaw( 30.0); break;  // yaw camera right
  case GLUT_KEY_F1: exit(0);
  }
  glutPostRedisplay(); // draw it again
}

//<<<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>>>>>>>>>
void myKeyboard(unsigned char key, int x, int y)
{
  // NOTE: CTRL-F = 'F' - 64

  switch(key)
  {	
  case 'f': cam.slide(0,0,-0.1); break; // slide camera forward
  case 'b': cam.slide(0,0,0.1);  break; // slide camera back
  case 'l': cam.slide(-0.1,0,0); break;
  case 'r': cam.slide(0.1,0,0);  break;
  case 'u': cam.slide(0,0.1,0);  break;
  case 'd': cam.slide(0,-0.1,0); break;
  case 'm': cam.roll(-1.0); break; // roll counter-clockwise
  case 'n': cam.roll(1.0); break; // roll clockwise
  case 'Q': exit(0);
  default : break;
  }
  glutPostRedisplay(); // draw it again
}

//<<<<<<<<<<<<<<<<<<< axis >>>>>>>>>>>>>>
void axis(double length)
{ // draw a z-axis, with cone at end
	glPushMatrix();
	glBegin(GL_LINES);
	   glVertex3d(0, 0, 0); glVertex3d(0,0,length); // along the z-axis
	glEnd();
	glTranslated(0, 0,length -0.2); 
	glutWireCone(0.04, 0.2, 12, 9);
	glPopMatrix();
}	

void drawaxes(double length)
{  //Draw x,y,z-axes
  glPushMatrix();
    glTranslatef(0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    //glColor3d(1,1,1); // draw white lines
    axis(length);				 // x-axis
    glPushMatrix(); 
    glRotated(90, 0,1.0, 0);
    axis(length);				// y-axis
    glRotated(-90.0, 1, 0, 0);
    axis(length);				// z-axis
  glPopMatrix();	
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displaySolid(void)
{
    

  // SET THE CAMERA

  // PERSPECTIVE
  cam.setShape(50.0, 64.0f/48.0f, 0.1, 100.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  cam.setModelViewMatrix();

  // START DRAWING
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
  	
  drawaxes(2.0);
  glColor3f(0,0,1);
  cam.roll(30);
  
  
  barn.drawMesh();
 

  glutSwapBuffers();
}
//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void main(int argc, char **argv)
{
  char filename[80];
  cout << "enter mesh to view: ";
  
  cin >> filename;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
  glutInitWindowSize(640,480);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("First Mesh");
  glutSpecialFunc(mySpecialKeys);
  glutKeyboardFunc(myKeyboard);
  glutDisplayFunc(displaySolid);
   
 
  
  glClearColor(0.10f, 0.10f, 0.10f,0.0f);  // background is light-gray
  glViewport(0,0,640,480);
  
  // set initial camera position
  barn.readMesh(filename);
  cam.set(2.3, 1.3, 2,     0, 0.25, 0,     0,1,0);
  
  glutMainLoop();
}

 


