
// Prevent erros which inhibit use of deprecated functions (eg. strcpy)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

// Request definition of math constants (considered non-C-standard)
#define _USE_MATH_DEFINES

// Include Windows and OpenGL APIs, with other standard tools
#include <Windows.h>
#include <gl/gl.h>
#include "glext.h"
#include <stdio.h>
#include <math.h>

class PixelOps {
public:
	static void InitPanelData();
	static void SetPanelData();
	static void AdjustImage(GLubyte*, GLubyte*, DWORD, GLfloat, GLfloat);
	static void SetTexture(GLuint, GLubyte*, GLint, GLint);
	static void FinaliseTexture();
};

extern BITMAPINFOHEADER BMIH1, BMIH2, BMIH3, BMIH4, BMIH5;

extern GLubyte *PanoDataTop, *PanoDataMiddle, *PanoDataBottom, *TexDataRoof, *TexDataGround;
extern GLubyte *AdjPanoDataTop, *AdjPanoDataBottom, *AdjTexDataRoof, *AdjTexDataGround;
extern GLubyte *JoinTextures, *FinalData;

extern GLfloat PanelScale, PanelSize;
extern GLfloat PanelTopX, PanelTopY, PanelTopWidth, PanelTopHeight;
extern GLfloat PanelTopTransY, PanelTopBrightness, PanelTopContrast;
extern GLfloat PanelMiddleY1, PanelMiddleY2;
extern GLfloat PanelBottomX, PanelBottomY, PanelBottomWidth, PanelBottomHeight;
extern GLfloat PanelBottomTransY, PanelBottomBrightness, PanelBottomContrast;
extern double RoofHeight, RoofTexOverlap;
extern GLfloat *PanelDataArray;

extern GLuint PanoTextureFinal;
