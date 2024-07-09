/*
  Filename: ProcessManager.cpp
  Author: Alice C. Griffith
  Date: 06/2024 - 07/2024

  Description: Implentation of ProcessManager.h, Entry point of program, manages workload distribution
*/

#include "ProcessManager.h"
#include "ImgData.h"
#include "ImgGrayscaler.h"
#include "ImgSharpener.h"


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

void ProcessManager::initiateThreads(vector<string> paths) {
    vector<thread> work;
    // Generate threads
    for (string path : paths) {
        work.push_back(thread(&ProcessManager::processThread, this, path));
    }

    // Synchronize threads
    for (int i = 0; i < work.size(); i++) {
        work[i].join();
    }
}

bool ProcessManager::processThread(string path) {
    ImgData imgdata;
    ImgData::image_t* img = new ImgData::image_t;
    ImgGrayscaler* imgGrayscaler = new ImgGrayscaler;
    ImgSharpener* imgSharpener = new ImgSharpener;

    // Tokenize path (ext/filename)
    string token;
    vector<string> tokens;
    stringstream userStream(path);

    while (getline(userStream, token, '\\')) {
        tokens.push_back(token);
    }

    // assumes file and not PATH
    if (tokens.size() != 2) {
        cerr << "Invalid filepath: " << path << ", Are you including the file extension?";
        return -1;
    }

    // Setup image structure
    img->filename = tokens.back();
    img->out_path = "out\\" + tokens[1]; // staticly sets the output #TODO(waffles_54)
    img->width = 0;
    img->height = 0;
    img->components = 0;

    // Read phase
    img->imgDataLinear = stbi_load(path.c_str(), &img->width, &img->height, &img->components, 0);

    if (img->imgDataLinear == nullptr) {
        std::cerr << "Failed to load " << path << endl;
        return false;
    }

    imgdata.generateMatrix(img); // #TODO refactor this


    // #TODO Seperate work into threads
    imgSharpener->sharpenImage(img);
    imgGrayscaler->grayscaleImage(img);
    // Sharpen the image
    
    // Clean up blur
    // Edge Detection
    // Thresholding
    // Inversion


    // Output phase
    stbi_write_jpg(img->out_path.c_str(), img->width, img->height, img->components, img->imgDataLinear, 100);
    
    // Cleanup phase
    stbi_image_free(img->imgDataLinear);
    return true;
}

// Entry point of the program
int main(int argc, char* argv[]) {
        
    // Data setup
    ProcessManager processManager;

    string userInput = "";
    vector<string> filepaths;

    // Debugging data
    unsigned int badReads = 0;  // Track how many files failed to load
    vector<string> badFiles;


    if (argc == 1) {
        // No arguments passed
        // Get the directory or image to
        cout << "Enter a list of files/directories to process\nSeparate entries with a space, Include the extension\n";
        while (userInput.size() == 0) {
            getline(cin, userInput, '\n');
        }
    } else {
        // Arguments passed and need to be processed #TODO (Waffles_54)
        for (int i = 1; i < argc; i++) {
            userInput += argv[i] + ' ';
        }
        userInput.back() = '\0';
    }

    // Tokenize input
    string token;
    stringstream userStream(userInput);
    while (getline(userStream, token, ' ')) {
        if (fs::is_directory(token)) {
            for (const auto& entry : fs::directory_iterator(token)) {
                filepaths.push_back(entry.path().string());
            }
        } else {
            filepaths.push_back(token);
        }
    }
    
    // Pass control to the processManager
    processManager.initiateThreads(filepaths);
    return 0;
}