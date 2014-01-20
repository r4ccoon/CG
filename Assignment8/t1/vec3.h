//==========================================================================
// vec3.h : 3d vector class template. Works for any integer or real type.
//==========================================================================
#ifndef _VEC3_H
#define _VEC3_H

#include <stdio.h>
#include <math.h>

template<class Type>
class Vec3
{
  public:
    Type x, y, z;

    Vec3 (void) 
      {};
    Vec3 (const Type X, const Type Y, const Type Z) 
      { x=X; y=Y; z=Z; };
    Vec3 (const Vec3& v) 
      { x=v.x; y=v.y; z=v.z; };
    Vec3 (const Type v[3])
      { x=v[0]; y=v[1]; z=v[2]; };
    void Set (const Type X, const Type Y, const Type Z)
      { x=X; y=Y; z=Z; }
    void Set (const Type v[3])
      { x=v[0]; y=v[1]; z=v[2]; };

    operator Type*()                            // Type * CONVERSION
      { return (Type *)&x; }
    operator const Type*() const                // CONST Type * CONVERSION
      { return &x; }

    int operator == (const Vec3& A) const       // COMPARISON (==)
      { return (x==A.x && y==A.y && z==A.z); }

    int operator != (const Vec3& A) const       // COMPARISON (!=)
      { return (x!=A.x || y!=A.y || z!=A.z); }

    Vec3& operator = (const Vec3& A)            // ASSIGNMENT (=)
      { x=A.x; y=A.y; z=A.z; 
        return(*this);  };
    Vec3 operator + (const Vec3& A) const       // ADDITION (+)
      { Vec3 Sum(x+A.x, y+A.y, z+A.z); 
        return(Sum); };
    Vec3 operator - (const Vec3& A) const       // SUBTRACTION (-)
      { Vec3 Diff(x-A.x, y-A.y, z-A.z);
        return(Diff); };
    Type operator * (const Vec3& A) const       // DOT-PRODUCT (*)
      { Type DotProd = x*A.x+y*A.y+z*A.z; 
        return(DotProd); };
    Vec3 operator / (const Vec3& A) const       // CROSS-PRODUCT (/)
      { Vec3 CrossProd(y*A.z-z*A.y, z*A.x-x*A.z, x*A.y-y*A.x);
        return(CrossProd); };
    Vec3 operator ^ (const Vec3& A) const       // ALSO CROSS-PRODUCT (^)
      { Vec3 CrossProd(y*A.z-z*A.y, z*A.x-x*A.z, x*A.y-y*A.x);
        return(CrossProd); };
    Vec3 operator * (const Type s) const        // MULTIPLY BY SCALAR V*s (*)
      { Vec3 Scaled(x*s, y*s, z*s); 
        return(Scaled); };
    Vec3 operator / (const Type s) const        // DIVIDE BY SCALAR (/)
      { Vec3 Scaled(x/s, y/s, z/s);
        return(Scaled); };
    Vec3 operator & (const Vec3& A) const       // COMPONENT MULTIPLY (&)
      { Vec3 CompMult(x*A.x, y*A.y, z*A.z);
        return(CompMult); }

    friend inline Vec3 operator *(Type s, const Vec3& v)  // SCALAR MULT s*V
      { return Vec3(v.x*s, v.y*s, v.z*s); }

    Vec3& operator += (const Vec3& A)    // ACCUMULATED VECTOR ADDITION (+=)
      { x+=A.x; y+=A.y; z+=A.z;
        return *this;}
    Vec3& operator -= (const Vec3& A)    // ACCUMULATED VECTOR SUBTRACTION (-=)
      { x-=A.x; y-=A.y; z-=A.z; 
        return *this; }
    Vec3& operator *= (const Type s)     // ACCUMULATED SCALAR MULT (*=)
      { x*=s; y*=s; z*=s; 
        return *this; }
    Vec3& operator /= (const Type s)     // ACCUMULATED SCALAR DIV (/=)
      { x/=s; y/=s; z/=s; 
        return *this; }
    Vec3& operator &= (const Vec3& A)    // ACCUMULATED COMPONENT MULTIPLY (&=)
      { x*=A.x; y*=A.y; z*=A.z; return *this; }
    Vec3 operator - (void) const         // NEGATION (-)
      { Vec3 Negated(-x, -y, -z);
        return(Negated); };

/*
    const Type& operator [] (const int i) const // ALLOWS VECTOR ACCESS AS AN ARRAY.
      { return( (i==0)?x:((i==1)?y:z) ); };
    Type & operator [] (const int i)
      { return( (i==0)?x:((i==1)?y:z) ); };
*/

    Type Length (void) const                     // LENGTH OF VECTOR
      { return ((Type)sqrt(x*x+y*y+z*z)); };
    Type LengthSqr (void) const                  // LENGTH OF VECTOR (SQUARED)
      { return (x*x+y*y+z*z); };
    Vec3& Normalize (void)                       // NORMALIZE VECTOR
      { Type L = Length();                       // CALCULATE LENGTH
        if (L>0) { x/=L; y/=L; z/=L; } 
        return *this;
      };                                          // DIV COMPONENTS BY LENGTH

    void UpdateMinMax(Vec3 &Min, Vec3 &Max)
    {
      if (x<Min.x) Min.x=x; else if (x>Max.x) Max.x=x;
      if (y<Min.y) Min.y=y; else if (y>Max.y) Max.y=y;
      if (z<Min.z) Min.z=z; else if (z>Max.z) Max.z=z;
    }

    void Print() const
      { printf("(%.3g, %.3g, %.3g)\n",x, y, z); }

    static Vec3 ZERO;
};

typedef Vec3<float>  Vec3f;
typedef Vec3<double> Vec3d;

template<class Type> Vec3<Type> Vec3<Type>::ZERO = Vec3<Type>(0,0,0);

#endif
