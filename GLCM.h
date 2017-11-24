#ifndef _GLCM_H_
#define _GLCM_H_

#include "Data.h"
			
void ConvertIplImageToBuffer(IplImage *image, unsigned char *bufferImage)
{
	int imageWidth = image->width;
	int imageHeight = image->height;

	register int i, j;

	int index = 0;

	for(i=0; i<imageHeight; i++)
	{
		index = i*imageWidth;

		for(j=0; j<imageWidth; j++)
		{
			bufferImage[index+j] = (unsigned char)(image->imageData[i*image->widthStep+j]);
		}
	}

}

void MakeQuantizedImage(const unsigned char *inImage)
{
	memset(QUANTIZATION_IMAGE, 0, sizeof(QUANTIZATION_IMAGE));

	register int i, j;

	int index = 0;

	for(i=0; i<IMAGE_HEIGHT; i++)
	{
		index = i*IMAGE_WIDTH;

		for(j=0; j<IMAGE_WIDTH; j++)
		{

#if USE_QUANTIZATION_LEVEL8
			QUANTIZATION_IMAGE[index+j] = QUANTIZATION_LEVEL8_LUT[inImage[index+j]];
#endif

#if USE_QUANTIZATION_LEVEL16
			QUANTIZATION_IMAGE[index+j] = QUANTIZATION_LEVEL16_LUT[inImage[index+j]];
#endif

#if USE_QUANTIZATION_LEVEL32
			QUANTIZATION_IMAGE[index+j] = QUANTIZATION_LEVEL32_LUT[inImage[index+j]];
#endif

#if USE_QUANTIZATION_LEVEL64
			QUANTIZATION_IMAGE[index+j] = QUANTIZATION_LEVEL64_LUT[inImage[index+j]];
#endif

#if NO_USE_QUANTIZATION_LEVEL
			QUANTIZATION_IMAGE[index+j] = inImage[index+j];
#endif
		}
	}

}

const int MakeToneLUT()
{
	memset(TONE_LUT, -1, sizeof(TONE_LUT));

	int i, j;

	for(i=IMAGE_HEIGHT-1; i >= 0; --i)
	{
		for(j=0; j<IMAGE_WIDTH; ++j)
		{
			TONE_LUT[QUANTIZATION_IMAGE[i*IMAGE_WIDTH+j]] = QUANTIZATION_IMAGE[i*IMAGE_WIDTH+j];
		}
	}

	int iTone = 0;
	for(i=0, iTone=0; i <= MAX_GRAY_LEVEL_VAL; i++)
	{
		if (TONE_LUT[i] != -1)
		{
			TONE_LUT[i] = iTone++;
		}

	}

	const int toneCount = iTone;

	return toneCount;
}


const int PreProcessingForGLCM(const unsigned char *image)
{
	MakeQuantizedImage(image);
	const int toneCount = MakeToneLUT();

	return toneCount;
}


