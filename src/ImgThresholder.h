/*
  Filename: ImgThresholder.h
  Author: Alice C. Griffith
  Date: 2024

  Description: Class for applying a static threshold limiter to an image
*/

#pragma once

#include "ImgData.h"

#define THRESHOLD 200

class ImgThresholder
{
	public:
		void applyThreshold(ImgData::image_t* img);
};

