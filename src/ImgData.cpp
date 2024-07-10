/*
  Filename: ImgData.h
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Class for gray-scaling an image
*/

#include "ImgData.h"

bool compareArrays(ImgData::image_t* img) {
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width * img->components; j++) {
            if (img->imgDataMatrix[i][j] != img->imgDataLinear[i * img->width * img->components + j]) {
                printf("Mismatch at row %d, col %d: %u != %u\n", i, j, img->imgDataMatrix[i][j], img->imgDataLinear[i * img->width * img->components + j]);
                return false;
            }
        }
    }
    return true;
}

void ImgData::generateMatrix(image_t* img) {
    // Allocate memory for the 2D array (rows: height)
    img->imgDataMatrix = (unsigned int**)malloc(img->height * sizeof(unsigned int*));
    if (img->imgDataMatrix == NULL) {
        fprintf(stderr, "Memory allocation failed for imgDataMatrix.\n");
        exit(1);
    }

    for (int i = 0; i < img->height; i++) {
        // Allocate memory for each row (columns: width * components)
        img->imgDataMatrix[i] = (unsigned int*)malloc(img->width * img->components * sizeof(unsigned int));
        if (img->imgDataMatrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for imgDataMatrix[%d].\n", i);
            exit(1);
        }

        // Copy the row data from the 1D array to the 2D array
        memcpy(img->imgDataMatrix[i], img->imgDataLinear + (i * img->width * img->components), img->width * img->components * sizeof(unsigned int));
    }
}



