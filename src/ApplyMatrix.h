#pragma once

#include "ImgData.h"
#include <vector> 

#define THRESHOLD 225


// #TODO, Consider mergeing this class with ImgData, its so closely tied that splitting
// the class is creating external coupling
class ApplyMatrix {
	public:
        // Kernals
        const vector<vector<int>> sharpKernal = {
            {-1, -1, -1},
            {-1,  9, -1},
            {-1, -1, -1}
        };
        const vector<vector<int>> sobelVert = {
            {1,  0, -1},
            {2,  0, -2},
            {1,  0, -1}
        };
        const vector<vector<int>> sobelHor = {
            {1,   2, 1},
            {-1,  8, -1},
            {-1, -2, -1}
        };
        const vector<vector<int>> ridgeKernal = {
            {0, -1, 0},
            {-1, 4, -1},
            {0, -1, 0}
        };

        // Application Functions
        void generateMatrix(ImgData::image_t* img);
        void flattenMatrix(ImgData::image_t* img);
        void fillEdges(ImgData::image_t* img);
		void apply(ImgData::image_t* img, const vector<vector<int>>& kernel);
        void fixSpices(ImgData::image_t* img);


};

