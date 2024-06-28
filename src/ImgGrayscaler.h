/*
  Filename: ImgGrayscaler.h
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Class for grayscaling an image
*/

#pragma once
#include "image_data.h"

class ImgGrayscaler
{
	public:
		void grayscaleImage(image_data::image_t* img);
};

