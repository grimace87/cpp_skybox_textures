
#include "defs.h"

void PixelOps::InitPanelData() {

	const GLfloat Zcoord = -0.8f;

	// Top panel

	PanelDataArray[2] = Zcoord;
	PanelDataArray[3] = 0.0f;
	PanelDataArray[5] = 1.0f;

	PanelDataArray[8] = Zcoord;
	PanelDataArray[9] = 1.0f;
	PanelDataArray[11] = 1.0f;

	PanelDataArray[14] = Zcoord;
	PanelDataArray[15] = 1.0f;
	PanelDataArray[17] = 1.0f;

	PanelDataArray[20] = Zcoord;
	PanelDataArray[21] = 1.0f;
	PanelDataArray[23] = 1.0f;

	PanelDataArray[26] = Zcoord;
	PanelDataArray[27] = 0.0f;
	PanelDataArray[29] = 1.0f;

	PanelDataArray[32] = Zcoord;
	PanelDataArray[33] = 0.0f;
	PanelDataArray[35] = 1.0f;

	PanelDataArray[38] = Zcoord;
	PanelDataArray[39] = 0.0f;
	PanelDataArray[41] = 1.0f;

	PanelDataArray[44] = Zcoord;
	PanelDataArray[45] = 1.0f;
	PanelDataArray[47] = 1.0f;

	PanelDataArray[50] = Zcoord;
	PanelDataArray[51] = 1.0f;
	PanelDataArray[53] = 0.0f;

	PanelDataArray[56] = Zcoord;
	PanelDataArray[57] = 1.0f;
	PanelDataArray[59] = 0.0f;

	PanelDataArray[62] = Zcoord;
	PanelDataArray[63] = 0.0f;
	PanelDataArray[65] = 0.0f;

	PanelDataArray[68] = Zcoord;
	PanelDataArray[69] = 0.0f;
	PanelDataArray[71] = 1.0f;

	// Middle panel

	PanelDataArray[74] = Zcoord;
	PanelDataArray[75] = 0.0f;
	PanelDataArray[77] = 1.0f;

	PanelDataArray[80] = Zcoord;
	PanelDataArray[81] = 1.0f;
	PanelDataArray[83] = 1.0f;

	PanelDataArray[86] = Zcoord;
	PanelDataArray[87] = 1.0f;
	PanelDataArray[89] = 1.0f;

	PanelDataArray[92] = Zcoord;
	PanelDataArray[93] = 1.0f;
	PanelDataArray[95] = 1.0f;

	PanelDataArray[98] = Zcoord;
	PanelDataArray[99] = 0.0f;
	PanelDataArray[101] = 1.0f;

	PanelDataArray[104] = Zcoord;
	PanelDataArray[105] = 0.0f;
	PanelDataArray[107] = 1.0f;

	// Bottom panel

	PanelDataArray[110] = Zcoord;
	PanelDataArray[111] = 0.0f;
	PanelDataArray[113] = 0.0f;

	PanelDataArray[116] = Zcoord;
	PanelDataArray[117] = 1.0f;
	PanelDataArray[119] = 0.0f;

	PanelDataArray[122] = Zcoord;
	PanelDataArray[123] = 1.0f;
	PanelDataArray[125] = 1.0f;

	PanelDataArray[128] = Zcoord;
	PanelDataArray[129] = 1.0f;
	PanelDataArray[131] = 1.0f;

	PanelDataArray[134] = Zcoord;
	PanelDataArray[135] = 0.0f;
	PanelDataArray[137] = 1.0f;

	PanelDataArray[140] = Zcoord;
	PanelDataArray[141] = 0.0f;
	PanelDataArray[143] = 0.0f;

	PanelDataArray[146] = Zcoord;
	PanelDataArray[147] = 0.0f;
	PanelDataArray[149] = 1.0f;

	PanelDataArray[152] = Zcoord;
	PanelDataArray[153] = 1.0f;
	PanelDataArray[155] = 1.0f;

	PanelDataArray[158] = Zcoord;
	PanelDataArray[159] = 1.0f;
	PanelDataArray[161] = 1.0f;

	PanelDataArray[164] = Zcoord;
	PanelDataArray[165] = 1.0f;
	PanelDataArray[167] = 1.0f;

	PanelDataArray[170] = Zcoord;
	PanelDataArray[171] = 0.0f;
	PanelDataArray[173] = 1.0f;

	PanelDataArray[176] = Zcoord;
	PanelDataArray[177] = 0.0f;
	PanelDataArray[179] = 1.0f;

	// The display of the comp[leted texture

	PanelDataArray[180] = -PanelSize / 2;
	PanelDataArray[181] = PanelMiddleY2 - 1.5f * PanelBottomHeight;
	PanelDataArray[182] = Zcoord;
	PanelDataArray[183] = 0.0f;
	PanelDataArray[184] = 0.0f;
	PanelDataArray[185] = 1.0f;

	PanelDataArray[186] = PanelSize / 2;
	PanelDataArray[187] = PanelMiddleY2 - 1.5f * PanelBottomHeight;
	PanelDataArray[188] = Zcoord;
	PanelDataArray[189] = 1.0f;
	PanelDataArray[190] = 0.0f;
	PanelDataArray[191] = 1.0f;

	PanelDataArray[192] = PanelSize / 2;
	PanelDataArray[193] = PanelMiddleY2 - 1.5f * PanelBottomHeight - PanelSize / 2;
	PanelDataArray[194] = Zcoord;
	PanelDataArray[195] = 1.0f;
	PanelDataArray[196] = 1.0f;
	PanelDataArray[197] = 1.0f;

	PanelDataArray[198] = PanelSize / 2;
	PanelDataArray[199] = PanelMiddleY2 - 1.5f * PanelBottomHeight - PanelSize / 2;
	PanelDataArray[200] = Zcoord;
	PanelDataArray[201] = 1.0f;
	PanelDataArray[202] = 1.0f;
	PanelDataArray[203] = 1.0f;

	PanelDataArray[204] = -PanelSize / 2;
	PanelDataArray[205] = PanelMiddleY2 - 1.5f * PanelBottomHeight - PanelSize / 2;
	PanelDataArray[206] = Zcoord;
	PanelDataArray[207] = 0.0f;
	PanelDataArray[208] = 1.0f;
	PanelDataArray[209] = 1.0f;

	PanelDataArray[210] = -PanelSize / 2;
	PanelDataArray[211] = PanelMiddleY2 - 1.5f * PanelBottomHeight;
	PanelDataArray[212] = Zcoord;
	PanelDataArray[213] = 0.0f;
	PanelDataArray[214] = 0.0f;
	PanelDataArray[215] = 1.0f;

}

