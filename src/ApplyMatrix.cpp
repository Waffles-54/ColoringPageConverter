#include "ApplyMatrix.h"
void ApplyMatrix::apply(ImgData::image_t* img, const vector<vector<int>>& kernel) {
    // For every pixel not on the border:
    unsigned char** matrixOut = (unsigned char**)malloc(img->height * sizeof(unsigned char*));
    for (int i = 0; i < img->height; i++) {
        matrixOut[i] = (unsigned char*)malloc(img->width * img->components * sizeof(unsigned char));
    }

    // Apply the filter
    for (int y = 1; y < img->height - 1; y++) {
        for (int x = 1; x < img->width * img->components - 1; x++) {
            int sum = 0;

            // Apply the kernel
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int pixVal = img->imgDataMatrix[y + ky][x + kx];
                    sum += pixVal * kernel[ky + 1][kx + 1];
                }
            }

            // Clamp the result to ensure it fits within 0-255
            matrixOut[y][x] = std::min(std::max(sum, 0), 255);
        }
    }

    for (int i = 1; i < img->height - 1; i++) {
        for (int j = 1; j < img->width * img->components - 1; j++) {
            img->imgDataMatrix[i][j] = matrixOut[i][j];
        }
    }

    for (int i = 0; i < img->height; ++i) {
        free(matrixOut[i]);
    }
    free(matrixOut);
};

void ApplyMatrix::generateMatrix(ImgData::image_t* img) {
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

void ApplyMatrix::flattenMatrix(ImgData::image_t* img) {
    for (int i = 0; i < img->height; i++) {
        // In-Place replacement (Avoids memory leaks)
        int offset = i * img->width * img->components;
        memcpy(img->imgDataLinear + offset, img->imgDataMatrix[i], img->width * img->components * sizeof(unsigned char));
    }
}