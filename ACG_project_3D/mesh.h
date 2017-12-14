
#include <iostream>
#include <fstream>

using namespace std;

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "fshill.h"





//################## class VertexID ################
//used to define a Mesh
class VertexID{

public: int vertIndex, normIndex;

		VertexID(){}
VertexID(int VI,int NI)
{
  vertIndex = VI;
  normIndex = NI;
}

};


//################# class FACE ##############
//used to define a Mesh
class Face{
public:
  int nVerts;
  VertexID * vert; // array of vertex and normal indices
  Face(){ nVerts = 0; vert = NULL;}
  
  Face(int n,VertexID *VI)
  {
    nVerts = n;
	vert = VI;
  
  }
  ~Face(){vert = NULL; nVerts = 0;}
 
  };


class TxtrCoord
{
public: float s,t;
};


//@$@$@$@$@$@$@$@$@$@ Mesh class @$@$@$@$@$@$@$@$@$
class Mesh {
private:
  /*int numVerts,*/ int numNorms, numFaces;
  //Point3 *pt; // array of points
  Vector3 *norm; // array of normals
  Face *face; // array of faces
  int lastVertUsed;
  int lastNormUsed;
  int lastFaceUsed;
public:
	int numVerts;
  char* meshFileName; // holds file name for this Mesh
  TxtrCoord *txtr;
  Point3 *pt; // array of points


  Mesh();
  Mesh(char* fname); // read this file to build mesh
  Mesh(int nv,Point3* v, int nf, Face*f, int nn, Vector3* n);
  void readMesh(char* fname);
  void writeMesh(char* fname);
  void drawMeshExtrusion();
  void drawMeshSmooth();
  void freeMesh();
  int isEmpty(); 
  void makeEmpty();
  void extrudedPolygon(Point2 pp[],int numP,int height);
  Vector3 newell4pts(Point3 a , Point3 b , Point3 c,Point3 d)
  {
	  Vector3 m;
	  m.x = (a.y - b.y)*(a.z + b.z)+(b.y-c.y)*(b.z+ c.z)+(c.y-d.z)*(c.z+d.z)+(d.y-a.y)*(d.z-a.z);
	  m.y = (a.z-b.z)*(a.x+b.x)+(b.z-c.z)*(b.x+c.x)+(c.z-d.z)*(c.x+d.x)+(d.z-a.z)*(d.x+a.x);
	  m.z = (a.x-b.x)*(a.y+b.y)+(b.x-c.x)*(b.y+c.y)+(c.x-d.x)*(c.y+d.y)+(d.x-a.x)*(d.y+a.y);
	return m;
  }

  void makeSurfaceMesh();
  double X(double u,double v);
  double Y(double u,double v);
  double Z(double u,double v);
  double nx(double u,double v);
  double ny(double u,double v);
  double nz(double u,double v);
  void makeBus();
   double busX(double u,double v);
   double busY(double u,double v);
   double busZ(double u,double v);

};







//<<<<<<<<<<<<<<<<<<<<<< Constructors >>>>>>>>>>>>>>>>>>>>

Mesh :: Mesh(){
  numVerts = numFaces = numNorms = 0; 
  pt = NULL; norm  =  NULL; face = NULL;
  lastVertUsed = lastNormUsed = lastFaceUsed = -1;
}

Mesh :: Mesh(char* fname){ // read this file to build mesh
  numVerts = numFaces = numNorms = 0; 
  pt = NULL; norm  =  NULL; face = NULL;
  lastVertUsed = lastNormUsed = lastFaceUsed = -1;
  readMesh(fname);
}