void PixelOps::SetPanelData() {

	GLfloat TransT;

	// Top panel

	TransT = (PanelTopTransY - PanelTopY + PanelTopHeight) / PanelTopHeight;

	PanelDataArray[0] = PanelTopX;
	PanelDataArray[1] = PanelTopY;
	PanelDataArray[4] = 1.0f;

	PanelDataArray[6] = PanelTopX + PanelTopWidth;
	PanelDataArray[7] = PanelTopY;
	PanelDataArray[10] = 1.0f;

	PanelDataArray[12] = PanelTopX + PanelTopWidth;
	PanelDataArray[13] = PanelTopTransY;
	PanelDataArray[16] = TransT;

	PanelDataArray[18] = PanelTopX + PanelTopWidth;
	PanelDataArray[19] = PanelTopTransY;
	PanelDataArray[22] = TransT;

	PanelDataArray[24] = PanelTopX;
	PanelDataArray[25] = PanelTopTransY;
	PanelDataArray[28] = TransT;

	PanelDataArray[30] = PanelTopX;
	PanelDataArray[31] = PanelTopY;
	PanelDataArray[34] = 1.0f;

	PanelDataArray[36] = PanelTopX;
	PanelDataArray[37] = PanelTopTransY;
	PanelDataArray[40] = TransT;

	PanelDataArray[42] = PanelTopX + PanelTopWidth;
	PanelDataArray[43] = PanelTopTransY;
	PanelDataArray[46] = TransT;

	PanelDataArray[48] = PanelTopX + PanelTopWidth;
	PanelDataArray[49] = PanelTopY - PanelTopHeight;
	PanelDataArray[52] = 0.0f;

	PanelDataArray[54] = PanelTopX + PanelTopWidth;
	PanelDataArray[55] = PanelTopY - PanelTopHeight;
	PanelDataArray[58] = 0.0f;

	PanelDataArray[60] = PanelTopX;
	PanelDataArray[61] = PanelTopY - PanelTopHeight;
	PanelDataArray[64] = 0.0f;

	PanelDataArray[66] = PanelTopX;
	PanelDataArray[67] = PanelTopTransY;
	PanelDataArray[70] = TransT;

	// Middle panel

	PanelDataArray[72] = -PanelSize;
	PanelDataArray[73] = PanelMiddleY1;
	PanelDataArray[76] = 1.0f;

	PanelDataArray[78] = PanelSize;
	PanelDataArray[79] = PanelMiddleY1;
	PanelDataArray[82] = 1.0f;

	PanelDataArray[84] = PanelSize;
	PanelDataArray[85] = PanelMiddleY2;
	PanelDataArray[88] = 0.0f;

	PanelDataArray[90] = PanelSize;
	PanelDataArray[91] = PanelMiddleY2;
	PanelDataArray[94] = 0.0f;

	PanelDataArray[96] = -PanelSize;
	PanelDataArray[97] = PanelMiddleY2;
	PanelDataArray[100] = 0.0f;

	PanelDataArray[102] = -PanelSize;
	PanelDataArray[103] = PanelMiddleY1;
	PanelDataArray[106] = 1.0f;

	// Bottom panel

	TransT = (PanelBottomTransY - PanelBottomY + PanelBottomHeight) / PanelBottomHeight;

	PanelDataArray[108] = PanelBottomX;
	PanelDataArray[109] = PanelBottomY;
	PanelDataArray[112] = 1.0f;

	PanelDataArray[114] = PanelBottomX + PanelBottomWidth;
	PanelDataArray[115] = PanelBottomY;
	PanelDataArray[118] = 1.0f;

	PanelDataArray[120] = PanelBottomX + PanelBottomWidth;
	PanelDataArray[121] = PanelBottomTransY;
	PanelDataArray[124] = TransT;

	PanelDataArray[126] = PanelBottomX + PanelBottomWidth;
	PanelDataArray[127] = PanelBottomTransY;
	PanelDataArray[130] = TransT;

	PanelDataArray[132] = PanelBottomX;
	PanelDataArray[133] = PanelBottomTransY;
	PanelDataArray[136] = TransT;

	PanelDataArray[138] = PanelBottomX;
	PanelDataArray[139] = PanelBottomY;
	PanelDataArray[142] = 1.0f;

	PanelDataArray[144] = PanelBottomX;
	PanelDataArray[145] = PanelBottomTransY;
	PanelDataArray[148] = TransT;

	PanelDataArray[150] = PanelBottomX + PanelBottomWidth;
	PanelDataArray[151] = PanelBottomTransY;
	PanelDataArray[154] = TransT;

	PanelDataArray[156] = PanelBottomX + PanelBottomWidth;
	PanelDataArray[157] = PanelBottomY - PanelBottomHeight;
	PanelDataArray[160] = 0.0f;

	PanelDataArray[162] = PanelBottomX + PanelBottomWidth;
	PanelDataArray[163] = PanelBottomY - PanelBottomHeight;
	PanelDataArray[166] = 0.0f;

	PanelDataArray[168] = PanelBottomX;
	PanelDataArray[169] = PanelBottomY - PanelBottomHeight;
	PanelDataArray[172] = 0.0f;

	PanelDataArray[174] = PanelBottomX;
	PanelDataArray[175] = PanelBottomTransY;
	PanelDataArray[178] = TransT;

}

void PixelOps::AdjustImage(GLubyte *Src, GLubyte *Dest, DWORD Size, GLfloat Brightness, GLfloat Contrast) {

	GLfloat Calc;

	for (DWORD Count = 0; Count < Size; Count++) {

		Calc = (GLfloat)Src[Count];
		Calc /= 255;
		Calc -= 0.5f;
		Calc *= Contrast * 2.0f;
		Calc += 2.0f * (Brightness - 0.5f);
		Calc += 0.5f;
		if (Calc < 0.0f) Calc = 0.0f;
		if (Calc > 1.0f) Calc = 1.0f;
		Dest[Count] = (GLubyte)(Calc * 255.0f);

	}

}

void PixelOps::SetTexture(GLuint TexID, GLubyte *Data, GLint Width, GLint Height) {

	glBindTexture(GL_TEXTURE_2D, TexID);
	glTexImage2D(
		GL_TEXTURE_2D, 0, 3, Width, Height, 0,
		GL_BGR, GL_UNSIGNED_BYTE, Data
		);

}
