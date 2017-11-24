// Vision_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include "Param.h"
#include "GLCM.h"

int _tmain(int argc, _TCHAR* argv[])
{
	IplImage *iplInputImage = cvLoadImage("lenna.bmp", CV_LOAD_IMAGE_GRAYSCALE);

	const int imageWidth = iplInputImage->width;
	const int imageHeight = iplInputImage->height;
	assert(imageWidth == IMAGE_WIDTH || imageHeight == IMAGE_HEIGHT);

	unsigned char *inputImage = (unsigned char *)malloc(sizeof(unsigned char)*imageWidth*imageHeight);
	ConvertIplImageToBuffer(iplInputImage, inputImage);

	//////////////////////////////////////////////////////////////////////////
	//Run Algorithm
	const int toneCount = PreProcessingForGLCM(inputImage); 
	GetGLCM(toneCount);
	GetGLCMFeature(toneCount);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//Result print
	//1. FEATURE 1(ENERGY = Angular Second Moment)
	register int i;
	printf("< Feature 1: Energy >\n");
	for(i=0; i<ANGLE_BIN_NUM; i++)
	{
		printf("%d: %f\n", i, FEATURE1_ENERGY[i]);
	}

	//2. FEATURE 2(CONTRAST = Inertia)
	printf("\n");
	printf("< Feature 2: Contrast >\n");
	for(i=0; i<ANGLE_BIN_NUM; i++)
	{
		printf("%d: %f\n", i, FEATURE2_CONTRAST[i]);
	}

	//3. FEATURE 3(CORRELATION)
	printf("\n");
	printf("< Feature 3: Correlation >\n");
	for(i=0; i<ANGLE_BIN_NUM; i++)
	{
		printf("%d: %f\n", i, FEATURE3_CORRELATION[i]);
	}

	//4. FEATURE 4(VARIANCE = Sum of Squares)
	printf("\n");
	printf("< Feature 4: Variance >\n");
	for(i=0; i<ANGLE_BIN_NUM; i++)
	{
		printf("%d: %f\n", i, FEATURE4_VARIANCE[i]);
	}

	//5. FEATURE 5(LOCAL STABILITY = Inverse Difference Moment)
	printf("\n");
	printf("< Feature 5: Local Stability >\n");
	for(i=0; i<ANGLE_BIN_NUM; i++)
	{
		printf("%d: %f\n", i, FEATURE5_LOCAL_STABILITY[i]);
	}

	//6. FEATURE 6(SUM AVERAGE)
	printf("\n");
	printf("< Feature 6: Sum Average >\n");
	for(i=0; i<ANGLE_BIN_NUM; i++)
	{
		printf("%d: %f\n", i, FEATURE6_SUM_AVERAGE[i]);
	}

	//7. FEATURE 7(SUM VARIANCE)
	printf("\n");
	printf("< Feature 7: Sum Variance >\n");
	for(i=0; i<ANGLE_BIN_NUM; i++)
	{
		printf("%d: %f\n", i, FEATURE7_SUM_VARIANCE[i]);
	}

	//8. FEATURE 8(SUM ENTROPY)
	printf("\n");
	printf("< Feature 8: Sum Entropy >\n");
	for(i=0; i<ANGLE_BIN_NUM; i++)
	{
		printf("%d: %f\n", i, FEATURE8_SUM_ENTROPY[i]);
	}

	//9. FEATURE 9(ENTROPY)
	printf("\n");
	printf("< Feature 9: Entropy >\n");
	for(i=0; i<ANGLE_BIN_NUM; i++)
	{
		printf("%d: %f\n", i, FEATURE9_ENTROPY[i]);
	}

	//10. FEATURE 10(DIFFERENCE VARIANCE)
	printf("\n");
	printf("< Feature 10: Difference Variance >\n");
	for(i=0; i<ANGLE_BIN_NUM; i++)
	{
		printf("%d: %f\n", i, FEATURE10_DIFFERENCE_VARIANCE[i]);
	}

	//11. FEATURE 11(DIFFERENCE ENTROPY)
	printf("\n");
	printf("< Feature 11: Difference Entropy >\n");
	for(i=0; i<ANGLE_BIN_NUM; i++)
	{
		printf("%d: %f\n", i, FEATURE11_DIFFERENCE_ENTROPY[i]);
	}

	//12. FEATURE 12(INFOMATION MEASURE CORRELATION 1)
	printf("\n");
	printf("< Feature 12: Information Measure Correlation 1>\n");
	for(i=0; i<ANGLE_BIN_NUM; i++)
	{
		printf("%d: %f\n", i, FEATURE12_INFOMATION_MEASURE_CORRELATION1[i]);
	}

	//13. FEATURE 13(INFOMATION MEASURE CORRELATION 2)
	printf("\n");
	printf("< Feature 13: Information Measure Correlation 2>\n");
	for(i=0; i<ANGLE_BIN_NUM; i++)
	{
		printf("%d: %f\n", i, FEATURE13_INFOMATION_MEASURE_CORRELATION2[i]);
	}
	//////////////////////////////////////////////////////////////////////////

	if(iplInputImage != NULL)
	{
		cvReleaseImage(&iplInputImage);
	}

	if(inputImage != NULL)
	{
		free(inputImage);
	}

	printf("\n");
	printf("Press enter for exit!\n");

	getchar();

	return 0;
}

