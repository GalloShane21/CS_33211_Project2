#include <fstream>
#include "utils.hpp"

// Reads in resource and process values from input.txt and stores in the appropriate matrix/arrays
void inputFileRead(char *inputFile, int alloc[][RESCOURCES], int max[][RESCOURCES], int available[]) {
    // Open the input file and error out if unable to open
    std::ifstream inFile(inputFile);
    if(!inFile) {
        std::cerr << "Error opening " << inputFile << "exiting program now" << std::endl;
        exit(1);
    }

    //Read in values from input file and populate allocation matrix
    for(int i = 0; i < PROCESSES; ++i) {
        for(int j = 0; j < RESCOURCES; ++j) {
            inFile >> alloc[i][j];
        }
    }

    //Read in values for and populate max matrix
    for(int i = 0; i < PROCESSES; ++i) {
        for(int j = 0; j < RESCOURCES; ++j) {
            inFile >> max[i][j];
        }
    }

    //read in values for and populate available array
    for(int j = 0; j < RESCOURCES; ++j) {
        inFile >> available[j];
    }

    // Close input file
    inFile.close();
}

// Prints the matrix's and array's. Used for debug purposes
void printMatrix(int alloc[][RESCOURCES], int max[][RESCOURCES], int available[], int need[][RESCOURCES]) {
    // Print the allocation matrix
    std::cout << "Alloc:" << std::endl;
    for(int i = 0; i < PROCESSES; ++i) {
        for(int j = 0; j < RESCOURCES; ++j) {
            std::cout << alloc[i][j] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Print the max matrix
    std::cout << "Max:" << std::endl;
    for(int i = 0; i < PROCESSES; ++i) {
        for(int j = 0; j < RESCOURCES; ++j) {
            std::cout << max[i][j] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Print the max matrix
    std::cout << "Need:" << std::endl;
    for(int i = 0; i < PROCESSES; ++i) {
        for(int j = 0; j < RESCOURCES; ++j) {
            std::cout << need[i][j] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Print the available matrix
    std::cout << "Available:" << std::endl;
    for(int j = 0; j < RESCOURCES; ++j){
        std::cout << available[j] << ", ";
    }
    std::cout << std::endl;
}

// Calculates need which is Max - allocation
void calculateNeed(int max[][RESCOURCES], int alloc[][RESCOURCES], int need[][RESCOURCES]) {
    // Loop through each matrix index and subtract max - allocation and store in need
    for(int i = 0; i < PROCESSES; ++i) {
        for(int j = 0; j < RESCOURCES; ++j) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

//Check the sequence to see if system is in a safe state
bool isSafe(int alloc[][RESCOURCES], int need[][RESCOURCES], int available[]) {
    int dynAvail[RESCOURCES]; // dynAvail array to dynamically track available resources
    bool procComplete[PROCESSES] = {false}; // process complete array to track when processes are finished
    int safeSequence[PROCESSES]; // Stores the safe sequence

    // Initialize dynAvail with available resources 
    for(int i = 0; i < RESCOURCES; ++i){
        dynAvail[i] = available[i];
    }

    int count = 0;
    while(count < PROCESSES) {
        bool found = false;
        for(int i = 0; i < PROCESSES; ++i) {
            if(!procComplete[i]) {
                bool canAllocate = true;
                // Check if resources needed can be allocated
                for(int j = 0; j < RESCOURCES; ++j) {
                    //if unable to allocate then break out and move to next process
                    if(need[i][j] > dynAvail[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                // If resources can be allocated
                if (canAllocate) {
                    for(int j = 0; j < RESCOURCES; ++j) {
                        // process complete so free resources
                        dynAvail[j] += alloc[i][j];
                    }
                    safeSequence[count++] = i; //add process to safe sequence
                    procComplete[i] = true; // mark process as complete
                    found = true; 
                }
            }
        }
        // If an available process can't be found then print unsafe and return
        if(!found) {
            std::cout << "System is not safe!" << std::endl;
            return false;
        }
    }
    // When all process can be allocated print safe, print safe sequence, and return true
    std::cout << "System is in a safe state!" << std::endl << "The safe sequence is: ";
    for(int i = 0; i < PROCESSES; ++i) {
        std::cout << "P" << safeSequence[i];
        if (i != PROCESSES - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
    return true;
}