Mesh ::Mesh(int nv,Point3 *v, int nf, Face *f, int nn, Vector3 *n)
{
  numVerts = nv;
  pt=v;

  numFaces = nf;
  face = f;

  numNorms = nn;
  norm = n;


}
//<<<<<<<<<<<<<<<<<<<<<< drawMesh >>>>>>>>>>>>>>>>>>>>
void Mesh :: drawMeshExtrusion()
{ // draw each face of this mesh using OpenGL: draw each polygon.
  if(isEmpty()) return; // mesh is empty
  for( int f = 0; f < numFaces; f++)
    {
      int n = face[f].nVerts;
      
	  //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	  glBegin(GL_POLYGON);
      for(int v = 0; v < n; v++)
	{
	 
	  int iv = face[f].vert[v].vertIndex; assert(iv >= 0 && iv < numVerts);
	  int in = face[f].vert[v].normIndex; assert(in>=0 && in <numNorms );
	  glNormal3f(norm[in].x,norm[in].y,norm[in].z);
	  
	  if(f!=1 && f!= 5 && f!= 9 && f != 3 && f!=7 && f!=11){
		if(v % 4 == 0)
			glTexCoord2f(0,0);
		else if(v%4 == 1)
			glTexCoord2f(1,0);
		if(v%4 == 2)
			glTexCoord2f(1,1);
		if(v%4 == 3)
			glTexCoord2f(0,1);
	  }
	  glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
	}
      glEnd();	
    }
  glBegin(GL_POLYGON);
  glNormal3f(norm[0].x,norm[0].y,norm[0].z);
  glVertex3f(pt[0].x,pt[0].y,pt[0].z);
  glVertex3f(pt[1].x,pt[1].y,pt[1].z);
  glVertex3f(pt[2].x,pt[2].y,pt[2].z);
  glVertex3f(pt[3].x,pt[3].y,pt[3].z);
  glEnd();
  int ii = face[numFaces-1].vert[0].vertIndex+1;
   glBegin(GL_POLYGON);
  glNormal3f(norm[ii+3].x,norm[ii+3].y,norm[ii+3].z);
  glVertex3f(pt[ii].x,pt[ii].y,pt[ii].z);
  glVertex3f(pt[ii+1].x,pt[ii+1].y,pt[ii+1].z);
  glVertex3f(pt[ii+2].x,pt[ii+2].y,pt[ii+2].z);
  glVertex3f(pt[ii+3].x,pt[ii+3].y,pt[ii+3].z);
  glEnd();
  glFlush();
}