void GetGLCM(const int toneCount)
{
	memset(MATRIX_ANGLE_0,   0, sizeof(MATRIX_ANGLE_0));
	memset(MATRIX_ANGLE_45,	 0, sizeof(MATRIX_ANGLE_45));
	memset(MATRIX_ANGLE_90,	 0, sizeof(MATRIX_ANGLE_90));
	memset(MATRIX_ANGLE_135, 0, sizeof(MATRIX_ANGLE_135));

	register int i, j;
	int x0, y0, x45, y45, x90, y90, x135, y135;
	int count0 = 0, count45 = 0, count90 = 0, count135 = 0;

	for(i=0; i<IMAGE_HEIGHT; ++i)
	{
		for(j=0; j<IMAGE_WIDTH; ++j) 
		{
			//For angle 0
			if(j+DISTANCE < IMAGE_WIDTH) 
			{		
				x0 = TONE_LUT[QUANTIZATION_IMAGE[i*IMAGE_WIDTH+j]];
				y0 = TONE_LUT[QUANTIZATION_IMAGE[i*IMAGE_WIDTH+(j+DISTANCE)]];
				MATRIX_ANGLE_0[x0][y0]++;
				MATRIX_ANGLE_0[y0][x0]++;
				count0 += 2;
			}

			//For angle 45
			if(i+DISTANCE < IMAGE_HEIGHT && j+DISTANCE < IMAGE_WIDTH) 
			{			
				x45 = TONE_LUT[QUANTIZATION_IMAGE[i*IMAGE_WIDTH+j]];
				y45 = TONE_LUT[QUANTIZATION_IMAGE[(i+DISTANCE)*IMAGE_WIDTH+(j+DISTANCE)]];
				MATRIX_ANGLE_45[x45][y45]++;
				MATRIX_ANGLE_45[y45][x45]++;
				count45 += 2;
			}

			//For angle 90
			if(i+DISTANCE < IMAGE_HEIGHT) 
			{			
				x90 = TONE_LUT[QUANTIZATION_IMAGE[i*IMAGE_WIDTH+j]];
				y90 = TONE_LUT[QUANTIZATION_IMAGE[(i+DISTANCE)*IMAGE_WIDTH+j]];
				MATRIX_ANGLE_90[x90][y90]++;
				MATRIX_ANGLE_90[y90][x90]++;
				count90 += 2;
			}

			//For angle 135
			if(i+DISTANCE < IMAGE_HEIGHT && j-DISTANCE >= 0) 
			{		
				x135 = TONE_LUT[QUANTIZATION_IMAGE[i*IMAGE_WIDTH+j]];
				y135 = TONE_LUT[QUANTIZATION_IMAGE[(i+DISTANCE)*IMAGE_WIDTH+(j-DISTANCE)]];
				MATRIX_ANGLE_135[x135][y135]++;
				MATRIX_ANGLE_135[y135][x135]++;
				count135 += 2;
			}

		}
	}

	//Normalize matrix
	for(i=0; i<toneCount; ++i)
	{
		for(j=0; j<toneCount; ++j)
		{
			//For angle 0
			if (count0 == 0)
			{
				MATRIX_ANGLE_0[i][j] = 0;
			}

			else
			{
				MATRIX_ANGLE_0[i][j] /= count0;
			}

			//For angle 45
			if (count45 == 0)
			{
				MATRIX_ANGLE_45[i][j] = 0;
			}

			else
			{
				MATRIX_ANGLE_45[i][j] /= count45;
			}

			//For angle 90
			if (count90 == 0)
			{
				MATRIX_ANGLE_90[i][j] = 0;
			}

			else
			{
				MATRIX_ANGLE_90[i][j] /= count90;
			}

			//For angle 135
			if (count135 == 0)
			{
				MATRIX_ANGLE_135[i][j] = 0;
			}

			else
			{
				MATRIX_ANGLE_135[i][j] /= count135;
			}

		}

	}

}

