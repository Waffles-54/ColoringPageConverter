/*
  Filename: ImgSharpener.h
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Class for sharpening an image
*/

#pragma once
#include "image_data.h"

#define KERNEL_SIZE 3

class ImgSharpener
{
	public:
		void sharpenImage(image_data::image_t* img);
	private:
		const int sharpKernal[3][3] = {
			{0, -1, 0}, 
			{-1, 5, -1},
			{0, -1, 0}
		};
};

