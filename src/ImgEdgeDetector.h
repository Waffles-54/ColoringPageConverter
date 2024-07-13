/*
  Filename: ImgEdgeDetector.h
  Author: Alice C. Griffith
  Date: 2024

  Description: Class for detecting edges in an image
*/

#pragma once

#include "ImgData.h"

class ImgEdgeDetector
{
	public:

		void detectEdges(ImgData::image_t* img);
	private:
		const int edgeKernal[3][3] = {
			{-1, -1, -1},
			{-1,  8, -1},
			{-1, -1, -1}
		};
};

