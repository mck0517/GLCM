#ifndef _PARAM_H_
#define _PARAM_H_

//gray level quantization level: only choose one option  
#define USE_QUANTIZATION_LEVEL8		1
#define USE_QUANTIZATION_LEVEL16	0
#define USE_QUANTIZATION_LEVEL32	0
#define USE_QUANTIZATION_LEVEL64	0
#define NO_USE_QUANTIZATION_LEVEL	0

static const int IMAGE_WIDTH = 256;
static const int IMAGE_HEIGHT = 256;

static const int DISTANCE = 1; //pixel distance 

static const int ANGLE_BIN_NUM = 4;  //Angle range(0, 45, 90, 135) 
static const float GLCM_EPSILON	= 0.000000001f;


#endif