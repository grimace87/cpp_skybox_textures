
#include "defs.h"

void PixelOps::FinaliseTexture() {

	float Num, Den;

	long X, Y;
	long SrcIndex;
	long DestIndex;

	long PanelTopXL = (long)(PanelScale * (PanelTopX + PanelSize));
	long PanelTopWidthL = (long)(PanelScale * PanelTopWidth);
	long PanelTopOpaqueHeightL = (long)(PanelScale * (PanelTopY - PanelTopTransY));
	long PanelTopTransHeightL = (long)(PanelScale * (PanelTopTransY - PanelTopY + PanelTopHeight));
	long PanelTopTotalHeightL = PanelTopOpaqueHeightL + PanelTopTransHeightL;
	long PanelMiddleHeightL = BMIH2.biHeight;
	long PanelMiddleWidthL = BMIH2.biWidth;
	long PanelBottomXL = (long)(PanelScale * (PanelBottomX + PanelSize));
	long PanelBottomWidthL = (long)(PanelScale * PanelBottomWidth);
	long PanelBottomOpaqueHeightL = (long)(PanelScale * (PanelBottomTransY - PanelBottomY + PanelBottomHeight));
	long PanelBottomTransHeightL = (long)(PanelScale * (PanelBottomY - PanelBottomTransY));
	long PanelBottomTotalHeightL = PanelBottomOpaqueHeightL + PanelBottomTransHeightL;

	float PanelTopWidthF = (float)PanelTopWidthL;

	long TotalWidthL = PanelMiddleWidthL;
	long TotalHeightL = PanelTopOpaqueHeightL + BMIH2.biHeight + PanelBottomOpaqueHeightL;

	delete[] JoinTextures;
	JoinTextures = new GLubyte[4 * TotalWidthL * TotalHeightL];

	float Brigh, Contr;
	float Colour, Alpha, OneMinusAlpha;

	double Xd, Yd;

	// Copy middle panel into temporary texture
	for (Y = 0; Y < PanelMiddleHeightL; Y++) {
		for (X = 0; X < TotalWidthL; X++) {
			SrcIndex = 3 * (Y * TotalWidthL + X);
			DestIndex = SrcIndex + 3 * (TotalWidthL * PanelBottomOpaqueHeightL);
			JoinTextures[DestIndex++] = PanoDataMiddle[SrcIndex++];
			JoinTextures[DestIndex++] = PanoDataMiddle[SrcIndex++];
			JoinTextures[DestIndex] = PanoDataMiddle[SrcIndex];
		}
	}

	// Copy top panel (copied to bottom of new texture since they're inverted in memory)
	Brigh = 2.0f * ((float)PanelTopBrightness - 0.5f);
	Contr = (float)PanelTopContrast * 2.0f;
	// Opaque section
	for (Y = 0; Y < PanelTopOpaqueHeightL; Y++) {
		for (X = 0; X < TotalWidthL; X++) {
			Num = (float)(X - PanelTopXL);
			Den = (float)PanelTopWidthL;
			Num /= Den;
			Num += 1.0f; // Will usually be countered by modulo below
			Num *= (float)BMIH1.biWidth;
			SrcIndex = 3 * (((long)Num) % BMIH1.biWidth + ((Y + PanelTopTransHeightL) * BMIH1.biWidth));
			DestIndex = 3 * ((Y + PanelBottomOpaqueHeightL + PanelMiddleHeightL) * TotalWidthL + X);
			Colour = ((float)PanoDataTop[SrcIndex++] / 255.0f - 0.5f) * Contr + Brigh + 0.5f;
			if (Colour < 0.0f) Colour = 0.0f; if (Colour > 1.0f) Colour = 1.0f;
			JoinTextures[DestIndex++] = (GLubyte)(Colour * 255.0f);
			Colour = ((float)PanoDataTop[SrcIndex++] / 255.0f - 0.5f) * Contr + Brigh + 0.5f;
			if (Colour < 0.0f) Colour = 0.0f; if (Colour > 1.0f) Colour = 1.0f;
			JoinTextures[DestIndex++] = (GLubyte)(Colour * 255.0f);
			Colour = ((float)PanoDataTop[SrcIndex] / 255.0f - 0.5f) * Contr + Brigh + 0.5f;
			if (Colour < 0.0f) Colour = 0.0f; if (Colour > 1.0f) Colour = 1.0f;
			JoinTextures[DestIndex] = (GLubyte)(Colour * 255.0f);
		}
	}
	// Transparent section
	for (Y = 0; Y < PanelTopTransHeightL; Y++) {
		Alpha = (float)Y / (float)PanelTopTransHeightL;
		OneMinusAlpha = 1.0f - Alpha;
		for (X = 0; X < TotalWidthL; X++) {
			Num = (float)(X - PanelTopXL);
			Den = (float)PanelTopWidthL;
			Num /= Den;
			Num += 1.0f; // Will usually be countered by modulo below
			Num *= (float)BMIH1.biWidth;
			SrcIndex = 3 * (((long)Num) % BMIH1.biWidth + (Y * BMIH1.biWidth));
			DestIndex = 3 * ((Y - PanelTopTransHeightL + PanelBottomOpaqueHeightL + PanelMiddleHeightL) * TotalWidthL + X);
			Colour = ((float)PanoDataTop[SrcIndex++] / 255.0f - 0.5f) * Contr + Brigh + 0.5f;
			if (Colour < 0.0f) Colour = 0.0f; if (Colour > 1.0f) Colour = 1.0f;
			JoinTextures[DestIndex] = (GLubyte)(Colour * 255.0f * Alpha + OneMinusAlpha * (float)JoinTextures[DestIndex]);
			DestIndex++;
			Colour = ((float)PanoDataTop[SrcIndex++] / 255.0f - 0.5f) * Contr + Brigh + 0.5f;
			if (Colour < 0.0f) Colour = 0.0f; if (Colour > 1.0f) Colour = 1.0f;
			JoinTextures[DestIndex] = (GLubyte)(Colour * 255.0f * Alpha + OneMinusAlpha * (float)JoinTextures[DestIndex]);
			DestIndex++;
			Colour = ((float)PanoDataTop[SrcIndex] / 255.0f - 0.5f) * Contr + Brigh + 0.5f;
			if (Colour < 0.0f) Colour = 0.0f; if (Colour > 1.0f) Colour = 1.0f;
			JoinTextures[DestIndex] = (GLubyte)(Colour * 255.0f * Alpha + OneMinusAlpha * (float)JoinTextures[DestIndex]);
		}
	}

	// Copy bottom panel
	Brigh = 2.0f * ((float)PanelBottomBrightness - 0.5f);
	Contr = (float)PanelBottomContrast * 2.0f;
	// Opaque section
	for (Y = 0; Y < PanelBottomOpaqueHeightL; Y++) {
		for (X = 0; X < TotalWidthL; X++) {
			Num = (float)(X - PanelBottomXL);
			Den = (float)PanelBottomWidthL;
			Num /= Den;
			Num += 1.0f; // Will usually be countered by modulo below
			Num *= (float)BMIH3.biWidth;
			SrcIndex = 3 * (((long)Num) % BMIH3.biWidth + (Y * BMIH3.biWidth));
			DestIndex = 3 * (Y * TotalWidthL + X);
			Colour = ((float)PanoDataBottom[SrcIndex++] / 255.0f - 0.5f) * Contr + Brigh + 0.5f;
			if (Colour < 0.0f) Colour = 0.0f; if (Colour > 1.0f) Colour = 1.0f;
			JoinTextures[DestIndex++] = (GLubyte)(Colour * 255.0f);
			Colour = ((float)PanoDataBottom[SrcIndex++] / 255.0f - 0.5f) * Contr + Brigh + 0.5f;
			if (Colour < 0.0f) Colour = 0.0f; if (Colour > 1.0f) Colour = 1.0f;
			JoinTextures[DestIndex++] = (GLubyte)(Colour * 255.0f);
			Colour = ((float)PanoDataBottom[SrcIndex] / 255.0f - 0.5f) * Contr + Brigh + 0.5f;
			if (Colour < 0.0f) Colour = 0.0f; if (Colour > 1.0f) Colour = 1.0f;
			JoinTextures[DestIndex] = (GLubyte)(Colour * 255.0f);
		}
	}
	// Transparent section
	for (Y = 0; Y < PanelBottomTransHeightL; Y++) {
		OneMinusAlpha = (float)Y / (float)PanelBottomTransHeightL;
		Alpha = 1.0f - OneMinusAlpha;
		for (X = 0; X < TotalWidthL; X++) {
			Num = (float)(X - PanelBottomXL);
			Den = (float)PanelBottomWidthL;
			Num /= Den;
			Num += 1.0f; // Will usually be countered by modulo below
			Num *= (float)BMIH3.biWidth;
			SrcIndex = 3 * (((long)Num) % BMIH3.biWidth + ((Y + PanelBottomOpaqueHeightL) * BMIH3.biWidth));
			DestIndex = 3 * ((Y + PanelBottomOpaqueHeightL) * TotalWidthL + X);
			Colour = ((float)PanoDataBottom[SrcIndex++] / 255.0f - 0.5f) * Contr + Brigh + 0.5f;
			if (Colour < 0.0f) Colour = 0.0f; if (Colour > 1.0f) Colour = 1.0f;
			JoinTextures[DestIndex] = (GLubyte)(Colour * 255.0f * Alpha + OneMinusAlpha * (float)JoinTextures[DestIndex]);
			DestIndex++;
			Colour = ((float)PanoDataBottom[SrcIndex++] / 255.0f - 0.5f) * Contr + Brigh + 0.5f;
			if (Colour < 0.0f) Colour = 0.0f; if (Colour > 1.0f) Colour = 1.0f;
			JoinTextures[DestIndex] = (GLubyte)(Colour * 255.0f * Alpha + OneMinusAlpha * (float)JoinTextures[DestIndex]);
			DestIndex++;
			Colour = ((float)PanoDataBottom[SrcIndex] / 255.0f - 0.5f) * Contr + Brigh + 0.5f;
			if (Colour < 0.0f) Colour = 0.0f; if (Colour > 1.0f) Colour = 1.0f;
			JoinTextures[DestIndex] = (GLubyte)(Colour * 255.0f * Alpha + OneMinusAlpha * (float)JoinTextures[DestIndex]);
		}
	}

	// Clear memory for final texture to all black
	long Max = 3 * 512 * 256;
	for (X = 0; X < Max; X++)
		FinalData[X] = 0;

	// Project the temporary texture onto the final skybox texture
	double UseHeightD = (double)PanelMiddleWidthL / (2 * M_PI) * M_SQRT2;
	double TotalHeightD = (double)TotalHeightL;
	long UseSubWidthL = PanelMiddleWidthL / 4;
	double UseSubWidthD = (double)UseSubWidthL;
	double ScaleRoof;
	long TexWidthRL = (long)BMIH4.biWidth;
	long TexWidthGL = (long)BMIH5.biWidth;
	double TexWidthRD = (double)TexWidthRL;
	double TexHeightRD = (double)BMIH4.biHeight;
	double TexWidthGD = (double)TexWidthGL;
	double TexHeightGD = (double)BMIH5.biHeight;

	double A = 1.0, R = 0.0, G = 0.0, B = 0.0;
	double Z = 0.0, Radius;

	// Generate outer walls of the skybox
	for (Y = 0; Y < 128; Y++) {
		for (X = 0; X < 512; X++) {
			DestIndex = 3 * (Y * 512 + X);
			// Find projected height
			Xd = (double)(X % 128) / 128.0;
			Yd = (double)(Y - 64) / 128.0;
			Yd = Yd * M_SQRT2 * cos(M_PI_4 - Xd * M_PI_2);
			Z = UseHeightD * Yd + 0.5 * TotalHeightD;
			if (Z < RoofTexOverlap) {
				// Project onto floor
				A = 1.0;
				Xd = (double)(X % 128) / 128.0 - 0.5;
				Yd = (double)Y / 128.0 - 0.5;
				ScaleRoof = 1.0 * RoofHeight / sqrt(Xd*Xd + Yd*Yd + 0.25);
				if (X < 128) {
					Yd = -0.5 * TexHeightGD * ScaleRoof + TexHeightGD * 0.5;
					Xd = Xd * TexWidthGD * ScaleRoof + TexWidthGD * 0.5;
				}
				else if (X < 256) {
					Yd = Xd * TexHeightGD * ScaleRoof + TexHeightGD * 0.5;
					Xd = 0.5 * TexWidthGD * ScaleRoof + TexWidthGD * 0.5;
				}
				else if (X < 384) {
					Xd = -Xd * TexWidthGD * ScaleRoof + TexWidthGD * 0.5;
					Yd = 0.5 * TexHeightGD * ScaleRoof + TexHeightGD * 0.5;
				}
				else {
					Yd = -Xd * TexHeightGD * ScaleRoof + TexHeightGD * 0.5;
					Xd = -0.5 * TexWidthGD * ScaleRoof + TexWidthGD * 0.5;
				}
				if (Xd < 0.0) A = 0.0;
				if (Yd < 0.0) A = 0.0;
				if (Xd > TexWidthGD - 1.0) A = 0.0;
				if (Yd > TexHeightGD - 1.0) A = 0.0;
				if (A > 0.0) {
					if (Z >= 0)
						A = 1.0 - Z / RoofTexOverlap;
					SrcIndex = 3 * ((long)Yd * TexWidthGL + (long)Xd);
					B = (double)TexDataGround[SrcIndex++];
					G = (double)TexDataGround[SrcIndex++];
					R = (double)TexDataGround[SrcIndex];
				}
				Xd = (double)(X % 128) / 128.0;
			}
			else if (Z > TotalHeightD - RoofTexOverlap) {
				// Project onto roof
				A = 1.0;
				Xd = (double)(X % 128) / 128.0 - 0.5;
				Yd = (double)Y / 128.0 - 0.5;
				ScaleRoof = 1.0 * RoofHeight / sqrt(Xd*Xd + Yd*Yd + 0.25);
				if (X < 128) {
					Yd = -0.5 * TexHeightRD * ScaleRoof + TexHeightRD * 0.5;
					Xd = Xd * TexWidthRD * ScaleRoof + TexWidthRD * 0.5;
				}
				else if (X < 256) {
					Yd = Xd * TexHeightRD * ScaleRoof + TexHeightRD * 0.5;
					Xd = 0.5 * TexWidthRD * ScaleRoof + TexWidthRD * 0.5;
				}
				else if (X < 384) {
					Xd = -Xd * TexWidthRD * ScaleRoof + TexWidthRD * 0.5;
					Yd = 0.5 * TexHeightRD * ScaleRoof + TexHeightRD * 0.5;
				}
				else {
					Yd = -Xd * TexHeightRD * ScaleRoof + TexHeightRD * 0.5;
					Xd = -0.5 * TexWidthRD * ScaleRoof + TexWidthRD * 0.5;
				}
				if (Xd < 0.0) A = 0.0;
				if (Yd < 0.0) A = 0.0;
				if (Xd > TexWidthRD - 1.0) A = 0.0;
				if (Yd > TexHeightRD - 1.0) A = 0.0;
				if (A > 0.0) {
					if (Z < TotalHeightD)
						A = 1.0 - (TotalHeightD - Z) / RoofTexOverlap;
					SrcIndex = 3 * ((long)Yd * TexWidthRL + (long)Xd);
					B = (double)TexDataRoof[SrcIndex++];
					G = (double)TexDataRoof[SrcIndex++];
					R = (double)TexDataRoof[SrcIndex];
				}
				Xd = (double)(X % 128) / 128.0;
			}
			else
				A = 0.0;
			if ((Z < 0) || (Z > TotalHeightD)) {
				FinalData[DestIndex++] = (unsigned char)B;
				FinalData[DestIndex++] = (unsigned char)G;
				FinalData[DestIndex] = (unsigned char)R;
				continue;
			}
			Xd = UseSubWidthD * 0.5 * (1.0 - tan(M_PI_4 - Xd * M_PI_2));
			Yd = Z;
			if (Xd < 0) continue;
			if (Xd >= PanelMiddleWidthL) continue;
			SrcIndex = 3 * ((long)Yd * TotalWidthL + (long)Xd + UseSubWidthL * (X / 128));
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * B);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * G);
			FinalData[DestIndex] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex] + A * R);
		}
	}
	
	// Generate roof tile of the skybox
	long Offset = 0;
	for (Y = 0; Y < 64; Y++) {
		for (X = Y; X < 128 - Y; X++) {
			DestIndex = 3 * ((Y + 128) * 512 + X);
			Xd = (double)X / 128.0 - 0.5;
			Yd = (double)Y / 128.0 - 0.5;
			Radius = sqrt(Yd * Yd + Xd * Xd);
			Z = UseHeightD * M_SQRT2 / (4.0 * Radius);
			if (Z >= (TotalHeightD / 2.0 - RoofTexOverlap)) {
				// Doesn't project onto cylinder, or overlaps. Use roof texture.
				ScaleRoof = 1.0 * RoofHeight / sqrt(Xd*Xd + Yd*Yd + 0.25);
				Xd = Xd * TexWidthRD * ScaleRoof + TexWidthRD * 0.5;
				Yd = Yd * TexHeightRD * ScaleRoof + TexHeightRD * 0.5;
				if (Xd < 0.0) continue;
				if (Yd < 0.0) continue;
				if (Xd > TexWidthRD - 1.0) continue;
				if (Yd > TexHeightRD - 1.0) continue;
				SrcIndex = 3 * ((long)Yd * TexWidthRL + (long)Xd);
				if (Z >= (TotalHeightD / 2.0)) {
					FinalData[DestIndex++] = TexDataRoof[SrcIndex++];
					FinalData[DestIndex++] = TexDataRoof[SrcIndex++];
					FinalData[DestIndex] = TexDataRoof[SrcIndex];
					continue;
				}
				B = TexDataRoof[SrcIndex++];
				G = TexDataRoof[SrcIndex++];
				R = TexDataRoof[SrcIndex];
				A = 1.0 - (TotalHeightD / 2.0 - Z) / RoofTexOverlap;
				Xd = (double)X / 128.0 - 0.5;
			}
			else
				A = 0.0;
			// Projects onto the cylinder, not beyond it
			Yd = Z + TotalHeightD / 2.0;
			Xd = Xd / (M_SQRT2 * Radius);
			Xd = UseSubWidthD * (asin(M_SQRT2 * Xd) + M_PI_4) / M_PI_2;
			SrcIndex = 3 * ((long)Yd * TotalWidthL + (long)Xd + Offset);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * B);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * G);
			FinalData[DestIndex] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex] + A * R);
		}
	}
	Offset = UseSubWidthL;
	for (Y = 0; Y < 64; Y++) {
		for (X = Y; X < 128 - Y; X++) {
			DestIndex = 3 * ((X + 128) * 512 + (127 - Y));
			Xd = (double)X / 128.0 - 0.5;
			Yd = (double)Y / 128.0 - 0.5;
			Radius = sqrt(Yd * Yd + Xd * Xd);
			Z = UseHeightD * M_SQRT2 / (4.0 * Radius);
			if (Z >= (TotalHeightD / 2.0 - RoofTexOverlap)) {
				// Doesn't project onto cylinder. Use roof texture.
				ScaleRoof = 1.0 * RoofHeight / sqrt(Xd*Xd + Yd*Yd + 0.25);
				Xd = Xd * TexHeightRD * ScaleRoof + TexHeightRD * 0.5;
				Yd = Yd * TexWidthRD * ScaleRoof + TexWidthRD * 0.5;
				if (Xd < 0.0) continue;
				if (Yd < 0.0) continue;
				if (Xd > TexHeightRD - 1.0) continue;
				if (Yd > TexWidthRD - 1.0) continue;
				SrcIndex = 3 * ((long)Xd * TexWidthRL + (long)(TexWidthRD - Yd));
				if (Z >= (TotalHeightD / 2.0)) {
					FinalData[DestIndex++] = TexDataRoof[SrcIndex++];
					FinalData[DestIndex++] = TexDataRoof[SrcIndex++];
					FinalData[DestIndex] = TexDataRoof[SrcIndex];
					continue;
				}
				B = TexDataRoof[SrcIndex++];
				G = TexDataRoof[SrcIndex++];
				R = TexDataRoof[SrcIndex];
				A = 1.0 - (TotalHeightD / 2.0 - Z) / RoofTexOverlap;
				Xd = (double)X / 128.0 - 0.5;
			}
			else
				A = 0.0;
			// Projects onto the cylinder, not beyond it
			Yd = Z + TotalHeightD / 2.0;
			Xd = Xd / (M_SQRT2 * Radius);
			Xd = UseSubWidthD * (asin(M_SQRT2 * Xd) + M_PI_4) / M_PI_2;
			SrcIndex = 3 * ((long)Yd * TotalWidthL + (long)Xd + Offset);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * B);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * G);
			FinalData[DestIndex] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex] + A * R);
		}
	}
	Offset = 2 * UseSubWidthL;
	for (Y = 0; Y < 64; Y++) {
		for (X = Y; X < 128 - Y; X++) {
			DestIndex = 3 * ((255 - Y) * 512 + (127 - X));
			Xd = (double)X / 128.0 - 0.5;
			Yd = (double)Y / 128.0 - 0.5;
			Radius = sqrt(Yd * Yd + Xd * Xd);
			Z = UseHeightD * M_SQRT2 / (4.0 * Radius);
			if (Z >= (TotalHeightD / 2.0 - RoofTexOverlap)) {
				// Doesn't project onto cylinder. Use roof texture.
				ScaleRoof = 1.0 * RoofHeight / sqrt(Xd*Xd + Yd*Yd + 0.25);
				Xd = Xd * TexWidthRD * ScaleRoof + TexWidthRD * 0.5;
				Yd = Yd * TexHeightRD * ScaleRoof + TexHeightRD * 0.5;
				if (Xd < 0.0) continue;
				if (Yd < 0.0) continue;
				if (Xd > TexWidthRD - 1.0) continue;
				if (Yd > TexHeightRD - 1.0) continue;
				SrcIndex = 3 * ((long)(TexHeightRD - Yd) * TexWidthRL + (long)(TexWidthRD - Xd));
				if (Z >= (TotalHeightD / 2.0)) {
					FinalData[DestIndex++] = TexDataRoof[SrcIndex++];
					FinalData[DestIndex++] = TexDataRoof[SrcIndex++];
					FinalData[DestIndex] = TexDataRoof[SrcIndex];
					continue;
				}
				B = TexDataRoof[SrcIndex++];
				G = TexDataRoof[SrcIndex++];
				R = TexDataRoof[SrcIndex];
				A = 1.0 - (TotalHeightD / 2.0 - Z) / RoofTexOverlap;
				Xd = (double)X / 128.0 - 0.5;
			}
			else
				A = 0.0;
			// Projects onto the cylinder, not beyond it
			Yd = Z + TotalHeightD / 2.0;
			Xd = Xd / (M_SQRT2 * Radius);
			Xd = UseSubWidthD * (asin(M_SQRT2 * Xd) + M_PI_4) / M_PI_2;
			SrcIndex = 3 * ((long)Yd * TotalWidthL + (long)Xd + Offset);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * B);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * G);
			FinalData[DestIndex] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex] + A * R);
		}
	}
	Offset = 3 * UseSubWidthL;
	for (Y = 0; Y < 64; Y++) {
		for (X = Y; X < 128 - Y; X++) {
			DestIndex = 3 * ((255 - X) * 512 + Y);
			Xd = (double)X / 128.0 - 0.5;
			Yd = (double)Y / 128.0 - 0.5;
			Radius = sqrt(Yd * Yd + Xd * Xd);
			Z = UseHeightD * M_SQRT2 / (4.0 * Radius);
			if (Z >= (TotalHeightD / 2.0 - RoofTexOverlap)) {
				// Doesn't project onto cylinder. Use roof texture.
				ScaleRoof = 1.0 * RoofHeight / sqrt(Xd*Xd + Yd*Yd + 0.25);
				Xd = Xd * TexHeightRD * ScaleRoof + TexHeightRD * 0.5;
				Yd = Yd * TexWidthRD * ScaleRoof + TexWidthRD * 0.5;
				if (Xd < 0.0) continue;
				if (Yd < 0.0) continue;
				if (Xd > TexHeightRD - 1.0) continue;
				if (Yd > TexWidthRD - 1.0) continue;
				SrcIndex = 3 * ((long)(TexHeightRD - Xd) * TexWidthRL + (long)Yd);
				if (Z >= (TotalHeightD / 2.0)) {
					FinalData[DestIndex++] = TexDataRoof[SrcIndex++];
					FinalData[DestIndex++] = TexDataRoof[SrcIndex++];
					FinalData[DestIndex] = TexDataRoof[SrcIndex];
					continue;
				}
				B = TexDataRoof[SrcIndex++];
				G = TexDataRoof[SrcIndex++];
				R = TexDataRoof[SrcIndex];
				A = 1.0 - (TotalHeightD / 2.0 - Z) / RoofTexOverlap;
				Xd = (double)X / 128.0 - 0.5;
			}
			else
				A = 0.0;
			// Projects onto the cylinder, not beyond it
			Yd = Z + TotalHeightD / 2.0;
			Xd = Xd / (M_SQRT2 * Radius);
			Xd = UseSubWidthD * (asin(M_SQRT2 * Xd) + M_PI_4) / M_PI_2;
			SrcIndex = 3 * ((long)Yd * TotalWidthL + (long)Xd + Offset);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * B);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * G);
			FinalData[DestIndex] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex] + A * R);
		}
	}

	// Generate ground tile of the skybox
	Offset = 0;
	for (Y = 0; Y < 64; Y++) {
		for (X = Y; X < 128 - Y; X++) {
			DestIndex = 3 * ((Y + 128) * 512 + X + 128);
			Xd = (double)X / 128.0 - 0.5;
			Yd = (double)Y / 128.0 - 0.5;
			Radius = sqrt(Yd * Yd + Xd * Xd);
			Z = UseHeightD * M_SQRT2 / (4.0 * Radius);
			if (Z >= (TotalHeightD / 2.0 - RoofTexOverlap)) {
				// Doesn't project onto cylinder, or overlaps. Use ground texture.
				ScaleRoof = 1.0 * RoofHeight / sqrt(Xd*Xd + Yd*Yd + 0.25);
				Xd = Xd * TexWidthGD * ScaleRoof + TexWidthGD * 0.5;
				Yd = Yd * TexHeightGD * ScaleRoof + TexHeightGD * 0.5;
				if (Xd < 0.0) continue;
				if (Yd < 0.0) continue;
				if (Xd > TexWidthGD - 1.0) continue;
				if (Yd > TexHeightGD - 1.0) continue;
				SrcIndex = 3 * ((long)Yd * TexWidthGL + (long)Xd);
				if (Z >= (TotalHeightD / 2.0)) {
					FinalData[DestIndex++] = TexDataGround[SrcIndex++];
					FinalData[DestIndex++] = TexDataGround[SrcIndex++];
					FinalData[DestIndex] = TexDataGround[SrcIndex];
					continue;
				}
				B = TexDataGround[SrcIndex++];
				G = TexDataGround[SrcIndex++];
				R = TexDataGround[SrcIndex];
				A = 1.0 - (TotalHeightD / 2.0 - Z) / RoofTexOverlap;
				Xd = (double)X / 128.0 - 0.5;
			}
			else
				A = 0.0;
			// Projects onto the cylinder, not beyond it
			Yd = Z + TotalHeightD / 2.0;
			Xd = Xd / (M_SQRT2 * Radius);
			Xd = UseSubWidthD * (asin(M_SQRT2 * Xd) + M_PI_4) / M_PI_2;
			SrcIndex = 3 * ((TotalHeightL - (long)Yd - 1) * TotalWidthL + (long)Xd + Offset);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * B);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * G);
			FinalData[DestIndex] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex] + A * R);
		}
	}
	Offset = UseSubWidthL;
	for (Y = 0; Y < 64; Y++) {
		for (X = Y; X < 128 - Y; X++) {
			DestIndex = 3 * ((X + 128) * 512 + (127 - Y) + 128);
			Xd = (double)X / 128.0 - 0.5;
			Yd = (double)Y / 128.0 - 0.5;
			Radius = sqrt(Yd * Yd + Xd * Xd);
			Z = UseHeightD * M_SQRT2 / (4.0 * Radius);
			if (Z >= (TotalHeightD / 2.0 - RoofTexOverlap)) {
				// Doesn't project onto cylinder. Use ground texture.
				ScaleRoof = 1.0 * RoofHeight / sqrt(Xd*Xd + Yd*Yd + 0.25);
				Xd = Xd * TexHeightGD * ScaleRoof + TexHeightGD * 0.5;
				Yd = Yd * TexWidthGD * ScaleRoof + TexWidthGD * 0.5;
				if (Xd < 0.0) continue;
				if (Yd < 0.0) continue;
				if (Xd > TexHeightGD - 1.0) continue;
				if (Yd > TexWidthGD - 1.0) continue;
				SrcIndex = 3 * ((long)Xd * TexWidthGL + (long)(TexWidthGD - Yd));
				if (Z >= (TotalHeightD / 2.0)) {
					FinalData[DestIndex++] = TexDataGround[SrcIndex++];
					FinalData[DestIndex++] = TexDataGround[SrcIndex++];
					FinalData[DestIndex] = TexDataGround[SrcIndex];
					continue;
				}
				B = TexDataGround[SrcIndex++];
				G = TexDataGround[SrcIndex++];
				R = TexDataGround[SrcIndex];
				A = 1.0 - (TotalHeightD / 2.0 - Z) / RoofTexOverlap;
				Xd = (double)X / 128.0 - 0.5;
			}
			else
				A = 0.0;
			// Projects onto the cylinder, not beyond it
			Yd = Z + TotalHeightD / 2.0;
			Xd = Xd / (M_SQRT2 * Radius);
			Xd = UseSubWidthD * (asin(M_SQRT2 * Xd) + M_PI_4) / M_PI_2;
			SrcIndex = 3 * ((TotalHeightL - (long)Yd - 1) * TotalWidthL + (long)Xd + Offset);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * B);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * G);
			FinalData[DestIndex] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex] + A * R);
		}
	}
	Offset = 2 * UseSubWidthL;
	for (Y = 0; Y < 64; Y++) {
		for (X = Y; X < 128 - Y; X++) {
			DestIndex = 3 * ((255 - Y) * 512 + (127 - X) + 128);
			Xd = (double)X / 128.0 - 0.5;
			Yd = (double)Y / 128.0 - 0.5;
			Radius = sqrt(Yd * Yd + Xd * Xd);
			Z = UseHeightD * M_SQRT2 / (4.0 * Radius);
			if (Z >= (TotalHeightD / 2.0 - RoofTexOverlap)) {
				// Doesn't project onto cylinder. Use ground texture.
				ScaleRoof = 1.0 * RoofHeight / sqrt(Xd*Xd + Yd*Yd + 0.25);
				Xd = Xd * TexWidthGD * ScaleRoof + TexWidthGD * 0.5;
				Yd = Yd * TexHeightGD * ScaleRoof + TexHeightGD * 0.5;
				if (Xd < 0.0) continue;
				if (Yd < 0.0) continue;
				if (Xd > TexWidthGD - 1.0) continue;
				if (Yd > TexHeightGD - 1.0) continue;
				SrcIndex = 3 * ((long)(TexHeightGD - Yd) * TexWidthGL + (long)(TexWidthGD - Xd));
				if (Z >= (TotalHeightD / 2.0)) {
					FinalData[DestIndex++] = TexDataGround[SrcIndex++];
					FinalData[DestIndex++] = TexDataGround[SrcIndex++];
					FinalData[DestIndex] = TexDataGround[SrcIndex];
					continue;
				}
				B = TexDataGround[SrcIndex++];
				G = TexDataGround[SrcIndex++];
				R = TexDataGround[SrcIndex];
				A = 1.0 - (TotalHeightD / 2.0 - Z) / RoofTexOverlap;
				Xd = (double)X / 128.0 - 0.5;
			}
			else
				A = 0.0;
			// Projects onto the cylinder, not beyond it
			Yd = Z + TotalHeightD / 2.0;
			Xd = Xd / (M_SQRT2 * Radius);
			Xd = UseSubWidthD * (asin(M_SQRT2 * Xd) + M_PI_4) / M_PI_2;
			SrcIndex = 3 * ((TotalHeightL - (long)Yd - 1) * TotalWidthL + (long)Xd + Offset);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * B);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * G);
			FinalData[DestIndex] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex] + A * R);
		}
	}
	Offset = 3 * UseSubWidthL;
	for (Y = 0; Y < 64; Y++) {
		for (X = Y; X < 128 - Y; X++) {
			DestIndex = 3 * ((255 - X) * 512 + Y + 128);
			Xd = (double)X / 128.0 - 0.5;
			Yd = (double)Y / 128.0 - 0.5;
			Radius = sqrt(Yd * Yd + Xd * Xd);
			Z = UseHeightD * M_SQRT2 / (4.0 * Radius);
			if (Z >= (TotalHeightD / 2.0 - RoofTexOverlap)) {
				// Doesn't project onto cylinder. Use ground texture.
				ScaleRoof = 1.0 * RoofHeight / sqrt(Xd*Xd + Yd*Yd + 0.25);
				Xd = Xd * TexHeightGD * ScaleRoof + TexHeightGD * 0.5;
				Yd = Yd * TexWidthGD * ScaleRoof + TexWidthGD * 0.5;
				if (Xd < 0.0) continue;
				if (Yd < 0.0) continue;
				if (Xd > TexHeightGD - 1.0) continue;
				if (Yd > TexWidthGD - 1.0) continue;
				SrcIndex = 3 * ((long)(TexHeightGD - Xd) * TexWidthGL + (long)Yd);
				if (Z >= (TotalHeightD / 2.0)) {
					FinalData[DestIndex++] = TexDataGround[SrcIndex++];
					FinalData[DestIndex++] = TexDataGround[SrcIndex++];
					FinalData[DestIndex] = TexDataGround[SrcIndex];
					continue;
				}
				B = TexDataGround[SrcIndex++];
				G = TexDataGround[SrcIndex++];
				R = TexDataGround[SrcIndex];
				A = 1.0 - (TotalHeightD / 2.0 - Z) / RoofTexOverlap;
				Xd = (double)X / 128.0 - 0.5;
			}
			else
				A = 0.0;
			// Projects onto the cylinder, not beyond it
			Yd = Z + TotalHeightD / 2.0;
			Xd = Xd / (M_SQRT2 * Radius);
			Xd = UseSubWidthD * (asin(M_SQRT2 * Xd) + M_PI_4) / M_PI_2;
			SrcIndex = 3 * ((TotalHeightL- (long)Yd - 1) * TotalWidthL + (long)Xd + Offset);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * B);
			FinalData[DestIndex++] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex++] + A * G);
			FinalData[DestIndex] = (GLubyte)((1.0 - A) * (double)JoinTextures[SrcIndex] + A * R);
		}
	}
/*
	// Generate roof tile of the skybox WITH SUPERFICIAL METHODS
	TotalHeightL = BMIH5.biHeight;
	TotalWidthL = BMIH5.biWidth;
	for (Y = 0; Y < 128; Y++) {
		for (X = 0; X < 128; X++) {
			Num = ((float)Y / 128.0f) * (float)TotalHeightL;
			Den = ((float)X / 128.0f) * (float)TotalWidthL;
			SrcIndex = 3 * ((long)Num * TotalWidthL + (long)Den);
			DestIndex = 3 * (Y * 512 + X + 65664);
			FinalData[DestIndex++] = TexDataGround[SrcIndex++];
			FinalData[DestIndex++] = TexDataGround[SrcIndex++];
			FinalData[DestIndex] = TexDataGround[SrcIndex];
		}
	}
*/
	glBindTexture(GL_TEXTURE_2D, PanoTextureFinal);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(
		GL_TEXTURE_2D, 0, 3, 512, 256, 0,
		GL_BGR, GL_UNSIGNED_BYTE, FinalData
		);
		
	
}
