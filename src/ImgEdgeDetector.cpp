#include "ImgEdgeDetector.h"

void ImgEdgeDetector::detectEdges(ImgData::image_t* img) {
    //int pixDensity = img->height * img->width * img->components;
    for (int y = 1; y < img->height - 1; y++) {
        for (int x = 1; x < img->width - 1; x++) {
            int sum = 0;

            // Apply the kernel
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int pixelValue = img->imgDataLinear[(y + ky) * img->width + (x + kx)];
                    sum += pixelValue * sharpKernal[ky + 1][kx + 1];
                }
            }

            // Clamp the result to ensure it fits within 0-255
            int sharpenedValue = std::min(std::max(sum, 0), 255);
            img->imgDataLinear[y * img->width + x] = sharpenedValue;
        }
    }
}