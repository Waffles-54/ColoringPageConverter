#include "ImgThresholder.h"

void ImgThresholder::applyThreshold(ImgData::image_t* img) {
	int pixDensity = img->height * img->width * img->components;
	for (int i = 0; i < pixDensity; i += img->components) {
		//Apply thresholds across all pixels
		int value = ((int)img->imgDataLinear[i] > THRESHOLD) ? 0 : 255;
		img->imgDataLinear[i] = value;
		img->imgDataLinear[i + 1] = value;
		img->imgDataLinear[i + 2] = value;
	}
}