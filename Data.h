#ifndef _DATA_H_
#define _DATA_H_

#if USE_QUANTIZATION_LEVEL8
static const int MAX_GRAY_LEVEL_VAL	= 8;
static unsigned char QUANTIZATION_LEVEL8_LUT[256] = 
{
	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 
	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 
	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,	2,
	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,
	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,
	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,
	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,
	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
};
#endif

#if USE_QUANTIZATION_LEVEL16
static const int MAX_GRAY_LEVEL_VAL	= 16;
static unsigned char QUANTIZATION_LEVEL16_LUT[256] = 
{
	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 
	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 
	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 	2, 
	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,	3,
	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,	4,
	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,	5,
	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,
	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,
	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,	9,
	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,	10,
	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,	11,
	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,	12,
	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,	13,
	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,
	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,
};
#endif

#if USE_QUANTIZATION_LEVEL32
static const int MAX_GRAY_LEVEL_VAL	= 32;
static unsigned char QUANTIZATION_LEVEL32_LUT[256] = 
{
	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 
	1, 	1, 	1, 	1, 	1, 	1, 	1, 	1, 
	2,	2,	2,	2,	2,	2,	2,	2,
	3,	3,	3,	3,	3,	3,	3,	3,
	4,	4,	4,	4,	4,	4,	4,	4,
	5,	5,	5,	5,	5,	5,	5,	5,
	6,	6,	6,	6,	6,	6,	6,	6,
	7,	7,	7,	7,	7,	7,	7,	7,
	8,	8,	8,	8,	8,	8,	8,	8,
	9,	9,	9,	9,	9,	9,	9,	9,
	10,	10,	10,	10,	10,	10,	10,	10,
	11,	11,	11,	11,	11,	11,	11,	11,
	12,	12,	12,	12,	12,	12,	12,	12,
	13,	13,	13,	13,	13,	13,	13,	13,
	14,	14,	14,	14,	14,	14,	14,	14,
	15,	15,	15,	15,	15,	15,	15,	15,
	16,	16,	16,	16,	16,	16,	16,	16,
	17,	17,	17,	17,	17,	17,	17,	17,
	18,	18,	18,	18,	18,	18,	18,	18,
	19,	19,	19,	19,	19,	19,	19,	19,
	20,	20,	20,	20,	20,	20,	20,	20,
	21,	21,	21,	21,	21,	21,	21,	21,
	22,	22,	22,	22,	22,	22,	22,	22,
	23,	23,	23,	23,	23,	23,	23,	23,
	24,	24,	24,	24,	24,	24,	24,	24,
	25,	25,	25,	25,	25,	25,	25,	25,
	26,	26,	26,	26,	26,	26,	26,	26,
	27,	27,	27,	27,	27,	27,	27,	27,
	28,	28,	28,	28,	28,	28,	28,	28,
	29,	29,	29,	29,	29,	29,	29,	29,
	30,	30,	30,	30,	30,	30,	30,	30,
	31,	31,	31,	31,	31,	31,	31,	31,
};
#endif

