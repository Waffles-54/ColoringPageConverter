/*
  Filename: ImgSharpener.h
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Class for sharpening an image
*/

#include "ImgSharpener.h"

void ImgSharpener::sharpenImage(ImgData::image_t* img) {
	// For every pixel not on the border:
    unsigned char** matrixOut = (unsigned char**)malloc(img->height * sizeof(unsigned char*));
    for (int i = 0; i < img->height; i++) {
        matrixOut[i] = (unsigned char*)malloc(img->width * img->components * sizeof(unsigned char));
    }


    //////////////////////////////////////////////////////
    // Matrix m       Kernal k
    // [ 1 2 3      [ 0 -1  0
    //   4 5 6   ->  -1 -5 -1    -> sum[(m*k)]/9
    //   7 8 9        0 -1  0 ]
    //////////////////////////////////////////////////////
    // Apply the filter
    for (int y = 1; y < img->height - 1; y++) {
        for (int x = 1; x < img->width * img->components - 1; x++) {
            int sum = 0;

            // Apply the kernel
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int pixVal = img->imgDataMatrix[y + ky][x + kx];
                    sum += pixVal * sharpKernal[ky + 1][kx + 1];
                }
            }

            // Average the result?
            //sum /= 9; // #TODO: Magic (#)

            // Clamp the result to ensure it fits within 0-255
            matrixOut[y][x] = std::min(std::max(sum, 0), 255);
        }
    }

    for (int i = 1; i < img->height - 1; i++) {
        for (int j = 1; j < img->width * img->components - 1; j++) {
            img->imgDataMatrix[i][j] = matrixOut[i][j];
        }
        //int x = 1; x < img->width* img->components - 1; x++
    }

    for (int i = 0; i < img->height; ++i) {
        free(matrixOut[i]);
    }
    free(matrixOut);
}

