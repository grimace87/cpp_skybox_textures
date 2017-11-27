/**************************
* Includes
*
**************************/

#include "defs.h"

/**************************
* Button alignment
*
**************************/

#define BSX 100
#define BSY 24
#define BGX 10
#define BGY 10

/**************************
* Function Declarations
*
**************************/

HWND hWndMain;
HWND hWndSide;

HWND hWndShiftTopLeft;
HWND hWndShiftTopRight;
HWND hWndShiftTopLeftMin;
HWND hWndShiftTopRightMin;
HWND hWndStretchTopOut;
HWND hWndStretchTopIn;
HWND hWndBrightTopUp;
HWND hWndBrightTopDown;
HWND hWndContrastTopUp;
HWND hWndContrastTopDown;
HWND hWndShiftTopUp;
HWND hWndShiftTopDown;

HWND hWndShiftBottomLeft;
HWND hWndShiftBottomRight;
HWND hWndShiftBottomLeftMin;
HWND hWndShiftBottomRightMin;
HWND hWndStretchBottomOut;
HWND hWndStretchBottomIn;
HWND hWndBrightBottomUp;
HWND hWndBrightBottomDown;
HWND hWndContrastBottomUp;
HWND hWndContrastBottomDown;
HWND hWndShiftBottomUp;
HWND hWndShiftBottomDown;

HWND hWndRoofExtend;
HWND hWndRoofWithdraw;
HWND hWndOverlapIncrease;
HWND hWndOverlapDecrease;
HWND hWndGenFinal;
HWND hWndExport;