#if USE_QUANTIZATION_LEVEL64
static const int MAX_GRAY_LEVEL_VAL	= 64;
static unsigned char QUANTIZATION_LEVEL64_LUT[256] = 
{
	0, 	0, 	0, 	0, 
	1, 	1, 	1, 	1, 
	2,	2,	2,	2,
	3,	3,	3,	3,
	4,	4,	4,	4,
	5,	5,	5,	5,
	6,	6,	6,	6,
	7,	7,	7,	7,
	8,	8,	8,	8,
	9,	9,	9,	9,
	10,	10,	10,	10,
	11,	11,	11,	11,
	12,	12,	12,	12,
	13,	13,	13,	13,
	14,	14,	14,	14,
	15,	15,	15,	15,
	16,	16,	16,	16,
	17,	17,	17,	17,
	18,	18,	18,	18,
	19,	19,	19,	19,
	20,	20,	20,	20,
	21,	21,	21,	21,
	22,	22,	22,	22,
	23,	23,	23,	23,
	24,	24,	24,	24,
	25,	25,	25,	25,
	26,	26,	26,	26,
	27,	27,	27,	27,
	28,	28,	28,	28,
	29,	29,	29,	29,
	30,	30,	30,	30,
	31,	31,	31,	31,
	32,	32,	32,	32,
	33,	33,	33,	33,
	34,	34,	34,	34,
	35,	35,	35,	35,
	36,	36,	36,	36,
	37,	37,	37,	37,
	38,	38,	38,	38,
	39,	39,	39,	39,
	40,	40,	40,	40,
	41,	41,	41,	41,
	42,	42,	42,	42,
	43,	43,	43,	43,
	44,	44,	44,	44,
	45,	45,	45,	45,
	46,	46,	46,	46,
	47,	47,	47,	47,
	48,	48,	48,	48,
	49,	49,	49,	49,
	50,	50,	50,	50,
	51,	51,	51,	51,
	52,	52,	52,	52,
	53,	53,	53,	53,
	54,	54,	54,	54,
	55,	55,	55,	55,
	56,	56,	56,	56,
	57,	57,	57,	57,
	58,	58,	58,	58,
	59,	59,	59,	59,
	60,	60,	60,	60,
	61,	61,	61,	61,
	62,	62,	62,	62,
	63,	63,	63,	63,
};
#endif

#if NO_USE_QUANTIZATION_LEVEL
static const int MAX_GRAY_LEVEL_VAL	= 255;
#endif

static const int MAX_TONE_LEVEL	= (MAX_GRAY_LEVEL_VAL+1);	

static const int MAX_TONE_LEVEL_DOUBLE	= (MAX_TONE_LEVEL*2);

static unsigned char QUANTIZATION_IMAGE[IMAGE_WIDTH*IMAGE_HEIGHT] = {0, }; 
static int			 TONE_LUT[MAX_TONE_LEVEL] = {-1, };

static float MATRIX_ANGLE_0[MAX_TONE_LEVEL][MAX_TONE_LEVEL] = {0, };
static float MATRIX_ANGLE_45[MAX_TONE_LEVEL][MAX_TONE_LEVEL] = {0, };
static float MATRIX_ANGLE_90[MAX_TONE_LEVEL][MAX_TONE_LEVEL] = {0, };
static float MATRIX_ANGLE_135[MAX_TONE_LEVEL][MAX_TONE_LEVEL] = {0, };

//GLCM Feature 13
static float FEATURE1_ENERGY[ANGLE_BIN_NUM] = {0, }; // = Angular Second Moment
static float FEATURE2_CONTRAST[ANGLE_BIN_NUM] = {0, }; // = Inertia
static float FEATURE3_CORRELATION[ANGLE_BIN_NUM] = {0, }; 
static float FEATURE4_VARIANCE[ANGLE_BIN_NUM] = {0, };  // = Sum of Squares
static float FEATURE5_LOCAL_STABILITY[ANGLE_BIN_NUM] = {0, }; // = Inverse Difference Moment
static float FEATURE6_SUM_AVERAGE[ANGLE_BIN_NUM] = {0, };  
static float FEATURE7_SUM_VARIANCE[ANGLE_BIN_NUM] = {0, };
static float FEATURE8_SUM_ENTROPY[ANGLE_BIN_NUM] = {0, };
static float FEATURE9_ENTROPY[ANGLE_BIN_NUM] = {0, }; 
static float FEATURE10_DIFFERENCE_VARIANCE[ANGLE_BIN_NUM] = {0, };
static float FEATURE11_DIFFERENCE_ENTROPY[ANGLE_BIN_NUM] = {0, };
static float FEATURE12_INFOMATION_MEASURE_CORRELATION1[ANGLE_BIN_NUM] = {0, };
static float FEATURE13_INFOMATION_MEASURE_CORRELATION2[ANGLE_BIN_NUM] = {0, };

#endif