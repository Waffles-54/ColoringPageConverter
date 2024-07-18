#include "ApplyMatrix.h"
void ApplyMatrix::apply(ImgData::image_t* img, const vector<vector<int>>& kernel) {

    unsigned char** matrixOut = (unsigned char**)malloc(img->height * sizeof(unsigned char*));
    for (int i = 0; i < img->height; i++) {
        matrixOut[i] = (unsigned char*)malloc(img->width * img->components * sizeof(unsigned char));
    }

    // #TODO, because were ignoring the border, it gets set to black. 
    // this shows in the final result.
    // For every pixel not on the border, Apply the filter
    for (int y = 1; y < img->height - 1; y++) {
        for (int x = 1; x < img->width * img->components - 1; x++) {
            int sum = 0;

            // Apply the kernel
            // #TODO, this forces a 3x3 kernal, consider making it dynamic
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

    // replace the original matrix with the calculated data
    for (int i = 1; i < img->height - 1; i++) {
        for (int j = 1; j < img->width * img->components - 1; j++) {
            img->imgDataMatrix[i][j] = matrixOut[i][j];
        }
    }

    // Cleanup the calculation matrix
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

    // Load the contents of the array expression
    for (int i = 0; i < img->height; i++) {
        img->imgDataMatrix[i] = (unsigned char*)malloc(img->width * img->components * sizeof(unsigned char));
        unsigned int offset = i * img->width * img->components;
        memcpy(img->imgDataMatrix[i], img->imgDataLinear + offset, img->width * img->components * sizeof(unsigned char));
    }
}

void ApplyMatrix::flattenMatrix(ImgData::image_t* img) {
    for (int i = 0; i < img->height; i++) {
        // In-Place replacement
        int offset = i * img->width * img->components;
        memcpy(img->imgDataLinear + offset, img->imgDataMatrix[i], img->width * img->components * sizeof(unsigned char));
    }
}

void ApplyMatrix::fillEdges(ImgData::image_t* img) {
    /*for (int i = 0; i < img->width * img->components; i++) {
        img->imgDataMatrix[0][i] = 0;
    }*/
    memset(img->imgDataMatrix[0], 0, img->width * img->components);
    memset(img->imgDataMatrix[1], 0, img->width * img->components);
    memset(img->imgDataMatrix[img->height - 2], 0, img->width * img->components);
    memset(img->imgDataMatrix[img->height - 1], 0, img->width * img->components);
    for (int i = 2; i < img->height - 2; i++) {
        // first x elements in row
        img->imgDataMatrix[i][0] = 0;
        img->imgDataMatrix[i][1] = 0;
        img->imgDataMatrix[i][2] = 0;
        // last x elements in row
        img->imgDataMatrix[i][img->width * img->components - 1] = 0;
        img->imgDataMatrix[i][img->width * img->components - 2] = 0;
        img->imgDataMatrix[i][img->width*img->components - 3] = 0;

    }
}

void ApplyMatrix::fixSpices(ImgData::image_t* img) {
    int pixDensity = img->height * img->width * img->components;
    int val;
    for (int i = 0; i < pixDensity; i += img->components) {
        val = 255;
        for (int j = 0; j < img->components; j++) {
            if (img->imgDataLinear[i + j] > THRESHOLD) {
                val = 0;
            }
        }

        // apply pixel average across all components
        for (int j = 0; j < img->components; j++) {
            img->imgDataLinear[i + j] = val;
        }
    }
}
