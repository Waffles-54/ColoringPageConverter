/*
  Filename: ImgData.h
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Class for gray-scaling an image
*/

#include "ImgData.h"

void ImgData::generateMatrix(image_t* img) {
    // Convert to thread function #TODO
    if (img == NULL) {
        exit(-1);
    }

    // Allocate memory for the 2D array (rows: height)
    img->imgDataMatrix = (unsigned char**)malloc(img->height * sizeof(unsigned char*));
    
    for (int i = 0; i < img->height; i++) {
        img->imgDataMatrix[i] = (unsigned char*)malloc(img->width * img->components * sizeof(unsigned char));
        unsigned int offset = i * img->width * img->components;
        memcpy(img->imgDataMatrix[i], img->imgDataLinear + offset, img->width * img->components * sizeof(unsigned char));
    }
}

void ImgData::flattenMatrix(image_t* img) {
    for (int i = 0; i < img->height; i++) {
        // In-Place replacement (Avoids memory leaks)
        int offset = i * img->width * img->components;
        memcpy(img->imgDataLinear + offset, img->imgDataMatrix[i], img->width * img->components * sizeof(unsigned char));
    }
}