LRESULT CALLBACK WndProcMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcPanelShift(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcPanelStretch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcPanelAdjust(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcPanelOverlap(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcFinal(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

WNDPROC PanelTopShiftLeftDefProc;
WNDPROC PanelTopShiftRightDefProc;
WNDPROC PanelTopShiftLeftMinDefProc;
WNDPROC PanelTopShiftRightMinDefProc;
WNDPROC PanelTopStretchOutDefProc;
WNDPROC PanelTopStretchInDefProc;
WNDPROC PanelTopBrightUpDefProc;
WNDPROC PanelTopBrightDownDefProc;
WNDPROC PanelTopContrastUpDefProc;
WNDPROC PanelTopContrastDownDefProc;
WNDPROC PanelTopShiftUpDefProc;
WNDPROC PanelTopShiftDownDefProc;

WNDPROC PanelBottomShiftLeftDefProc;
WNDPROC PanelBottomShiftRightDefProc;
WNDPROC PanelBottomShiftLeftMinDefProc;
WNDPROC PanelBottomShiftRightMinDefProc;
WNDPROC PanelBottomStretchOutDefProc;
WNDPROC PanelBottomStretchInDefProc;
WNDPROC PanelBottomBrightUpDefProc;
WNDPROC PanelBottomBrightDownDefProc;
WNDPROC PanelBottomContrastUpDefProc;
WNDPROC PanelBottomContrastDownDefProc;
WNDPROC PanelBottomShiftUpDefProc;
WNDPROC PanelBottomShiftDownDefProc;

WNDPROC RoofExtendDefProc;
WNDPROC RoofWithdrawDefProc;
WNDPROC OverlapIncreaseDefProc;
WNDPROC OverlapDecreaseDefProc;
WNDPROC GenFinalDefProc;
WNDPROC ExportDefProc;

void EnableOpenGL(HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);
void GetGLFunctions();
int GenerateShaderProgram(HWND hWnd);
void GenerateTextures(HWND hWnd);
void ReadBitmap(
	HWND hWnd, GLubyte **Data1, GLubyte **Data2, const char *Filename, BITMAPFILEHEADER *BMFH, BITMAPINFOHEADER *BMIH);
void ExportBitmap();

PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

GLuint Program;
GLuint PanoTextureTop, PanoTextureMiddle, PanoTextureBottom, TextureRoof, TextureGround;

BITMAPFILEHEADER BMFH1, BMFH2, BMFH3, BMFH4, BMFH5;

GLuint TriMVPMatrixHandle;
GLuint TriMVMatrixHandle;
GLuint TexUniHandle;
GLuint TriPositionHandle;
GLuint TriTexCoordHandle;
GLuint TriTransHandle;

// Global variables, declared extern in header

BITMAPINFOHEADER BMIH1, BMIH2, BMIH3, BMIH4, BMIH5;

GLubyte *PanoDataTop, *PanoDataMiddle, *PanoDataBottom, *TexDataRoof, *TexDataGround;
GLubyte *AdjPanoDataTop, *AdjPanoDataBottom, *AdjTexDataRoof, *AdjTexDataGround;
GLubyte *JoinTextures, *FinalData;

GLfloat PanelScale;
GLfloat PanelSize;
GLfloat PanelTopX;
GLfloat PanelTopY;
GLfloat PanelTopWidth;
GLfloat PanelTopHeight;
GLfloat PanelTopTransY;
GLfloat PanelTopBrightness;
GLfloat PanelTopContrast;
GLfloat PanelMiddleY1;
GLfloat PanelMiddleY2;
GLfloat PanelBottomX;
GLfloat PanelBottomY;
GLfloat PanelBottomWidth;
GLfloat PanelBottomHeight;
GLfloat PanelBottomTransY;
GLfloat PanelBottomBrightness;
GLfloat PanelBottomContrast;
double RoofHeight;
double RoofTexOverlap;
GLfloat *PanelDataArray;

GLuint PanoTextureFinal;

// Custom matrix class

class Matrix {

public:
	float Data[16];

	void CopyData(Matrix *Copy) {
		float* Dat = Copy->Data;
		Data[0] = Dat[0]; Data[1] = Dat[1]; Data[2] = Dat[2]; Data[3] = Dat[3];
		Data[4] = Dat[4]; Data[5] = Dat[5]; Data[6] = Dat[6]; Data[7] = Dat[7];
		Data[8] = Dat[8]; Data[9] = Dat[9]; Data[10] = Dat[10]; Data[11] = Dat[11];
		Data[12] = Dat[12]; Data[13] = Dat[13]; Data[14] = Dat[14]; Data[15] = Dat[15];
	}

	void SetIdentity() {
		Data[0] = 1; Data[1] = 0; Data[2] = 0; Data[3] = 0;
		Data[4] = 0; Data[5] = 1; Data[6] = 0; Data[7] = 0;
		Data[8] = 0; Data[9] = 0; Data[10] = 1; Data[11] = 0;
		Data[12] = 0; Data[13] = 0; Data[14] = 0; Data[15] = 1;
	}

	void SetFrustum(float Left, float Right, float Bottom, float Top, float Near, float Far) {
		Data[0] = (2.0f * Near) / (Right - Left);
		Data[1] = 0.0f;
		Data[2] = (Right + Left) / (Right - Left);
		Data[3] = 0.0f;
		Data[4] = 0.0f;
		Data[5] = 2.0f * Near / (Top - Bottom);
		Data[6] = (Top + Bottom) / (Top - Bottom);
		Data[7] = 0.0f;
		Data[8] = 0.0f;
		Data[9] = 0.0f;
		Data[10] = (Near + Far) / (Near - Far);
		Data[11] = -2.0f * Far * Near / (Far - Near);
		Data[12] = 0.0f;
		Data[13] = 0.0f;
		Data[14] = -1.0f;
		Data[15] = 0.0f;
	}

	void MultiplyMM(Matrix *Mult) {
		Matrix Dup;
		Dup.CopyData(this);
		// Try to improve execution time
		float *DupDat = Dup.Data;
		float *MulDat = Mult->Data;
		// Do it
		Data[0] = DupDat[0] * MulDat[0] + DupDat[1] * MulDat[4] + DupDat[2] * MulDat[8] + DupDat[3] * MulDat[12];
		Data[1] = DupDat[0] * MulDat[1] + DupDat[1] * MulDat[5] + DupDat[2] * MulDat[9] + DupDat[3] * MulDat[13];
		Data[2] = DupDat[0] * MulDat[2] + DupDat[1] * MulDat[6] + DupDat[2] * MulDat[10] + DupDat[3] * MulDat[14];
		Data[3] = DupDat[0] * MulDat[3] + DupDat[1] * MulDat[7] + DupDat[2] * MulDat[11] + DupDat[3] * MulDat[15];
		Data[4] = DupDat[4] * MulDat[0] + DupDat[5] * MulDat[4] + DupDat[6] * MulDat[8] + DupDat[7] * MulDat[12];
		Data[5] = DupDat[4] * MulDat[1] + DupDat[5] * MulDat[5] + DupDat[6] * MulDat[9] + DupDat[7] * MulDat[13];
		Data[6] = DupDat[4] * MulDat[2] + DupDat[5] * MulDat[6] + DupDat[6] * MulDat[10] + DupDat[7] * MulDat[14];
		Data[7] = DupDat[4] * MulDat[3] + DupDat[5] * MulDat[7] + DupDat[6] * MulDat[11] + DupDat[7] * MulDat[15];
		Data[8] = DupDat[8] * MulDat[0] + DupDat[9] * MulDat[4] + DupDat[10] * MulDat[8] + DupDat[11] * MulDat[12];
		Data[9] = DupDat[8] * MulDat[1] + DupDat[9] * MulDat[5] + DupDat[10] * MulDat[9] + DupDat[11] * MulDat[13];
		Data[10] = DupDat[8] * MulDat[2] + DupDat[9] * MulDat[6] + DupDat[10] * MulDat[10] + DupDat[11] * MulDat[14];
		Data[11] = DupDat[8] * MulDat[3] + DupDat[9] * MulDat[7] + DupDat[10] * MulDat[11] + DupDat[11] * MulDat[15];
		Data[12] = DupDat[12] * MulDat[0] + DupDat[13] * MulDat[4] + DupDat[14] * MulDat[8] + DupDat[15] * MulDat[12];
		Data[13] = DupDat[12] * MulDat[1] + DupDat[13] * MulDat[5] + DupDat[14] * MulDat[9] + DupDat[15] * MulDat[13];
		Data[14] = DupDat[12] * MulDat[2] + DupDat[13] * MulDat[6] + DupDat[14] * MulDat[10] + DupDat[15] * MulDat[14];
		Data[15] = DupDat[12] * MulDat[3] + DupDat[13] * MulDat[7] + DupDat[14] * MulDat[11] + DupDat[15] * MulDat[15];

	}

	void RotateY(float theta) {
		float Sin = (float)sin(theta * M_PI / 180);
		float Cos = (float)cos(theta * M_PI / 180);
		Matrix Rote;
		Rote.SetIdentity();
		Rote.Data[0] = Cos;
		Rote.Data[2] = Sin;
		Rote.Data[8] = -Sin;
		Rote.Data[10] = Cos;
		MultiplyMM(&Rote);
	}

};

/**************************
* WinMain
*
**************************/

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int iCmdShow)
{
	WNDCLASS wc;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	BOOL bQuit = FALSE;
	float theta = 0.0f;

	/* register window class */
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProcMain;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"StockWindow";
	RegisterClass(&wc);

	/* create main window */
	hWndMain = CreateWindow(
		L"StockWindow", L"Grimace Skybox Viewer",
		WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
		3 * BGX + 2 * BSX + 10, 0, 18 * BGY + 14 * BSY + 10, 18 * BGY + 14 * BSY + 80,
		NULL, NULL, hInstance, NULL
		);

	// Create other stuff
	hWndSide = CreateWindow(
		L"StockWindow", L"Grimace Skybox Creator",
		WS_CAPTION | WS_VISIBLE | WS_POPUPWINDOW | WS_CHILD,
		0, 0, 3 * BGX + 2 * BSX + 10, 18 * BGY + 14 * BSY + 80,
		hWndMain, NULL, hInstance, NULL
		);
	hWndShiftTopLeft = CreateWindow(
		L"BUTTON", L"Shift Left",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		BGX, BGY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelTopShiftLeftDefProc = (WNDPROC)SetWindowLong(hWndShiftTopLeft, GWL_WNDPROC, (LONG)WndProcPanelShift);
	hWndShiftTopRight = CreateWindow(
		L"BUTTON", L"Shift Right",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		2 * BGX + BSX, BGY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelTopShiftRightDefProc = (WNDPROC)SetWindowLong(hWndShiftTopRight, GWL_WNDPROC, (LONG)WndProcPanelShift);
	hWndShiftTopLeftMin = CreateWindow(
		L"BUTTON", L"Nudge Left",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		BGX, 2 * BGY + BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelTopShiftLeftMinDefProc = (WNDPROC)SetWindowLong(hWndShiftTopLeftMin, GWL_WNDPROC, (LONG)WndProcPanelShift);
	hWndShiftTopRightMin = CreateWindow(
		L"BUTTON", L"Nudge Right",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		2 * BGX + BSX, 2 * BGY + BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelTopShiftRightMinDefProc = (WNDPROC)SetWindowLong(hWndShiftTopRightMin, GWL_WNDPROC, (LONG)WndProcPanelShift);
	hWndStretchTopOut = CreateWindow(
		L"BUTTON", L"Stretch",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		BGX, 3 * BGY + 2 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelTopStretchOutDefProc = (WNDPROC)SetWindowLong(hWndStretchTopOut, GWL_WNDPROC, (LONG)WndProcPanelStretch);
	hWndStretchTopIn = CreateWindow(
		L"BUTTON", L"Shrink",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		2 * BGX + BSX, 3 * BGY + 2 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelTopStretchInDefProc = (WNDPROC)SetWindowLong(hWndStretchTopIn, GWL_WNDPROC, (LONG)WndProcPanelStretch);
	hWndBrightTopUp = CreateWindow(
		L"BUTTON", L"Brighten",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		BGX, 4 * BGY + 3 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelTopBrightUpDefProc = (WNDPROC)SetWindowLong(hWndBrightTopUp, GWL_WNDPROC, (LONG)WndProcPanelAdjust);
	hWndBrightTopDown = CreateWindow(
		L"BUTTON", L"Darken",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		2 * BGX + BSX, 4 * BGY + 3 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelTopBrightDownDefProc = (WNDPROC)SetWindowLong(hWndBrightTopDown, GWL_WNDPROC, (LONG)WndProcPanelAdjust);
	hWndContrastTopUp = CreateWindow(
		L"BUTTON", L"Contrast+",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		BGX, 5 * BGY + 4 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelTopContrastUpDefProc = (WNDPROC)SetWindowLong(hWndContrastTopUp, GWL_WNDPROC, (LONG)WndProcPanelAdjust);
	hWndContrastTopDown = CreateWindow(
		L"BUTTON", L"Contrast-",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		2 * BGX + BSX, 5 * BGY + 4 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelTopContrastDownDefProc = (WNDPROC)SetWindowLong(hWndContrastTopDown, GWL_WNDPROC, (LONG)WndProcPanelAdjust);
	hWndShiftTopUp = CreateWindow(
		L"BUTTON", L"Shift Up",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		BGX, 6 * BGY + 5 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelTopShiftUpDefProc = (WNDPROC)SetWindowLong(hWndShiftTopUp, GWL_WNDPROC, (LONG)WndProcPanelOverlap);
	hWndShiftTopDown = CreateWindow(
		L"BUTTON", L"Shift Down",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		2 * BGX + BSX, 6 * BGY + 5 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelTopShiftDownDefProc = (WNDPROC)SetWindowLong(hWndShiftTopDown, GWL_WNDPROC, (LONG)WndProcPanelOverlap);

	hWndShiftBottomLeft = CreateWindow(
		L"BUTTON", L"Shift Left",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		BGX, 8 * BGY + 6 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelBottomShiftLeftDefProc = (WNDPROC)SetWindowLong(hWndShiftBottomLeft, GWL_WNDPROC, (LONG)WndProcPanelShift);
	hWndShiftBottomRight = CreateWindow(
		L"BUTTON", L"Shift Right",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		2 * BGX + BSX, 8 * BGY + 6 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelBottomShiftRightDefProc = (WNDPROC)SetWindowLong(hWndShiftBottomRight, GWL_WNDPROC, (LONG)WndProcPanelShift);
	hWndShiftBottomLeftMin = CreateWindow(
		L"BUTTON", L"Nudge Left",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		BGX, 9 * BGY + 7 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelBottomShiftLeftMinDefProc = (WNDPROC)SetWindowLong(hWndShiftBottomLeftMin, GWL_WNDPROC, (LONG)WndProcPanelShift);
	hWndShiftBottomRightMin = CreateWindow(
		L"BUTTON", L"Nudge Right",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		2 * BGX + BSX, 9 * BGY + 7 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelBottomShiftRightMinDefProc = (WNDPROC)SetWindowLong(hWndShiftBottomRightMin, GWL_WNDPROC, (LONG)WndProcPanelShift);
	hWndStretchBottomOut = CreateWindow(
		L"BUTTON", L"Stretch",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		BGX, 10 * BGY + 8 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelBottomStretchOutDefProc = (WNDPROC)SetWindowLong(hWndStretchBottomOut, GWL_WNDPROC, (LONG)WndProcPanelStretch);
	hWndStretchBottomIn = CreateWindow(
		L"BUTTON", L"Shrink",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		2 * BGX + BSX, 10 * BGY + 8 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelBottomStretchInDefProc = (WNDPROC)SetWindowLong(hWndStretchBottomIn, GWL_WNDPROC, (LONG)WndProcPanelStretch);
	hWndBrightBottomUp = CreateWindow(
		L"BUTTON", L"Brighten",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		BGX, 11 * BGY + 9 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelBottomBrightUpDefProc = (WNDPROC)SetWindowLong(hWndBrightBottomUp, GWL_WNDPROC, (LONG)WndProcPanelAdjust);
	hWndBrightBottomDown = CreateWindow(
		L"BUTTON", L"Darken",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		2 * BGX + BSX, 11 * BGY + 9 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelBottomBrightDownDefProc = (WNDPROC)SetWindowLong(hWndBrightBottomDown, GWL_WNDPROC, (LONG)WndProcPanelAdjust);
	hWndContrastBottomUp = CreateWindow(
		L"BUTTON", L"Contrast+",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		BGX, 12 * BGY + 10 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelBottomContrastUpDefProc = (WNDPROC)SetWindowLong(hWndContrastBottomUp, GWL_WNDPROC, (LONG)WndProcPanelAdjust);
	hWndContrastBottomDown = CreateWindow(
		L"BUTTON", L"Contrast-",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		2 * BGX + BSX, 12 * BGY + 10 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelBottomContrastDownDefProc = (WNDPROC)SetWindowLong(hWndContrastBottomDown, GWL_WNDPROC, (LONG)WndProcPanelAdjust);
	hWndShiftBottomUp = CreateWindow(
		L"BUTTON", L"Shift Up",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		BGX, 13 * BGY + 11 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelBottomShiftUpDefProc = (WNDPROC)SetWindowLong(hWndShiftBottomUp, GWL_WNDPROC, (LONG)WndProcPanelOverlap);
	hWndShiftBottomDown = CreateWindow(
		L"BUTTON", L"Shift Down",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		2 * BGX + BSX, 13 * BGY + 11 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	PanelBottomShiftDownDefProc = (WNDPROC)SetWindowLong(hWndShiftBottomDown, GWL_WNDPROC, (LONG)WndProcPanelOverlap);

	hWndRoofExtend = CreateWindow(
		L"BUTTON", L"Extend roof/floor",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		BGX, 15 * BGY + 12 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	RoofExtendDefProc = (WNDPROC)SetWindowLong(hWndRoofExtend, GWL_WNDPROC, (LONG)WndProcFinal);
	hWndRoofWithdraw = CreateWindow(
		L"BUTTON", L"Withdraw roof/floor",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		2 * BGX + BSX, 15 * BGY + 12 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	RoofWithdrawDefProc = (WNDPROC)SetWindowLong(hWndRoofWithdraw, GWL_WNDPROC, (LONG)WndProcFinal);
	hWndOverlapIncrease = CreateWindow(
		L"BUTTON", L"Overlap+",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		BGX, 16 * BGY + 13 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	OverlapIncreaseDefProc = (WNDPROC)SetWindowLong(hWndOverlapIncrease, GWL_WNDPROC, (LONG)WndProcFinal);
	hWndOverlapDecrease = CreateWindow(
		L"BUTTON", L"Overlap-",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		2 * BGX + BSX, 16 * BGY + 13 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	OverlapDecreaseDefProc = (WNDPROC)SetWindowLong(hWndOverlapDecrease, GWL_WNDPROC, (LONG)WndProcFinal);
	hWndGenFinal = CreateWindow(
		L"BUTTON", L"Render Skybox",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		BGX, 18 * BGY + 14 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	GenFinalDefProc = (WNDPROC)SetWindowLong(hWndGenFinal, GWL_WNDPROC, (LONG)WndProcFinal);
	hWndExport = CreateWindow(
		L"BUTTON", L"Export Bitmap",
		WS_DLGFRAME | WS_VISIBLE | WS_CHILD,
		2 * BGX + BSX, 18 * BGY + 14 * BSY, BSX, BSY,
		hWndSide, NULL, hInstance, NULL
		);
	ExportDefProc = (WNDPROC)SetWindowLong(hWndExport, GWL_WNDPROC, (LONG)WndProcFinal);

	/* enable OpenGL for the window */
	EnableOpenGL(hWndMain, &hDC, &hRC);
	GetGLFunctions();

	GLfloat BoxSize = 1.8f;
	GLfloat SkyboxVertexData[] = {
		// -z face
		-BoxSize, -BoxSize, -BoxSize, 0.0f,  0.0f, 1.0f,
		BoxSize, -BoxSize, -BoxSize, 0.25f, 0.0f, 1.0f,
		BoxSize,  BoxSize, -BoxSize, 0.25f, 0.5f, 1.0f,
		BoxSize,  BoxSize, -BoxSize, 0.25f, 0.5f, 1.0f,
		-BoxSize,  BoxSize, -BoxSize, 0.0f,  0.5f, 1.0f,
		-BoxSize, -BoxSize, -BoxSize, 0.0f,  0.0f, 1.0f,
		// +x face
		BoxSize, -BoxSize, -BoxSize, 0.25f, 0.0f, 1.0f,
		BoxSize, -BoxSize,  BoxSize, 0.5f,  0.0f, 1.0f,
		BoxSize,  BoxSize,  BoxSize, 0.5f,  0.5f, 1.0f,
		BoxSize,  BoxSize,  BoxSize, 0.5f,  0.5f, 1.0f,
		BoxSize,  BoxSize, -BoxSize, 0.25f, 0.5f, 1.0f,
		BoxSize, -BoxSize, -BoxSize, 0.25f, 0.0f, 1.0f,
		// +z face
		BoxSize, -BoxSize,  BoxSize, 0.5f,  0.0f, 1.0f,
		-BoxSize, -BoxSize,  BoxSize, 0.75f, 0.0f, 1.0f,
		-BoxSize,  BoxSize,  BoxSize, 0.75f, 0.5f, 1.0f,
		-BoxSize,  BoxSize,  BoxSize, 0.75f, 0.5f, 1.0f,
		BoxSize,  BoxSize,  BoxSize, 0.5f,  0.5f, 1.0f,
		BoxSize, -BoxSize,  BoxSize, 0.5f,  0.0f, 1.0f,
		// -x face
		-BoxSize, -BoxSize,  BoxSize, 0.75f, 0.0f, 1.0f,
		-BoxSize, -BoxSize, -BoxSize, 1.0f,  0.0f, 1.0f,
		-BoxSize,  BoxSize, -BoxSize, 1.0f,  0.5f, 1.0f,
		-BoxSize,  BoxSize, -BoxSize, 1.0f,  0.5f, 1.0f,
		-BoxSize,  BoxSize,  BoxSize, 0.75f, 0.5f, 1.0f,
		-BoxSize, -BoxSize,  BoxSize, 0.75f, 0.0f, 1.0f,
		// +y face
		-BoxSize,  BoxSize, -BoxSize, 0.0f,  0.5f, 1.0f,
		BoxSize,  BoxSize, -BoxSize, 0.25f, 0.5f, 1.0f,
		BoxSize,  BoxSize,  BoxSize, 0.25f, 1.0f, 1.0f,
		BoxSize,  BoxSize,  BoxSize, 0.25f, 1.0f, 1.0f,
		-BoxSize,  BoxSize,  BoxSize, 0.0f,  1.0f, 1.0f,
		-BoxSize,  BoxSize, -BoxSize, 0.0f,  0.5f, 1.0f,
		// -y face
		-BoxSize, -BoxSize, -BoxSize, 0.25f, 0.5f, 1.0f,
		-BoxSize, -BoxSize,  BoxSize, 0.25f, 1.0f, 1.0f,
		BoxSize, -BoxSize,  BoxSize, 0.5f,  1.0f, 1.0f,
		BoxSize, -BoxSize,  BoxSize, 0.5f,  1.0f, 1.0f,
		BoxSize, -BoxSize, -BoxSize, 0.5f,  0.5f, 1.0f,
		-BoxSize, -BoxSize, -BoxSize, 0.25f, 0.5f, 1.0f
	};

	// Generate shaders
	GenerateShaderProgram(hWndMain);

	// Read bitmaps
	ReadBitmap(hWndMain, &PanoDataTop, &AdjPanoDataTop, "img/pano_top.bmp", &BMFH1, &BMIH1);
	ReadBitmap(hWndMain, &PanoDataMiddle, NULL, "img/pano_middle.bmp", &BMFH2, &BMIH2);
	ReadBitmap(hWndMain, &PanoDataBottom, &AdjPanoDataBottom, "img/pano_bottom.bmp", &BMFH3, &BMIH3);
	ReadBitmap(hWndMain, &TexDataRoof, &AdjTexDataRoof, "img/tex_roof.bmp", &BMFH4, &BMIH4);
	ReadBitmap(hWndMain, &TexDataGround, &AdjTexDataGround, "img/tex_ground.bmp", &BMFH5, &BMIH5);

	// Check all bitmaps were read
	int ReadAllMaps = 1;
	if (PanoDataTop == NULL) {
		PostQuitMessage(0);
		ReadAllMaps = 0;
	}
	if (PanoDataMiddle == NULL) {
		PostQuitMessage(0);
		ReadAllMaps = 0;
	}
	if (PanoDataBottom == NULL) {
		PostQuitMessage(0);
		ReadAllMaps = 0;
	}
	if (TexDataRoof == NULL) {
		PostQuitMessage(0);
		ReadAllMaps = 0;
	}
	if (TexDataGround == NULL) {
		PostQuitMessage(0);
		ReadAllMaps = 0;
	}

	// Declare matrices
	Matrix ModelMatrix;
	Matrix ViewMatrix;
	Matrix ProjectionMatrix;
	Matrix MVMatrix;
	Matrix MVPMatrix;

	// Generate textures
	if (ReadAllMaps > 0) {
		GenerateTextures(hWndMain);
		if (Program == 0)
			PostQuitMessage(0);
		if (glGetError() != GL_NO_ERROR)
			PostQuitMessage(0);

		TriMVPMatrixHandle = glGetUniformLocation(Program, "u_MVPMatrix");
		TriMVMatrixHandle = glGetUniformLocation(Program, "u_MVMatrix");
		TexUniHandle = glGetUniformLocation(Program, "u_Texture");
		TriPositionHandle = glGetAttribLocation(Program, "a_Position");
		TriTexCoordHandle = glGetAttribLocation(Program, "a_TexCoord");
		TriTransHandle = glGetAttribLocation(Program, "a_Trans");
		glGetError();
		glUseProgram(Program);
		glEnableVertexAttribArray(TriPositionHandle);
		glEnableVertexAttribArray(TriTexCoordHandle);
		glEnableVertexAttribArray(TriTransHandle);

		if (glGetError() != GL_NO_ERROR)
			PostQuitMessage(0);

		ModelMatrix.SetIdentity();
		ViewMatrix.SetIdentity();
		ProjectionMatrix.SetFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 0.9f, 150.0f);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

		// Create panels
		PanelSize = 1.3f;
		PanelScale = (GLfloat)BMIH2.biWidth / (2 * PanelSize);
		PanelMiddleY1 = PanelSize * (GLfloat)BMIH2.biHeight / (GLfloat)BMIH2.biWidth;
		PanelMiddleY2 = -PanelMiddleY1;
		PanelTopWidth = (GLfloat)BMIH1.biWidth / PanelScale;
		PanelTopHeight = (GLfloat)BMIH1.biHeight / PanelScale;
		PanelTopX = -PanelSize;
		PanelTopY = PanelMiddleY1 + PanelTopHeight;
		PanelTopTransY = PanelMiddleY1;
		PanelBottomX = -PanelSize;
		PanelBottomY = PanelMiddleY2;
		PanelBottomWidth = (GLfloat)BMIH3.biWidth / PanelScale;
		PanelBottomHeight = (GLfloat)BMIH3.biHeight / PanelScale;
		PanelBottomTransY = PanelMiddleY2;
		PanelTopBrightness = 0.5f;
		PanelTopContrast = 0.5f;
		PanelBottomBrightness = 0.5f;
		PanelBottomContrast = 0.5f;
		RoofHeight = 0.5;
		RoofTexOverlap = 45.0;

		PanelDataArray = new GLfloat[216];
		PixelOps::InitPanelData();
		PixelOps::SetPanelData();
		JoinTextures = new GLubyte[1];
		FinalData = new GLubyte[393216]; // 3 * 512 * 256
		PixelOps::FinaliseTexture();
	}

	/* program main loop */
	while (!bQuit) {

		/* check for messages */
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

			/* handle or dispatch messages */
			if (msg.message == WM_QUIT)
			{
				bQuit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}
		else {

			glClear(GL_COLOR_BUFFER_BIT);

			theta += 1.0f;
			ModelMatrix.SetIdentity();
			ModelMatrix.RotateY(theta);

			if (theta > 360.0f)
				theta -= 360.0f;

			// Calculate matrices
			MVMatrix.CopyData(&ModelMatrix);
			MVMatrix.MultiplyMM(&ViewMatrix);
			MVPMatrix.CopyData(&MVMatrix);
			MVPMatrix.MultiplyMM(&ProjectionMatrix);

			// Pass in uniform information
			glUniformMatrix4fv(TriMVPMatrixHandle, 1, GL_FALSE, MVPMatrix.Data);
			glUniformMatrix4fv(TriMVMatrixHandle, 1, GL_FALSE, MVMatrix.Data);
			glUniform1i(TexUniHandle, 0);

			// Pass in position and texture coordinate information
			glVertexAttribPointer(TriPositionHandle, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), SkyboxVertexData);
			glVertexAttribPointer(TriTexCoordHandle, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), &SkyboxVertexData[3]);
			glVertexAttribPointer(TriTransHandle, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), &SkyboxVertexData[5]);

			// Draw the skybox
			glBindTexture(GL_TEXTURE_2D, PanoTextureFinal);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			// Calculate matrices
			MVMatrix.SetIdentity();
			MVPMatrix.CopyData(&MVMatrix);
			MVPMatrix.MultiplyMM(&ProjectionMatrix);

			// Pass in uniform information
			glUniformMatrix4fv(TriMVPMatrixHandle, 1, GL_FALSE, MVPMatrix.Data);
			glUniformMatrix4fv(TriMVMatrixHandle, 1, GL_FALSE, MVMatrix.Data);
			glUniform1i(TexUniHandle, 0);

			// Pass in position and texture coordinate information
			glVertexAttribPointer(TriPositionHandle, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), PanelDataArray);
			glVertexAttribPointer(TriTexCoordHandle, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), &PanelDataArray[3]);
			glVertexAttribPointer(TriTransHandle, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), &PanelDataArray[5]);

			// Draw the panels
			glBindTexture(GL_TEXTURE_2D, PanoTextureMiddle);
			glDrawArrays(GL_TRIANGLES, 12, 6);
			glBindTexture(GL_TEXTURE_2D, PanoTextureTop);
			glDrawArrays(GL_TRIANGLES, 0, 12);
			glBindTexture(GL_TEXTURE_2D, PanoTextureBottom);
			glDrawArrays(GL_TRIANGLES, 18, 12);
			glBindTexture(GL_TEXTURE_2D, PanoTextureFinal);
			glDrawArrays(GL_TRIANGLES, 30, 6);

			SwapBuffers(hDC);

			Sleep(10);

		}
	}

	/* shutdown OpenGL */
	DisableOpenGL(hWndMain, hDC, hRC);

	/* destroy the window explicitly */
	DestroyWindow(hWndMain);

	return msg.wParam;
}

LRESULT CALLBACK WndProcMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message)
	{
	case WM_CREATE:
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		return 0;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

void EnableOpenGL(HWND hWnd, HDC *hDC, HGLRC *hRC) {
	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;

	/* get the device context (DC) */
	*hDC = GetDC(hWnd);

	/* set the pixel format for the DC */
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	iFormat = ChoosePixelFormat(*hDC, &pfd);
	SetPixelFormat(*hDC, iFormat, &pfd);

	/* create and enable the render context (RC) */
	*hRC = wglCreateContext(*hDC);
	wglMakeCurrent(*hDC, *hRC);

}

void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC) {
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hWnd, hDC);
}

void GetGLFunctions() {

	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");

}

int GenerateShaderProgram(HWND hWnd) {

	const char* VertexShaderSource =
		"uniform mat4 u_MVPMatrix;"
		"uniform mat4 u_MVMatrix;"
		"attribute vec4 a_Position;"
		"attribute vec2 a_TexCoord;"
		"attribute float a_Trans;"
		"varying vec3 v_Position;"
		"varying vec2 v_TexCoord;"
		"varying float v_Trans;"

		"void main() {"
		"    v_Position = vec3(u_MVMatrix * a_Position);"
		"    v_TexCoord = a_TexCoord;"
		"    v_Trans = a_Trans;"
		"    gl_Position = u_MVPMatrix * a_Position;"
		"}";

	const char* FragmentShaderSource =
		"precision mediump float;"
		"uniform sampler2D u_Texture;"
		"varying vec3 v_Position;"
		"varying vec2 v_TexCoord;"
		"varying float v_Trans;"

		"void main() {"
		"    gl_FragColor = vec4(vec3(texture2D(u_Texture, v_TexCoord)), v_Trans);"
		//"    gl_FragColor = texture2D(u_Texture, v_TexCoord);"
		"}";

	const GLint VertexShaderLength = strlen(VertexShaderSource);
	const GLint FragmentShaderLength = strlen(FragmentShaderSource);

	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(VertexShader, 1, &VertexShaderSource, &VertexShaderLength);
	glShaderSource(FragmentShader, 1, &FragmentShaderSource, &FragmentShaderLength);

	GLint Compiled;
	glCompileShader(VertexShader);
	glCompileShader(FragmentShader);
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Compiled);
	if (Compiled != GL_TRUE) {
		MessageBox(hWnd, L"Failed compilation of vertex shader.", L"Error", MB_OK);
		return 0;
	}
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Compiled);
	if (Compiled != GL_TRUE) {
		MessageBox(hWnd, L"Failed compilation of fragment shader.", L"Error", MB_OK);
		return 0;
	}

	Program = glCreateProgram();
	glAttachShader(Program, VertexShader);
	glAttachShader(Program, FragmentShader);
	glBindAttribLocation(Program, 0, "a_Position");
	glBindAttribLocation(Program, 1, "a_TexCoord");
	glBindAttribLocation(Program, 2, "a_Trans");
	glLinkProgram(Program);
	glGetProgramiv(Program, GL_LINK_STATUS, &Compiled);
	if (Compiled != GL_TRUE) {
		MessageBox(hWnd, L"Failed to link shader program.", L"Error", MB_OK);
		return 0;
	}

	return 1;

}

void GenerateTextures(HWND hWnd) {

	glGenTextures(1, &PanoTextureTop);
	glGenTextures(1, &PanoTextureMiddle);
	glGenTextures(1, &PanoTextureBottom);
	glGenTextures(1, &TextureRoof);
	glGenTextures(1, &TextureGround);
	glGenTextures(1, &PanoTextureFinal);

	glBindTexture(GL_TEXTURE_2D, PanoTextureTop);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D, 0, 3, BMIH1.biWidth, BMIH1.biHeight, 0,
		GL_BGR, GL_UNSIGNED_BYTE, PanoDataTop
		);

	glBindTexture(GL_TEXTURE_2D, PanoTextureMiddle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D, 0, 3, BMIH2.biWidth, BMIH2.biHeight, 0,
		GL_BGR, GL_UNSIGNED_BYTE, PanoDataMiddle
		);

	glBindTexture(GL_TEXTURE_2D, PanoTextureBottom);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D, 0, 3, BMIH3.biWidth, BMIH3.biHeight, 0,
		GL_BGR, GL_UNSIGNED_BYTE, PanoDataBottom
		);

	glBindTexture(GL_TEXTURE_2D, TextureRoof);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D, 0, 3, BMIH4.biWidth, BMIH4.biHeight, 0,
		GL_BGR, GL_UNSIGNED_BYTE, TexDataRoof
		);

	glBindTexture(GL_TEXTURE_2D, TextureGround);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D, 0, 3, BMIH5.biWidth, BMIH5.biHeight, 0,
		GL_BGR, GL_UNSIGNED_BYTE, TexDataGround
		);

	return;

}

void ReadBitmap(
	HWND hWnd, GLubyte **Data1, GLubyte **Data2, const char *Filename, BITMAPFILEHEADER *BMFH, BITMAPINFOHEADER *BMIH) {

	*Data1 = NULL;
	WCHAR GetUnicodeText[20];
	MultiByteToWideChar(0, 0, Filename, -1, GetUnicodeText, 20);

	GLubyte* PixelData;

	FILE *InputBMP = fopen(Filename, "rb");
	if (InputBMP == NULL) {
		MessageBox(hWnd, GetUnicodeText, L"Error - file not found", MB_OK);
		return;
	}

	fread(BMFH, sizeof(BITMAPFILEHEADER), 1, InputBMP);
	if (BMFH->bfType != 19778) {
		MessageBox(hWnd, GetUnicodeText, L"Error - doesn't appear to be a valid bitmap", MB_OK);
		fclose(InputBMP);
		return;
	}

	fread(BMIH, sizeof(BITMAPINFOHEADER), 1, InputBMP);
	if (BMIH->biBitCount != 24) {
		MessageBox(hWnd, GetUnicodeText, L"Error - must be a 24-bit bitmap", MB_OK);
		fclose(InputBMP);
		return;
	}

	// Find how much padding is in each row (data is padded to a multiple of 4 bytes on each row)
	LONG PadBytes = (BMIH->biWidth * 3) % 4;
	PadBytes = (4 - PadBytes) % 4;
	if (PadBytes != 0) {
		MessageBox(hWnd, GetUnicodeText, L"Error - width must be a multiple of 4", MB_OK);
		fclose(InputBMP);
		return;
	}

	// Allocate the required buffer and read in bitmap data
	const DWORD Size = BMFH->bfSize - BMFH->bfOffBits;
	*Data1 = new GLubyte[Size];
	fread(*Data1, sizeof(GLbyte), Size, InputBMP);

	// Copy to second buffer
	if (Data2 != NULL) {
		DWORD PixCount;
		*Data2 = new GLubyte[Size];
		for (PixCount = 0; PixCount < Size; PixCount++)
			(*Data2)[PixCount] = (*Data1)[PixCount];
	}

	fclose(InputBMP);

}

LRESULT CALLBACK WndProcPanelShift(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam) {

	if (hWnd == hWndShiftTopLeft) {
		if (message == WM_LBUTTONDOWN) {
			PanelTopX -= 0.02f;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelTopShiftLeftDefProc, hWndShiftTopLeft, message, wParam, lParam);
	}
	else if (hWnd == hWndShiftTopRight) {
		if (message == WM_LBUTTONDOWN) {
			PanelTopX += 0.02f;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelTopShiftRightDefProc, hWndShiftTopRight, message, wParam, lParam);
	}
	else if (hWnd == hWndShiftTopLeftMin) {
		if (message == WM_LBUTTONDOWN) {
			PanelTopX -= 0.002f;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelTopShiftLeftMinDefProc, hWndShiftTopLeftMin, message, wParam, lParam);
	}
	else if (hWnd == hWndShiftTopRightMin) {
		if (message == WM_LBUTTONDOWN) {
			PanelTopX += 0.002f;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelTopShiftRightMinDefProc, hWndShiftTopRightMin, message, wParam, lParam);
	}
	else if (hWnd == hWndShiftBottomLeft) {
		if (message == WM_LBUTTONDOWN) {
			PanelBottomX -= 0.02f;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelBottomShiftLeftDefProc, hWndShiftBottomLeft, message, wParam, lParam);
	}
	else if (hWnd == hWndShiftBottomRight) {
		if (message == WM_LBUTTONDOWN) {
			PanelBottomX += 0.02f;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelBottomShiftRightDefProc, hWndShiftBottomRight, message, wParam, lParam);
	}
	else if (hWnd == hWndShiftBottomLeftMin) {
		if (message == WM_LBUTTONDOWN) {
			PanelBottomX -= 0.002f;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelBottomShiftLeftMinDefProc, hWndShiftBottomLeftMin, message, wParam, lParam);
	}
	else if (hWnd == hWndShiftBottomRightMin) {
		if (message == WM_LBUTTONDOWN) {
			PanelBottomX += 0.002f;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelBottomShiftRightMinDefProc, hWndShiftBottomRightMin, message, wParam, lParam);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);

}

LRESULT CALLBACK WndProcPanelStretch(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam) {

	if (hWnd == hWndStretchTopIn) {
		if (message == WM_LBUTTONDOWN) {
			PanelTopWidth -= 0.01f;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelTopStretchInDefProc, hWndStretchTopIn, message, wParam, lParam);
	}
	else if (hWnd == hWndStretchTopOut) {
		if (message == WM_LBUTTONDOWN) {
			PanelTopWidth += 0.01f;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelTopStretchOutDefProc, hWndStretchTopOut, message, wParam, lParam);
	}
	else if (hWnd == hWndStretchBottomIn) {
		if (message == WM_LBUTTONDOWN) {
			PanelBottomWidth -= 0.01f;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelBottomStretchInDefProc, hWndStretchBottomIn, message, wParam, lParam);
	}
	else if (hWnd == hWndStretchBottomOut) {
		if (message == WM_LBUTTONDOWN) {
			PanelBottomWidth += 0.01f;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelBottomStretchOutDefProc, hWndStretchBottomOut, message, wParam, lParam);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);

}

LRESULT CALLBACK WndProcPanelAdjust(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam) {

	if (hWnd == hWndBrightTopUp) {
		if (message == WM_LBUTTONDOWN) {
			PanelTopBrightness += 0.02f;
			if (PanelTopBrightness > 1.0f) PanelTopBrightness = 1.0f;
			PixelOps::AdjustImage(
				PanoDataTop, AdjPanoDataTop, BMFH1.bfSize - BMFH1.bfOffBits, PanelTopBrightness, PanelTopContrast
				);
			PixelOps::SetTexture(PanoTextureTop, AdjPanoDataTop, BMIH1.biWidth, BMIH1.biHeight);
			return 0;
		}
		return CallWindowProc(PanelTopBrightUpDefProc, hWndBrightTopUp, message, wParam, lParam);
	}
	else if (hWnd == hWndBrightTopDown) {
		if (message == WM_LBUTTONDOWN) {
			PanelTopBrightness -= 0.02f;
			if (PanelTopBrightness < 0.0f) PanelTopBrightness = 0.0f;
			PixelOps::AdjustImage(
				PanoDataTop, AdjPanoDataTop, BMFH1.bfSize - BMFH1.bfOffBits, PanelTopBrightness, PanelTopContrast
				);
			PixelOps::SetTexture(PanoTextureTop, AdjPanoDataTop, BMIH1.biWidth, BMIH1.biHeight);
			return 0;
		}
		return CallWindowProc(PanelTopBrightDownDefProc, hWndBrightTopDown, message, wParam, lParam);
	}
	else if (hWnd == hWndContrastTopUp) {
		if (message == WM_LBUTTONDOWN) {
			PanelTopContrast += 0.02f;
			if (PanelTopContrast > 1.0f) PanelTopContrast = 1.0f;
			PixelOps::AdjustImage(
				PanoDataTop, AdjPanoDataTop, BMFH1.bfSize - BMFH1.bfOffBits, PanelTopBrightness, PanelTopContrast
				);
			PixelOps::SetTexture(PanoTextureTop, AdjPanoDataTop, BMIH1.biWidth, BMIH1.biHeight);
			return 0;
		}
		return CallWindowProc(PanelTopContrastUpDefProc, hWndContrastTopUp, message, wParam, lParam);
	}
	else if (hWnd == hWndContrastTopDown) {
		if (message == WM_LBUTTONDOWN) {
			PanelTopContrast -= 0.02f;
			if (PanelTopContrast < 0.0f) PanelTopContrast = 0.0f;
			PixelOps::AdjustImage(
				PanoDataTop, AdjPanoDataTop, BMFH1.bfSize - BMFH1.bfOffBits, PanelTopBrightness, PanelTopContrast
				);
			PixelOps::SetTexture(PanoTextureTop, AdjPanoDataTop, BMIH1.biWidth, BMIH1.biHeight);
			return 0;
		}
		return CallWindowProc(PanelTopContrastDownDefProc, hWndContrastTopDown, message, wParam, lParam);
	}
	if (hWnd == hWndBrightBottomUp) {
		if (message == WM_LBUTTONDOWN) {
			PanelBottomBrightness += 0.02f;
			if (PanelBottomBrightness > 1.0f) PanelBottomBrightness = 1.0f;
			PixelOps::AdjustImage(
				PanoDataBottom, AdjPanoDataBottom, BMFH3.bfSize - BMFH3.bfOffBits, PanelBottomBrightness, PanelBottomContrast
				);
			PixelOps::SetTexture(PanoTextureBottom, AdjPanoDataBottom, BMIH3.biWidth, BMIH3.biHeight);
			return 0;
		}
		return CallWindowProc(PanelBottomBrightUpDefProc, hWndBrightBottomUp, message, wParam, lParam);
	}
	else if (hWnd == hWndBrightBottomDown) {
		if (message == WM_LBUTTONDOWN) {
			PanelBottomBrightness -= 0.02f;
			if (PanelBottomBrightness < 0.0f) PanelBottomBrightness = 0.0f;
			PixelOps::AdjustImage(
				PanoDataBottom, AdjPanoDataBottom, BMFH3.bfSize - BMFH3.bfOffBits, PanelBottomBrightness, PanelBottomContrast
				);
			PixelOps::SetTexture(PanoTextureBottom, AdjPanoDataBottom, BMIH3.biWidth, BMIH3.biHeight);
			return 0;
		}
		return CallWindowProc(PanelBottomBrightDownDefProc, hWndBrightBottomDown, message, wParam, lParam);
	}
	else if (hWnd == hWndContrastBottomUp) {
		if (message == WM_LBUTTONDOWN) {
			PanelBottomContrast += 0.02f;
			if (PanelBottomContrast > 1.0f) PanelBottomContrast = 1.0f;
			PixelOps::AdjustImage(
				PanoDataBottom, AdjPanoDataBottom, BMFH3.bfSize - BMFH3.bfOffBits, PanelBottomBrightness, PanelBottomContrast
				);
			PixelOps::SetTexture(PanoTextureBottom, AdjPanoDataBottom, BMIH3.biWidth, BMIH3.biHeight);
			return 0;
		}
		return CallWindowProc(PanelBottomContrastUpDefProc, hWndContrastBottomUp, message, wParam, lParam);
	}
	else if (hWnd == hWndContrastBottomDown) {
		if (message == WM_LBUTTONDOWN) {
			PanelBottomContrast -= 0.02f;
			if (PanelBottomContrast < 0.0f) PanelBottomContrast = 0.0f;
			PixelOps::AdjustImage(
				PanoDataBottom, AdjPanoDataBottom, BMFH3.bfSize - BMFH3.bfOffBits, PanelBottomBrightness, PanelBottomContrast
				);
			PixelOps::SetTexture(PanoTextureBottom, AdjPanoDataBottom, BMIH3.biWidth, BMIH3.biHeight);
			return 0;
		}
		return CallWindowProc(PanelBottomContrastDownDefProc, hWndContrastBottomDown, message, wParam, lParam);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);

}

LRESULT CALLBACK WndProcPanelOverlap(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam) {

	if (hWnd == hWndShiftTopUp) {
		if (message == WM_LBUTTONDOWN) {
			PanelTopY += 0.01f;
			if (PanelTopY > PanelMiddleY1 + PanelTopHeight) PanelTopY = PanelMiddleY1 + PanelTopHeight;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelTopShiftUpDefProc, hWndShiftTopUp, message, wParam, lParam);
	}
	else if (hWnd == hWndShiftTopDown) {
		if (message == WM_LBUTTONDOWN) {
			PanelTopY -= 0.01f;
			if (PanelTopY < PanelMiddleY1) PanelTopY = PanelMiddleY1;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelTopShiftDownDefProc, hWndShiftTopDown, message, wParam, lParam);
	}
	else if (hWnd == hWndShiftBottomUp) {
		if (message == WM_LBUTTONDOWN) {
			PanelBottomY += 0.01f;
			if (PanelBottomY > PanelMiddleY2 + PanelBottomHeight) PanelBottomY = PanelMiddleY2 + PanelBottomHeight;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelBottomShiftUpDefProc, hWndShiftBottomUp, message, wParam, lParam);
	}
	else if (hWnd == hWndShiftBottomDown) {
		if (message == WM_LBUTTONDOWN) {
			PanelBottomY -= 0.01f;
			if (PanelBottomY < PanelMiddleY2) PanelBottomY = PanelMiddleY2;
			PixelOps::SetPanelData();
			return 0;
		}
		return CallWindowProc(PanelBottomShiftDownDefProc, hWndShiftBottomDown, message, wParam, lParam);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);

}

LRESULT CALLBACK WndProcFinal(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam) {

	if (hWnd == hWndRoofExtend) {
		if (message == WM_LBUTTONDOWN) {
			RoofHeight += 0.1f;
			if (RoofHeight > 10.0f)
				RoofHeight = 10.0f;
			PixelOps::FinaliseTexture();
			return 0;
		}
		return CallWindowProc(RoofExtendDefProc, hWndRoofExtend, message, wParam, lParam);
	}
	else if (hWnd == hWndRoofWithdraw) {
		if (message == WM_LBUTTONDOWN) {
			RoofHeight -= 0.1f;
			if (RoofHeight < 0.1f)
				RoofHeight = 0.1f;
			PixelOps::FinaliseTexture();
			return 0;
		}
		return CallWindowProc(RoofWithdrawDefProc, hWndRoofWithdraw, message, wParam, lParam);
	}
	else if (hWnd == hWndOverlapIncrease) {
		if (message == WM_LBUTTONDOWN) {
			RoofTexOverlap += 10;
			if (RoofTexOverlap > 150)
				RoofTexOverlap = 150;
			PixelOps::FinaliseTexture();
			return 0;
		}
		return CallWindowProc(OverlapIncreaseDefProc, hWndOverlapIncrease, message, wParam, lParam);
	}
	else if (hWnd == hWndOverlapDecrease) {
		if (message == WM_LBUTTONDOWN) {
			RoofTexOverlap -= 10;
			if (RoofTexOverlap < 0)
				RoofTexOverlap = 0;
			PixelOps::FinaliseTexture();
			return 0;
		}
		return CallWindowProc(OverlapDecreaseDefProc, hWndOverlapDecrease, message, wParam, lParam);
	}
	else if (hWnd == hWndGenFinal) {
		if (message == WM_LBUTTONDOWN) {
			PixelOps::FinaliseTexture();
			return 0;
		}
		return CallWindowProc(GenFinalDefProc, hWndGenFinal, message, wParam, lParam);
	}
	else if (hWnd == hWndExport) {
		if (message == WM_LBUTTONDOWN) {
			ExportBitmap();
			return 0;
		}
		return CallWindowProc(ExportDefProc, hWndExport, message, wParam, lParam);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);

}

void ExportBitmap() {

	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;

	bmfh.bfType = 19778;
	bmfh.bfSize = 512 * 256 * 3 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = 512;
	bmih.biHeight = 256;
	bmih.biPlanes = 1;
	bmih.biBitCount = 24;
	bmih.biCompression = BI_RGB;
	bmih.biSizeImage = 0;
	bmih.biXPelsPerMeter = 4096;
	bmih.biYPelsPerMeter = 4096;
	bmih.biClrUsed = 0;
	bmih.biClrImportant = 0;

	FILE *OutputFile = fopen("img/Output.bmp", "wb");
	if (OutputFile == NULL) {
		MessageBox(hWndMain, L"Error creating output file.", L"Error", MB_OK);
		return;
	}

	fwrite(&bmfh, sizeof(BITMAPFILEHEADER), 1, OutputFile);
	fwrite(&bmih, sizeof(BITMAPINFOHEADER), 1, OutputFile);
	fwrite(FinalData, 1, 393216, OutputFile);

	fclose(OutputFile);

	MessageBox(hWndMain, L"Bitmap created.", L"Success", MB_OK);

}
