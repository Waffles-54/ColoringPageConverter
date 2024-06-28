#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <thread>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class ProcessManager
{
	public:
		void initiateThreads(vector<string> paths);

	private:
		bool processThread(string path);

};

/*

*/