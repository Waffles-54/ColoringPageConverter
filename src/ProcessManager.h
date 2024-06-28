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
		bool processThread(string path);

};

/*

*/