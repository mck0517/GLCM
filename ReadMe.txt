* Reference: http://haralick.org/journals/TexturalFeatures.pdf

* File Description
- Param.h: parameters setting for quantization level, test image size, neighborhood pixel distance, angle range 
- Vision_Test: main fuction
- GLCM: image quantization, GLCM calculation
- Data.h: arrays for algorithms 

* Program Description
- You can use any kind of OpenCV Version.
- OpenCV was used only for image reading fuction(ex: cvLoadImage("lenna.bmp", CV_LOAD_IMAGE_GRAYSCALE)).
- This program use only gray scale image format But you can use color image format using above opencv code.  
- If you run the main fuction(GLCM_Test), you can see the results of the haralick`s features.
- haralick`s features: Energy, Contrast, Correlation, Sum of Squares, Local Stability, Sum Average, Sum Variance, Sum Entropy, Entropy, Difference Variance, Difference Entropy, Information Measure Correlation 1 and Information Measure Correlation 2.
 