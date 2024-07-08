/*
  Filename: ImgGrayscaler.h
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Class for grayscaling an image
*/

#pragma once
#include "ImgData.h"

class ImgGrayscaler
{
	public:
		void grayscaleImage(ImgData::image_t* img);
};

