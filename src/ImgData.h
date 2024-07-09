/*
  Filename: ImgData.h
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Class for grayscaling an image
*/

#pragma once

#include <string>
using namespace std;

class ImgData
{
	public:
		struct image_t {
			string filename;
			string out_path;
			unsigned char* imgDataLinear;
			int** imgDataMatrix;
			int width;
			int height;
			int components;
		};

		void generateMatrix(image_t* img);
		void cleanMemory(image_t* img);
};

