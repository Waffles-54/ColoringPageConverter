/*
  Filename: ImgGrayscaler.h
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Class for gray scaling an image
*/

#include "ImgGrayscaler.h"

void ImgGrayscaler::grayscaleImage(ImgData::image_t* img) {
	// Grayscale the image using an averaging technique [(R+G+B)/3]
	int pixDensity = img->height * img->width * img->components;
	int avg;

	for (int i = 0; i < pixDensity; i+=img->components) {
		// Calculate average pixel value
		avg = 0;
		for (int j = 0; j < img->components; j++) {
			avg += img->imgDataLinear[i+j];
		}
		avg /= img->components;

		// apply pixel average across all components
		for (int j = 0; j < img->components; j++) {
			img->imgDataLinear[i + j] = avg;
		}
	}
}