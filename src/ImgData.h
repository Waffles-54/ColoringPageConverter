/*
  Filename: ImgData.h
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Structure for managing images in this program
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
			unsigned char** imgDataMatrix;
			int width;
			int height;
			int components;
		};
};

