/*
  Filename: ImgSharpener.h
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Class for sharpening an image
*/

#include "ImgSharpener.h"

void ImgSharpener::sharpenImage(image_data::image_t* img) {
	int pixDensity = img->height * img->width * img->components;
    int sum, x, y;
	for (int i = 0; i < pixDensity; i += img->components) {
        x = (i / img->components) % img->width;
        y = (i / img->components) / img->width;
        sum = 0;
        for (int ky = -1; ky <= 1; ++ky) {
            for (int kx = -1; kx <= 1; ++kx) {
                int ny = std::min(std::max(y + ky, 0), img->height - 1);
                int nx = std::min(std::max(x + kx, 0), img->width - 1);
                int pixel = img->imgData[(ny * img->width + nx) * img->components];
                sum += pixel * sharpKernal[ky + 1][kx + 1];
            }
        }
        // Clamp the result to [0, 255]
        sum = std::min(std::max(sum, 0), 255);
        img->imgData[(y * img->width + x) * img->components] = sum;
	}
}