void Mesh :: drawMeshSmooth()
{ // draw each face of this mesh using OpenGL: draw each polygon.
  if(isEmpty()) return; // mesh is empty
  for(int f = 0; f < numFaces; f++)
    {
      int n = face[f].nVerts;
      
	  //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	  glBegin(GL_POLYGON);
      for(int v = 0; v < n; v++)
	{
	  int iv = face[f].vert[v].vertIndex; assert(iv >= 0 && iv < numVerts);
	  int in = face[f].vert[v].normIndex; assert(in>=0 && in <numNorms );
	  glNormal3f(norm[in].x,norm[in].y,norm[in].z);
	  glTexCoord2f(txtr[iv].s,txtr[iv].t);
	  glVertex3f(pt[iv].x,pt[iv].y,pt[iv].z);
	}
      glEnd();	
    }
  glFlush();
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<< readMesh >>>>>>>>>>>>>>>>>>>>>>>>
void Mesh:: readMesh(char* fname)
{
  fstream inStream;
  inStream.open(fname, ios ::in); //open needs a c-like string
  if(inStream.fail() || inStream.eof()) 
  {
    cout << "can't open file or eof: " << fname << endl; 
    makeEmpty();return;
  }
  inStream >> numVerts >> numNorms >> numFaces;
  // make arrays for vertices, normals, and faces
  pt = new Point3[numVerts];        assert(pt != NULL);
  norm = new Vector3[numNorms];     assert(norm != NULL);
  face = new Face[numFaces];        assert(face != NULL);
  for(int i = 0; i < numVerts; i++) 	// read in the vertices
    inStream >> pt[i].x >> pt[i].y >> pt[i].z;
  for(int ii = 0; ii < numNorms; ii++) 	// read in the normals
    inStream >> norm[ii].x >> norm[ii].y >> norm[ii].z;
  for(int f = 0; f < numFaces; f++)   // read in face data
    {
      inStream >> face[f].nVerts;
      int n = face[f].nVerts;
      face[f].vert = new VertexID[n]; assert(face[f].vert != NULL);
      for(int k = 0; k < n; k++) 		// read vertex indices for this face
	inStream >> face[f].vert[k].vertIndex;
      for(int kk = 0; kk < n; kk++) 		// read normal indices for this face
	inStream >> face[f].vert[kk].normIndex;
    }
  inStream.close();
} // end of readMesh


//<<<<<<<<<<<<<<<<<<<<<<<<<<<< write mesh>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Mesh:: writeMesh(char * fname)
{ // write this mesh object into a new Chapter 6 format file.
  if(numVerts == 0 || numNorms   == 0 || numFaces == 0) return; //empty
  fstream outStream(fname, ios ::out); // open the output stream
  if(outStream.fail()) {cout << "can't make new file: " << fname << endl; return;}
  outStream << numVerts << " " << numNorms << " " << numFaces << "\n";
  // write the vertex and vertex normal list
  for(int i = 0; i < numVerts; i++)
    outStream << pt[i].x   << " " << pt[i].y   << " " << pt[i].z << "\n";
  for(int ii = 0; ii < numNorms; ii++)
    outStream  << norm[ii].x << " " << norm[ii].y << " " << norm[ii].z << "\n";
  // write the face data
  for(int f = 0; f < numFaces; f++)
    {
      int n = face[f].nVerts;
      outStream << n << "\n";
      for(int v = 0; v < n; v++)// write vertex indices for this face
	outStream << face[f].vert[v].vertIndex << " ";	outStream << "\n";
      for(int k = 0; k < n; k++)	// write normal indices for this face 
	outStream << face[f].vert[k].normIndex << " "; outStream << "\n";
    }
  outStream.close();
}

void Mesh::freeMesh()
{ // free up memory used by this mesh.
  delete [] pt; // release whole vertex list
  delete [] norm;
  for(int f = 0; f < numFaces; f++)
    delete[] face[f].vert; // delete the vert[] array of this face
  delete [] face;
}

int Mesh :: isEmpty()
{return (numVerts == 0) || (numFaces == 0) || (numNorms == 0);}
void Mesh :: makeEmpty()
{ numVerts = numFaces = numNorms = 0;}



void Mesh::extrudedPolygon(Point2 pp[] , int numP,int height)
{
	Point2 * p;
	p = new Point2[numP];
	for(int i = 0 ; i < numP; i ++)
		p[i] =  pp[i];	
	int numPts = numP; //numbeer of points
	int d = height; //depth
	int numSegments = (numPts/2)-1;
	numVerts = numPts*2;
	numFaces = numSegments*4;
	numNorms = numFaces;

	pt = new Point3[numVerts]; assert(pt);
	face = new Face[numFaces]; assert(face);
	norm = new Vector3[numNorms]; assert(norm);
	txtr = new TxtrCoord[numVerts];

	for (int i = 0 ; i <= numSegments ; i++)
	{
		int twoI = 2*i;
		pt[4*i].set(p[twoI].x,p[twoI].y,0);
		pt[4*i+1].set(p[twoI+1].x,p[twoI+1].y,0);
		pt[4*i+2].set(p[2*i+1].x,p[2*i+1].y,d);
		pt[4*i+3].set(p[2*i].x,p[2*i].y,d);

	}

	for(int i = 0 ; i < numSegments ; i++)
		for(int j = 0 ; j < 4 ; j++)
		{
			int which = 4*i+j;

			int i0 = 4*i + j;
			int i1 = i0 +4;
			int i3 = 4*i + (j+3)%4;
			int i2 = i3 + 4;

			norm[which] = newell4pts(pt[i0],pt[i1],pt[i2],pt[i3]);
			norm[which].normalize();

			face[which].vert = new VertexID[4];
			face[which].nVerts = 4;

			face[which].vert[0].vertIndex = i0;
			face[which].vert[1].vertIndex = i1;
			face[which].vert[2].vertIndex = i2;
			face[which].vert[3].vertIndex = i3;

			face[which].vert[0].normIndex = which;
			face[which].vert[1].normIndex = which;
			face[which].vert[2].normIndex = which;
			face[which].vert[3].normIndex = which;
		}
}


void Mesh:: makeSurfaceMesh() 
{
	int i , j,numValsU = 15 , numValsV = 15;
	double u,v,uMin = 0, vMin = 3.1415/2, uMax = 3.1415*2 , vMax = -3.1415*2;

	double delU = (uMax-uMin)/(numValsU-1);
	double delV = (vMax - vMin)/(numValsV-1);

	numVerts = numValsU * numValsV+1;
	numFaces = (numValsU-1)* (numValsV-1);
	numNorms = numVerts;

	pt = new Point3[numVerts]; assert(pt != NULL);
	face = new Face[numFaces]; assert(face != NULL);
	norm = new Vector3[numNorms]; assert(norm != NULL);
	txtr = new TxtrCoord[numVerts];

	for(i = 0 , u = uMin ; i<numValsU ; i++ , u+= delU)
		for(j=0,v = vMin ; j < numValsV ; j++,v+=delV)
		{
			int whichVert = i * numValsV +j;
			pt[whichVert].set(X(u,v),Y(u,v),Z(u,v));

			norm[whichVert].set(nx(u,v),ny(u,v),nz(u,v));
			norm[whichVert].normalize();

			txtr[whichVert].s = ((u-uMin)/(uMax-uMin));
			txtr[whichVert].t = ((v-vMin)/(vMax-vMin));

			if(i>0 && j>0)
			{
				int whichFace = (i-1)*(numValsV-1) +(j-1);
				face[whichFace].vert = new VertexID[4];
				assert(face[whichFace].vert != NULL);
				face[whichFace].nVerts = 4;
				face[whichFace].vert[0].vertIndex = whichVert;
				face[whichFace].vert[0].normIndex = whichVert;
				face[whichFace].vert[1].vertIndex = whichVert-1;
				face[whichFace].vert[1].normIndex = whichVert-1;
				face[whichFace].vert[2].vertIndex = whichVert-numValsV-1;
				face[whichFace].vert[2].normIndex = whichVert-numValsV-1;
				face[whichFace].vert[3].vertIndex = whichVert-numValsV;
				face[whichFace].vert[3].normIndex = whichVert-numValsV;

			}
		}
}

double Mesh::X(double u , double v)
{
	float D = 1; 
	float A = 0.5;

	return ((D + A*cos(v))*cos(u));
}

double Mesh::Y(double u , double v)
{
	float D = 1; 
	float A = 0.5;

	return ((D + A*cos(v))*sin(u));

}

double Mesh::Z(double u , double v)
{
	
	float D = 1; 
	float A = 0.5;

	return (A*sin(v));
}

double Mesh :: nx(double u , double v)
{
	return -cos(u)*cos(v)*cos(u);
}

double Mesh :: ny(double u , double v)
{
	return -cos(u)*cos(v)*sin(u);
}

double Mesh :: nz(double u , double v)
{
	return -cos(u)*cos(v);
}


void Mesh:: makeBus() 
{
	int i , j,numValsU = 5 , numValsV = 20;
	double u,v,uMin = 0, vMin = 3.1415/2, uMax = 3.1415*2 , vMax = -3.1415*2;

	double delU = (uMax-uMin)/(numValsU-1);
	double delV = (vMax - vMin)/(numValsV-1);

	numVerts = numValsU * numValsV+1;
	numFaces = (numValsU-1)* (numValsV-1);
	numNorms = numVerts;

	pt = new Point3[numVerts]; assert(pt != NULL);
	face = new Face[numFaces]; assert(face != NULL);
	norm = new Vector3[numNorms]; assert(norm != NULL);
	txtr = new TxtrCoord[numVerts];

	for(i = 0 , u = uMin ; i<numValsU ; i++ , u+= delU)
		for(j=0,v = vMin ; j < numValsV ; j++,v+=delV)
		{
			int whichVert = i * numValsV +j;
			pt[whichVert].set(busX(u,v),busY(u,v),busZ(u,v));

			norm[whichVert].set(busX(u,v),busY(u,v),busZ(u,v));
			norm[whichVert].normalize();

			txtr[whichVert].s = ((u-uMin)/(uMax-uMin));
			txtr[whichVert].t = ((v-vMin)/(vMax-vMin));

			if(i>0 && j>0)
			{
				int whichFace = (i-1)*(numValsV-1) +(j-1);
				face[whichFace].vert = new VertexID[4];
				assert(face[whichFace].vert != NULL);
				face[whichFace].nVerts = 4;
				face[whichFace].vert[0].vertIndex = whichVert;
				face[whichFace].vert[0].normIndex = whichVert;
				face[whichFace].vert[1].vertIndex = whichVert-1;
				face[whichFace].vert[1].normIndex = whichVert-1;
				face[whichFace].vert[2].vertIndex = whichVert-numValsV-1;
				face[whichFace].vert[2].normIndex = whichVert-numValsV-1;
				face[whichFace].vert[3].vertIndex = whichVert-numValsV;
				face[whichFace].vert[3].normIndex = whichVert-numValsV;

			}
		}
}


double Mesh::busX(double u , double v)
{
	int s = 1;
	return (1+(s-1)*v)*cos(u);
}

double Mesh::busY(double u , double v)
{
	int s = 1;
	return (1+(s-1)*v)*sin(u);
}

double Mesh::busZ(double u , double v)
{
	return v;
}