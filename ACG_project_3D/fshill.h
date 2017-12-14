
/* class defs */

//@@@@@@@@@@@@@@@@@@ IntRect class @@@@@@@@@@@@@@@@
class IntRect{
 public:
  int top, bott, right, left;
};

//@@@@@@@@@@@@@@@@@@ GLintPoint class @@@@@@@@@@@@@@@@
class GLintPoint
{
public:
  int x, y;
};

const int MAX_NUM = 100;

//@@@@@@@@@@@@@@@@@@ GLintPointArray class @@@@@@@@@@@@@@@@
class GLintPointArray 
{
public:
  int num;
  GLintPoint pt[MAX_NUM];
};

//@@@@@@@@@@@@@@@@@@ Point2 class @@@@@@@@@@@@@@@@
class Point2{ // for 2D points with real coordinates
public: 
	float x,y;
	void set(float dx, float dy){x = dx; y = dy;}
	void set(Point2& p){ x = p.x; y = p.y;} 
	Point2(float xx, float yy){x = xx; y = yy;}
	Point2(){x = y = 0;}
};

//@@@@@@@@@@@@@@@@@@ Point3 class @@@@@@@@@@@@@@@@
class Point3{ 
public: 
	float x,y,z;

	void set(float dx, float dy, float dz)
	  {x = dx; y = dy; z = dz;}
	void set(Point3& p)
	  {x = p.x; y = p.y; z = p.z;} 	
	Point3(float xx, float yy, float zz)
	  {x = xx; y = yy; z = zz;}
	Point3()
	  {x = y = z = 0;}
	void build4tuple(float v[])
	{// load 4-tuple with this color: v[3] = 1 for homogeneous
		v[0] = x; v[1] = y; v[2] = z; v[3] = 1.0f;
	}	
};
//@@@@@@@@@@@@@@@@@@ Vector3 class @@@@@@@@@@@@@@@@
class Vector3{ 
public: 
	float x,y,z;

	void set(float dx, float dy, float dz)
	  { 
		  x = dx; y = dy; z = dz;} 
	void set(const Vector3& v)
	  {  
		  x = v.x; y = v.y; z = v.z;}
	void flip()
	  {x = -x; y = -y; z = -z;} // reverse this vector
	void setDiff(Point3& a, Point3& b)//set to difference a - b
	  { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;}
	void normalize()//adjust this vector to unit length
	{		
		double sizeSq = x * x + y * y + z * z;
		if(sizeSq < 0.0000001)
		{
			cerr << "\nnormalize() sees vector (0,0,0)!";
			return; // does nothing to zero vectors;
		}
		float scaleFactor = 1.0/(float)sqrt(sizeSq);
		x *= scaleFactor; y *= scaleFactor; z *= scaleFactor;
	}
	Vector3(float xx, float yy, float zz)
	  {x = xx; y = yy; z = zz;}
	Vector3(const Vector3& v)
	  {x = v.x; y = v.y; z = v.z;}
	Vector3()
	  {x = y = z = 0;} //default constructor
	Vector3 cross(Vector3 b) //return this cross b
	{
	   Vector3 c(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
	   return c;
	}
	float dot(Vector3 b) // return this dotted with b-
	  {return x * b.x + y * b.y + z * b.z;}
	Vector3 operator*(float scalar) // multiply vector by scalar
	  {
	    Vector3 c(scalar*x, scalar*y, scalar*z);
	    return c;
	  }
	Vector3 friend operator*(float scalar,Vector3 v) // multiply vector by scalar
	  {
	    Vector3 c(scalar*v.x, scalar*v.y, scalar*v.z);
	    return c;
	  }
	Vector3 operator+(const Vector3& v)
	  {
	    Vector3 c(x+v.x, y+v.y, z+v.z);
	    return c;
	  }
	Vector3 operator-(const Vector3& v)
	  {
	    Vector3 c(x-v.x, y-v.y, z-v.z);
	    return c;
	  }
};

