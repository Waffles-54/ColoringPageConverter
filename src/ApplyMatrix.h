#pragma once

#include "ImgData.h"
#include <vector> 

class ApplyMatrix {
	public:
        const vector<vector<int>> sharpKernal = {
            {0, -1, 0},
            {-1, 5, -1},
            {0, -1, 0}
        };
        const vector<vector<int>> edgeKernal = {
            {-1, -1, -1},
            {-1,  8, -1},
            {-1, -1, -1}
        };
        void generateMatrix(ImgData::image_t* img);
        void flattenMatrix(ImgData::image_t* img);
		void apply(ImgData::image_t* img, const vector<vector<int>>& kernel);
};

