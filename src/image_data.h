/*
  Filename: image_data.h
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Class for grayscaling an image
*/
#pragma once

#include <string>
using namespace std;

// Rolled image data structure
class image_data {
	public:
		struct image_t {
			string full_path;
			string ext;
			string filename;
			string out_path;
			unsigned char* imgData;
			int width;
			int height;
			int components;
		};
		//struct pixel_data{

		//};
};