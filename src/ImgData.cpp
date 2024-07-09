/*
  Filename: ImgData.h
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Class for gray-scaling an image
*/

#include "ImgData.h"

#include <iostream>
#include <string>

void ImgData::generateMatrix(image_t* img) {
	// 2D allocated matrix container (rows: sizeof(pointer) * rows)
	int** matrixData = (int**)malloc(sizeof(int*) * img->height);

	for (int i = 0; i < img->height; i++) {
		// Column allocation: sizeof(pointer) * collumns * pixelInfo (components)
		matrixData[i] = (int*)malloc(img->width * img->components * sizeof(int));
		memcpy(matrixData[i], img->imgDataLinear + (i * img->width * img->components), img->width * img->components * sizeof(int));
	}
	img->imgDataMatrix = matrixData;
}