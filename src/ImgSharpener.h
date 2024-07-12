/*
  Filename: ImgSharpener.h
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Class for sharpening an image
*/

#pragma once
#include "ImgData.h"

class ImgSharpener
{
	public:
		void sharpenImage(ImgData::image_t* img);
	private:
		const int KERNALSIZE = 3;
		const int sharpKernal[3][3] = {
			{0, -1, 0}, 
			{-1, 5, -1},
			{0, -1, 0}
		};
};

