#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <thread>

using namespace std;

class ProcessManager
{
	public:
		void initiateThreads(vector<string> paths);

	private:
        // Rolled image data structure
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

		bool processThread(string path);

};

/*

*/