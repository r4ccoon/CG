//===========================================================================
// ppmgl2d.h : portable pixel map framebuffer
//===========================================================================
#ifndef _PPMGL2D_H_
#define _PPMGL2D_H_

#include <stdio.h>

struct RGB
{
  unsigned char R,G,B;
};

class ppmGL2d
{
 public:

  RGB* FB;                         // LINEAR PIXEL FRAMEBUFFER
  int Width, Height, NumPixels;    // DIMENSIONS
  unsigned char fgR, fgG, fgB;     // CURRENT FOREGROUND COLOR
  unsigned char bgR, bgG, bgB;     // CURRENT BACKGROUND COLOR


  // THE CONSTRUCTOR: REQUIRES THE DESIRED DIMENSIONS OF THE FRAMEBUFFER
  ppmGL2d(int width=256, int height=256)
  {
    Width=width;
    Height=height;
    NumPixels = Width*Height;       // STORE NUMPIXELS IN FB
    FB = new RGB[NumPixels];        // ALLOCATE FRAMEBUFFER
    SetBackground(0,0,0);           // DEFAULT BACKGROUND COLOR (BLACK)
    SetForeground(1,1,1);           // DEFAULT FOREGROUND COLOR (WHITE)
    ClearColor();
  };

  // THE DESTRUCTOR: FREE THE FRAMEBUFFER
  ~ppmGL2d()
  {
    delete[] FB;
  };

  // CLEAR THE FRAMEBUFFER WITH THE CURRENT BACKGROUND COLOR
  void ClearColor()
  {
    for (int i=0; i<NumPixels; i++)
      { FB[i].R=bgR; FB[i].G=bgG; FB[i].B=bgB; }
  }

  // SET CURRENT FOREGROUND AND BACKGROUND COLORS (normalized values in [0,1])
  void SetBackground(float r, float g, float b)
    { bgR=(unsigned char)(r*255); bgG=(unsigned char)(g*255); bgB=(unsigned char)(b*255); }
  void SetForeground(float r, float g, float b)
    { fgR=(unsigned char)(r*255); fgG=(unsigned char)(g*255); fgB=(unsigned char)(b*255); }

  // PIXEL INDEX GET/SET ROUTINES
  int GetPixelIndex(int x, int y) { return(y*Width+x); }
  void SetPixelIndex(int i) { FB[i].R=fgR; FB[i].G=fgG; FB[i].B=fgB; }

  // SET PIXEL ROUTINE: SETS THE PIXEL AT (X,Y) TO THE CURRENT FOREGROUND COLOR
  void SetPixel(int x, int y)
  {
    int WhichPixel = y*Width+x;
    FB[WhichPixel].R = fgR;
    FB[WhichPixel].G = fgG;
    FB[WhichPixel].B = fgB;
  }

  // WRITES THE FRAMEBUFFER TO A PPM FILE
  void MakePPM(char* FileName)
  {
    FILE* fp = fopen(FileName,"wb");
    fprintf(fp, "P6\n%d %d\n255\n", Width, Height);
    fwrite(FB,1,NumPixels*3,fp);
    fclose(fp);
  };
};

#endif


