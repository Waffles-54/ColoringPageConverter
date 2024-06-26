/*
  Filename: ProcessManager.cpp
  Author: Alice C. Griffith
  Date: 2024

  Description: Implentation of ProcessManager.h, Entry point of program, manages workload distribution
*/

#include <iostream>
#include "ProcessManager.h"

using namespace std;

void ProcessManager::entry() {
    cout << "Hello proccess manager\n";
}

int main() {
    // Your code here
    ProcessManager pm;
    pm.entry();
    return 0; // Optional, but conventionally used
}