void GetGLCMFeature(const int toneCount)
{
	memset(FEATURE1_ENERGY,								0,		sizeof(FEATURE1_ENERGY));
	memset(FEATURE2_CONTRAST,							0,		sizeof(FEATURE2_CONTRAST));
	memset(FEATURE3_CORRELATION,						0,		sizeof(FEATURE3_CORRELATION));
	memset(FEATURE4_VARIANCE,							0,		sizeof(FEATURE4_VARIANCE));
	memset(FEATURE5_LOCAL_STABILITY,					0,		sizeof(FEATURE5_LOCAL_STABILITY));
	memset(FEATURE6_SUM_AVERAGE,						0,		sizeof(FEATURE6_SUM_AVERAGE));
	memset(FEATURE7_SUM_VARIANCE,						0,		sizeof(FEATURE7_SUM_VARIANCE));
	memset(FEATURE8_SUM_ENTROPY,						0,		sizeof(FEATURE8_SUM_ENTROPY));
	memset(FEATURE9_ENTROPY,							0,		sizeof(FEATURE9_ENTROPY));
	memset(FEATURE10_DIFFERENCE_VARIANCE,				0,		sizeof(FEATURE10_DIFFERENCE_VARIANCE));
	memset(FEATURE11_DIFFERENCE_ENTROPY,				0,		sizeof(FEATURE11_DIFFERENCE_ENTROPY));
	memset(FEATURE12_INFOMATION_MEASURE_CORRELATION1,	0,		sizeof(FEATURE12_INFOMATION_MEASURE_CORRELATION1));
	memset(FEATURE13_INFOMATION_MEASURE_CORRELATION2,	0,		sizeof(FEATURE13_INFOMATION_MEASURE_CORRELATION2));

	register int i, j, n;

	float sumEnergy0 = 0;
	float sumEnergy45 = 0;
	float sumEnergy90 = 0;
	float sumEnergy135 = 0;

	float entropy0 = 0;
	float entropy45 = 0;
	float entropy90 = 0;
	float entropy135 = 0;

	float localStability0 = 0;
	float localStability45 = 0;
	float localStability90 = 0;
	float localStability135 = 0;

	float correlation0 = 0;
	float correlation45 = 0;
	float correlation90 = 0;
	float correlation135 = 0;

	float pCOR0[MAX_TONE_LEVEL] = {0, }; //probability correlation 
	float pCOR45[MAX_TONE_LEVEL] = {0, };
	float pCOR90[MAX_TONE_LEVEL] = {0, };
	float pCOR135[MAX_TONE_LEVEL] = {0, };

	float pSA0[MAX_TONE_LEVEL_DOUBLE] = {0, }; //probability sum average  
	float pSA45[MAX_TONE_LEVEL_DOUBLE] = {0, };
	float pSA90[MAX_TONE_LEVEL_DOUBLE] = {0, };
	float pSA135[MAX_TONE_LEVEL_DOUBLE] = {0, };

	float pSE0[MAX_TONE_LEVEL_DOUBLE] = {0, }; //probability sum entropy  
	float pSE45[MAX_TONE_LEVEL_DOUBLE] = {0, };
	float pSE90[MAX_TONE_LEVEL_DOUBLE] = {0, };
	float pSE135[MAX_TONE_LEVEL_DOUBLE] = {0, };

	float pDV0[MAX_TONE_LEVEL_DOUBLE] = {0, }; //probability difference variance
	float pDV45[MAX_TONE_LEVEL_DOUBLE] = {0, };
	float pDV90[MAX_TONE_LEVEL_DOUBLE] = {0, };
	float pDV135[MAX_TONE_LEVEL_DOUBLE] = {0, };

	float pICy0[MAX_TONE_LEVEL] = {0, }; //probability information y correlation
	float pICy45[MAX_TONE_LEVEL] = {0, };
	float pICy90[MAX_TONE_LEVEL] = {0, };
	float pICy135[MAX_TONE_LEVEL] = {0, };

	float denominatorLog = log10(2.0f);

	for(i=0; i<toneCount; ++i)
	{
		for(j=0; j<toneCount; ++j)
		{
			//1. Energy(0, 45, 90, 135)
			sumEnergy0   += MATRIX_ANGLE_0[i][j]   * MATRIX_ANGLE_0[i][j];
			sumEnergy45  += MATRIX_ANGLE_45[i][j]  * MATRIX_ANGLE_45[i][j];
			sumEnergy90  += MATRIX_ANGLE_90[i][j]  * MATRIX_ANGLE_90[i][j];
			sumEnergy135 += MATRIX_ANGLE_135[i][j] * MATRIX_ANGLE_135[i][j];

			pCOR0[i]   += MATRIX_ANGLE_0[i][j];
			pCOR45[i]  += MATRIX_ANGLE_45[i][j];
			pCOR90[i]  += MATRIX_ANGLE_90[i][j];
			pCOR135[i] += MATRIX_ANGLE_135[i][j];

			pICy0[j]   += MATRIX_ANGLE_0[i][j];
			pICy45[j]  += MATRIX_ANGLE_45[i][j];
			pICy90[j]  += MATRIX_ANGLE_90[i][j];
			pICy135[j] += MATRIX_ANGLE_135[i][j];

			//5. Stability(0, 45, 90, 135)
			float denominatorLS = (float)((1+(i-j)*(i-j)));
			localStability0   += MATRIX_ANGLE_0[i][j]   / denominatorLS;
			localStability45  += MATRIX_ANGLE_45[i][j]  / denominatorLS;
			localStability90  += MATRIX_ANGLE_90[i][j]  / denominatorLS;
			localStability135 += MATRIX_ANGLE_135[i][j] / denominatorLS;
		
			pSA0[i+j]   += MATRIX_ANGLE_0[i][j];
			pSA45[i+j]  += MATRIX_ANGLE_45[i][j];
			pSA90[i+j]  += MATRIX_ANGLE_90[i][j];
			pSA135[i+j] += MATRIX_ANGLE_135[i][j];

			pSE0[i+j+2]   += MATRIX_ANGLE_0[i][j];
			pSE45[i+j+2]  += MATRIX_ANGLE_45[i][j];
			pSE90[i+j+2]  += MATRIX_ANGLE_90[i][j];
			pSE135[i+j+2] += MATRIX_ANGLE_135[i][j];

			//9. Entropy(0, 45, 90, 135)
			entropy0   += MATRIX_ANGLE_0[i][j]    * log10(MATRIX_ANGLE_0[i][j]   + GLCM_EPSILON)/denominatorLog;
			entropy45  += MATRIX_ANGLE_45[i][j]   * log10(MATRIX_ANGLE_45[i][j]  + GLCM_EPSILON)/denominatorLog;
			entropy90  += MATRIX_ANGLE_90[i][j]   * log10(MATRIX_ANGLE_90[i][j]  + GLCM_EPSILON)/denominatorLog;
			entropy135 += MATRIX_ANGLE_135[i][j]  * log10(MATRIX_ANGLE_135[i][j] + GLCM_EPSILON)/denominatorLog;

			int difference = abs(i-j);
			pDV0[difference]   += MATRIX_ANGLE_0[i][j];
			pDV45[difference]  += MATRIX_ANGLE_45[i][j];
			pDV90[difference]  += MATRIX_ANGLE_90[i][j];
			pDV135[difference] += MATRIX_ANGLE_135[i][j];

		}
	}

	float sumContrast0 = 0;
	float sumContrast45 = 0;
	float sumContrast90 = 0;
	float sumContrast135 = 0;

	float bigSumContrast0 = 0;
	float bigSumContrast45 = 0;
	float bigSumContrast90 = 0;
	float bigSumContrast135 = 0;

	float meanX0 = 0,   meanY0 = 0;
	float meanX45 = 0,  meanY45 = 0;
	float meanX90 = 0,  meanY90 = 0;
	float meanX135 = 0, meanY135 = 0;

	float sumSqrtX0 = 0;
	float sumSqrtX45 = 0;
	float sumSqrtX90 = 0;
	float sumSqrtX135 = 0;

	float stdDevX0 = 0,   stdDevY0 = 0;
	float stdDevX45 = 0,  stdDevY45 = 0;
	float stdDevX90 = 0,  stdDevY90 = 0;
	float stdDevX135 = 0, stdDevY135 = 0;

	float variance0 = 0;
	float variance45 = 0;
	float variance90 = 0;
	float variance135 = 0;

	for(n=0; n<toneCount; ++n) 
	{
		for(i= 0; i<toneCount; ++i)
		{
			for(j=0; j<toneCount; ++j) 
			{
				if((i - j) == n || (j - i) == n)
				{
					sumContrast0    += MATRIX_ANGLE_0[i][j];
					sumContrast45   += MATRIX_ANGLE_45[i][j];
					sumContrast90   += MATRIX_ANGLE_90[i][j];
					sumContrast135  += MATRIX_ANGLE_135[i][j];
				}
			}
		}

		//2. Contrast(0, 45, 90, 135)
		int nSquare = n*n;

		bigSumContrast0 += nSquare*sumContrast0;
		sumContrast0 = 0;

		bigSumContrast45 += nSquare*sumContrast45;
		sumContrast45 = 0;

		bigSumContrast90 += nSquare*sumContrast90;
		sumContrast90 = 0;

		bigSumContrast135 += nSquare*sumContrast135;
		sumContrast135 = 0;

	}

	float sum0 = 0;
	float sum45 = 0;
	float sum90 = 0;
	float sum135 = 0;

	float sumSquare0 = 0;
	float sumSquare45 = 0;
	float sumSquare90 = 0;
	float sumSquare135 = 0;

	float differenceVariance0 = 0;
	float differenceVariance45 = 0;
	float differenceVariance90 = 0;
	float differenceVariance135 = 0;

	float sumMinus0 = 0;
	float sumMinus45 = 0;
	float sumMinus90 = 0;
	float sumMinus135 = 0;

	for(i=0; i<toneCount; ++i) 
	{
		int iSquare = i*i;
		meanX0      += pCOR0[i]*i;
		sumSqrtX0   += pCOR0[i]*iSquare;

		meanX45     += pCOR45[i]*i;
		sumSqrtX45  += pCOR45[i]*iSquare;

		meanX90     += pCOR90[i]*i;
		sumSqrtX90  += pCOR90[i]*iSquare;

		meanX135    += pCOR135[i]*i;
		sumSqrtX135 += pCOR135[i]*iSquare;

		sum0       += i * pDV0[i];
		sumSquare0 += iSquare*pDV0[i];

		sum45       += i * pDV45[i];
		sumSquare45 += iSquare*pDV45[i];

		sum90       += i * pDV90[i];
		sumSquare90 += iSquare*pDV90[i];

		sum135       += i * pDV135[i];
		sumSquare135 += iSquare*pDV135[i];

		//11. Difference Entropy(0, 45, 90, 135)
		sumMinus0   += pDV0[i]   * log10(pDV0[i]   + GLCM_EPSILON)/denominatorLog;
		sumMinus45  += pDV45[i]  * log10(pDV45[i]  + GLCM_EPSILON)/denominatorLog;
		sumMinus90  += pDV90[i]  * log10(pDV90[i]  + GLCM_EPSILON)/denominatorLog;
		sumMinus135 += pDV135[i] * log10(pDV135[i] + GLCM_EPSILON)/denominatorLog;

	}

	meanY0 = meanX0;
	stdDevX0 = sqrt(sumSqrtX0 - (meanX0 * meanX0));
	stdDevY0 = stdDevX0;

	meanY45 = meanX45;
	stdDevX45 = sqrt(sumSqrtX45 - (meanX45 * meanX45));
	stdDevY45 = stdDevX45;

	meanY90 = meanX90;
	stdDevX90 = sqrt(sumSqrtX90 - (meanX90 * meanX90));
	stdDevY90 = stdDevX90;

	meanY135 = meanX135;
	stdDevX135 = sqrt(sumSqrtX135 - (meanX135 * meanX135));
	stdDevY135 = stdDevX135;

	//10. Difference Variance(0, 45, 90, 135)
	differenceVariance0   = sumSquare0   - sum0*sum0;
	differenceVariance45  = sumSquare45  - sum45*sum45;
	differenceVariance90  = sumSquare90  - sum90*sum90;
	differenceVariance135 = sumSquare135 - sum135*sum135;

	float temp0 = 0, temp45 = 0, temp90 = 0, temp135 = 0;

	for(temp0=0, temp45=0, temp90=0, temp135=0, i=0; i<toneCount; ++i)
	{
		for(j=0; j<toneCount; ++j)
		{
			int val = i*j;

			temp0   += val*MATRIX_ANGLE_0[i][j];
			temp45  += val*MATRIX_ANGLE_45[i][j];
			temp90  += val*MATRIX_ANGLE_90[i][j];
			temp135 += val*MATRIX_ANGLE_135[i][j];

		}
	}

	//3. Correlation(0, 45, 90, 135)
	correlation0   = (temp0-meanX0*meanY0)       / (stdDevX0*stdDevY0);
	correlation45  = (temp45-meanX45*meanY45)    / (stdDevX45*stdDevY45);
	correlation90  = (temp90-meanX90*meanY90)    / (stdDevX90*stdDevY90);
	correlation135 = (temp135-meanX135*meanY135) / (stdDevX135*stdDevY135);

	float hx0 = 0, hy0 = 0;
	float hx45 = 0, hy45 = 0;
	float hx90 = 0, hy90 = 0;
	float hx135 = 0, hy135 = 0;

	float hxyZero0 = 0;
	float hxyZero45 = 0;
	float hxyZero90 = 0;
	float hxyZero135 = 0;

	float hxyOne0 = 0;
	float hxyOne45 = 0;
	float hxyOne90 = 0;
	float hxyOne135 = 0;

	float hxyTwo0 = 0;
	float hxyTwo45 = 0;
	float hxyTwo90 = 0;
	float hxyTwo135 = 0;

	float infoCorrelationOne0 = 0;
	float infoCorrelationOne45 = 0;
	float infoCorrelationOne90 = 0;
	float infoCorrelationOne135 = 0;

	float infoCorrelationTwo0 = 0;
	float infoCorrelationTwo45 = 0;
	float infoCorrelationTwo90 = 0;
	float infoCorrelationTwo135 = 0;

	for(i= 0; i<toneCount; ++i)
	{
		for(j=0; j<toneCount; ++j) 
		{
			//4. Variance(0, 45, 90, 135)
			variance0   += (i-meanX0)*(i-meanX0)     * MATRIX_ANGLE_0[i][j];
			variance45  += (i-meanX45)*(i-meanX45)   * MATRIX_ANGLE_45[i][j];
			variance90  += (i-meanX90)*(i-meanX90)   * MATRIX_ANGLE_90[i][j];
			variance135 += (i-meanX135)*(i-meanX135) * MATRIX_ANGLE_135[i][j];

			hxyOne0  -= MATRIX_ANGLE_0[i][j] * log10(pCOR0[i] * pICy0[j]  + GLCM_EPSILON)/denominatorLog;
			hxyTwo0  -= pCOR0[i] * pICy0[j]  * log10(pCOR0[i] * pICy0[j]  + GLCM_EPSILON)/denominatorLog;
			hxyZero0 -= MATRIX_ANGLE_0[i][j] * log10(MATRIX_ANGLE_0[i][j] + GLCM_EPSILON)/denominatorLog;

			hxyOne45  -= MATRIX_ANGLE_45[i][j] * log10(pCOR45[i] * pICy45[j]  + GLCM_EPSILON)/denominatorLog;
			hxyTwo45  -= pCOR45[i] * pICy45[j] * log10(pCOR45[i] * pICy45[j]  + GLCM_EPSILON)/denominatorLog;
			hxyZero45 -= MATRIX_ANGLE_45[i][j] * log10(MATRIX_ANGLE_45[i][j]  + GLCM_EPSILON)/denominatorLog;

			hxyOne90  -= MATRIX_ANGLE_90[i][j] * log10(pCOR90[i] * pICy90[j]  + GLCM_EPSILON)/denominatorLog;
			hxyTwo90  -= pCOR90[i] * pICy90[j] * log10(pCOR90[i] * pICy90[j]  + GLCM_EPSILON)/denominatorLog;
			hxyZero90 -= MATRIX_ANGLE_90[i][j] * log10(MATRIX_ANGLE_90[i][j]  + GLCM_EPSILON)/denominatorLog;

			hxyOne135  -= MATRIX_ANGLE_135[i][j]  * log10(pCOR135[i] * pICy135[j]  + GLCM_EPSILON)/denominatorLog;
			hxyTwo135  -= pCOR135[i] * pICy135[j] * log10(pCOR135[i] * pICy135[j]  + GLCM_EPSILON)/denominatorLog;
			hxyZero135 -= MATRIX_ANGLE_135[i][j]  * log10(MATRIX_ANGLE_135[i][j]   + GLCM_EPSILON)/denominatorLog;

		}
	}

	for(i=0; i<toneCount; ++i) 
	{
		hx0 -= pCOR0[i] * log10(pCOR0[i] + GLCM_EPSILON)/denominatorLog;
		hy0 -= pICy0[i] * log10(pICy0[i] + GLCM_EPSILON)/denominatorLog;

		hx45 -= pCOR45[i] * log10(pCOR45[i] + GLCM_EPSILON)/denominatorLog;
		hy45 -= pICy45[i] * log10(pICy45[i] + GLCM_EPSILON)/denominatorLog;

		hx90 -= pCOR90[i] * log10(pCOR90[i] + GLCM_EPSILON)/denominatorLog;
		hy90 -= pICy90[i] * log10(pICy90[i] + GLCM_EPSILON)/denominatorLog;

		hx135 -= pCOR135[i] * log10(pCOR135[i] + GLCM_EPSILON)/denominatorLog;
		hy135 -= pICy135[i] * log10(pICy135[i] + GLCM_EPSILON)/denominatorLog;

	}

	//12. Information Measure Correlation 1
	infoCorrelationOne0   =  ((hxyZero0 - hxyOne0)     / (hx0 > hy0 ? hx0 : hy0));
	infoCorrelationOne45  =  ((hxyZero45 - hxyOne45)   / (hx45 > hy45 ? hx45 : hy45));
	infoCorrelationOne90  =  ((hxyZero90 - hxyOne90)   / (hx90 > hy90 ? hx90 : hy90));
	infoCorrelationOne135 =  ((hxyZero135 - hxyOne135) / (hx135 > hy135 ? hx135 : hy135));

	//13. Information Measure Correlation 2
	infoCorrelationTwo0   = sqrt(fabs(1 - exp(-2.0f * (hxyTwo0   - hxyZero0))));
	infoCorrelationTwo45  = sqrt(fabs(1 - exp(-2.0f * (hxyTwo45  - hxyZero45))));
	infoCorrelationTwo90  = sqrt(fabs(1 - exp(-2.0f * (hxyTwo90  - hxyZero90))));
	infoCorrelationTwo135 = sqrt(fabs(1 - exp(-2.0f * (hxyTwo135 - hxyZero135))));

	float sumEntropy0 = 0;
	float sumEntropy45 = 0;
	float sumEntropy90 = 0;
	float sumEntropy135 = 0;

	for(i=2; i <= 2*toneCount; ++i)
	{
		//8. Sum Entropy(0, 45, 90, 135)
		sumEntropy0   -= pSE0[i]   * log10(pSE0[i]   + GLCM_EPSILON)/denominatorLog;
		sumEntropy45  -= pSE45[i]  * log10(pSE45[i]  + GLCM_EPSILON)/denominatorLog;
		sumEntropy90  -= pSE90[i]  * log10(pSE90[i]  + GLCM_EPSILON)/denominatorLog;
		sumEntropy135 -= pSE135[i] * log10(pSE135[i] + GLCM_EPSILON)/denominatorLog;
	}

	float sumAverage0 = 0;
	float sumAverage45 = 0;
	float sumAverage90 = 0;
	float sumAverage135 = 0;

	float sumVariance0 = 0;
	float sumVariance45 = 0;
	float sumVariance90 = 0;
	float sumVariance135 = 0;

	for(i=0; i <= (2*toneCount-2); ++i)
	{
		//6. Sum Average(0, 45, 90, 135)
		sumAverage0   += i*pSA0[i];
		sumAverage45  += i*pSA45[i];
		sumAverage90  += i*pSA90[i];
		sumAverage135 += i*pSA135[i];

		//7. Sum Variance(0, 45, 90, 135)
		sumVariance0   += (i-sumEntropy0)   * (i-sumEntropy0)   * pSA0[i];
		sumVariance45  += (i-sumEntropy45)  * (i-sumEntropy45)  * pSA45[i];
		sumVariance90  += (i-sumEntropy90)  * (i-sumEntropy90)  * pSA90[i];
		sumVariance135 += (i-sumEntropy135) * (i-sumEntropy135) * pSA135[i];

	}

	FEATURE1_ENERGY[0] = sumEnergy0;
	FEATURE1_ENERGY[1] = sumEnergy45;
	FEATURE1_ENERGY[2] = sumEnergy90;
	FEATURE1_ENERGY[3] = sumEnergy135;

	FEATURE2_CONTRAST[0] = bigSumContrast0;
	FEATURE2_CONTRAST[1] = bigSumContrast45;
	FEATURE2_CONTRAST[2] = bigSumContrast90;
	FEATURE2_CONTRAST[3] = bigSumContrast135;

	FEATURE3_CORRELATION[0] = correlation0;
	FEATURE3_CORRELATION[1] = correlation45;
	FEATURE3_CORRELATION[2] = correlation90;
	FEATURE3_CORRELATION[3] = correlation135;

	FEATURE4_VARIANCE[0] = variance0;
	FEATURE4_VARIANCE[1] = variance45;
	FEATURE4_VARIANCE[2] = variance90;
	FEATURE4_VARIANCE[3] = variance135;

	FEATURE5_LOCAL_STABILITY[0] = localStability0;
	FEATURE5_LOCAL_STABILITY[1] = localStability45;
	FEATURE5_LOCAL_STABILITY[2] = localStability90;
	FEATURE5_LOCAL_STABILITY[3] = localStability135;

	FEATURE6_SUM_AVERAGE[0] = sumAverage0;
	FEATURE6_SUM_AVERAGE[1] = sumAverage45;
	FEATURE6_SUM_AVERAGE[2] = sumAverage90;
	FEATURE6_SUM_AVERAGE[3] = sumAverage135;

	FEATURE7_SUM_VARIANCE[0] = sumVariance0;
	FEATURE7_SUM_VARIANCE[1] = sumVariance45;
	FEATURE7_SUM_VARIANCE[2] = sumVariance90;
	FEATURE7_SUM_VARIANCE[3] = sumVariance135;

	FEATURE8_SUM_ENTROPY[0] = sumEntropy0;
	FEATURE8_SUM_ENTROPY[1] = sumEntropy45;
	FEATURE8_SUM_ENTROPY[2] = sumEntropy90;
	FEATURE8_SUM_ENTROPY[3] = sumEntropy135;

	FEATURE9_ENTROPY[0] = -entropy0;
	FEATURE9_ENTROPY[1] = -entropy45;
	FEATURE9_ENTROPY[2] = -entropy90;
	FEATURE9_ENTROPY[3] = -entropy135;

	FEATURE10_DIFFERENCE_VARIANCE[0] = differenceVariance0;
	FEATURE10_DIFFERENCE_VARIANCE[1] = differenceVariance45;
	FEATURE10_DIFFERENCE_VARIANCE[2] = differenceVariance90;
	FEATURE10_DIFFERENCE_VARIANCE[3] = differenceVariance135;
	
	FEATURE11_DIFFERENCE_ENTROPY[0] = -sumMinus0;
	FEATURE11_DIFFERENCE_ENTROPY[1] = -sumMinus45;
	FEATURE11_DIFFERENCE_ENTROPY[2] = -sumMinus90;
	FEATURE11_DIFFERENCE_ENTROPY[3] = -sumMinus135;

	FEATURE12_INFOMATION_MEASURE_CORRELATION1[0] = infoCorrelationOne0;
	FEATURE12_INFOMATION_MEASURE_CORRELATION1[1] = infoCorrelationOne45;
	FEATURE12_INFOMATION_MEASURE_CORRELATION1[2] = infoCorrelationOne90;
	FEATURE12_INFOMATION_MEASURE_CORRELATION1[3] = infoCorrelationOne135;

	FEATURE13_INFOMATION_MEASURE_CORRELATION2[0] = infoCorrelationTwo0;
	FEATURE13_INFOMATION_MEASURE_CORRELATION2[1] = infoCorrelationTwo45;
	FEATURE13_INFOMATION_MEASURE_CORRELATION2[2] = infoCorrelationTwo90;
	FEATURE13_INFOMATION_MEASURE_CORRELATION2[3] = infoCorrelationTwo135;

	int a = 0;

}


#endif
