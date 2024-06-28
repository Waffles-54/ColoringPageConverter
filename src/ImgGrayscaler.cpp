/*
  Filename: ImgGrayscaler.h
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Class for grayscaling an image
*/

#include "ImgGrayscaler.h"

void ImgGrayscaler::grayscaleImage(image_data::image_t* img) {
	// Grayscale the image using an averaging technique [(R+G+B)/3]
	int pixDensity = img->height * img->width * img->components;
	int avg;

	for (int i = 0; i < pixDensity; i+=img->components) {
		// Calculate averege pixel value
		avg = 0;
		for (int j = 0; j < img->components; j++) {
			avg += img->imgData[i+j];
		}
		avg /= img->components;

		// apply pixel avege across all components
		for (int j = 0; j < img->components; j++) {
			img->imgData[i + j] = avg;
		}
	}
}