/*
  Filename: ProcessManager.cpp
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Implentation of ProcessManager.h, Entry point of program, manages workload distribution
*/

#include "ProcessManager.h"

// Pre-Proccessors for stb_image.h
#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_BMP
#define STBI_NO_PSD
#define STBI_NO_TGA
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_PNM
#include "../lib/stb_image.h" // #TODO(Waffles_54)

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


using namespace std;

void ProcessManager::initiateThreads(vector<string> paths) {
    vector<thread> work;
    // Generate threads
    for (string path : paths) {
        work.push_back(thread(&ProcessManager::processThread, this, path));
    }

    // Syncronize threads
    for (int i = 0; i < work.size(); i++) {
        work[i].join();
    }
}

bool ProcessManager::processThread(string path) {
    //int x, y, n;
    image_t* img = new image_t;
    
    // Tokenize path
    string token;
    vector<string> tokens;
    stringstream userStream(path);
    while (getline(userStream, token, '.')) {
        tokens.push_back(token);
    }

    // assumes file and not PATH
    if (tokens.size() != 2) {
        cerr << "Invalid filepath: " << path << ", Are you including the file extension?";
        return -1;
    }

    // Setup image structure
    img->full_path = path;
    img->filename = tokens[0];
    img->ext = tokens[1];
    img->out_path = tokens[0] + "_o." + tokens[1]; // staticly sets the output to the same directory #TODO(waffles_54)
    img->width = 0;
    img->height = 0;
    img->components = 0;

    // Read phase
    img->imgData = stbi_load(img->full_path.c_str(), &img->width, &img->height, &img->components, 0);

    if (img->imgData == nullptr) {
        std::cerr << "Failed to load " << path << endl;
        return false;
    }

    // Process Phase #TODO (waffles_54)


    // Output phase
    stbi_write_jpg(img->out_path.c_str(), img->width, img->height, img->components, img->imgData, 100);
    
    // Cleanup phase
    stbi_image_free(img->imgData);
    free(img);
    return true;
}

// Entry point of the program
int main(int argc, char* argv[]) {
    ////////////////////////////// Program Flow /////////////////////////////
    // Load images as passed into the command line
    // Grayscale the image
    // Sharpen the image
    // Clean up blur
    // Edge Detection
    // Thresholding
    // Inversion
    // Output (PNG)
    //////////////////////////////////////////////////////////////////////////
        
    // Data setup
    ProcessManager pm;

    string userInput = "";
    vector<string> filepaths;

    // Debugging data
    unsigned int badReads = 0;  // Track how many files failed to load
    vector<string> badFiles;


    if (argc == 1) {
        // No arguments passed
        // Get the directory or image to
        cout << "Enter a list of files/directories to process\nSeperate entries with a space, Include the extension\n";
        while (userInput.size() == 0) {
            getline(cin, userInput, '\n');
        }
    } else {
        // Arguments passed and need to be processed #TODO (Waffles_54)
    }

    // Tokenize input
    string token;
    stringstream userStream(userInput);
    while (getline(userStream, token, ' ')) {
        filepaths.push_back(token);
    }
    
    // Pass control to the processManager
    pm.initiateThreads(filepaths);
    return 0;
}