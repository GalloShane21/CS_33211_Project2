#include "utils.hpp"

int main(int argc, char* argv[]) {
    // Check for proper argument count (includes input file name)
    if(argc < 2) {
        std::cerr << "Error: execution requires file path for input file (ex: ./bankers input.txt)" << std::endl;
        exit(1);
    }

    // Initialize inputFile to users input file argument
    char* inputFile = argv[1];

    int available[RESCOURCES];  // Stores available array
    int max[PROCESSES][RESCOURCES]; // Stores max matrix
    int alloc[PROCESSES][RESCOURCES]; // Stores allocation matrix

    // Populate matrixs' and array from input file
    inputFileRead(inputFile, alloc, max, available);

    // Calculate the resource need of each process and store in need matrix
    int need [PROCESSES][RESCOURCES];
    calculateNeed(max, alloc, need);

    //Check the sequence to see if system is in a safe state
    isSafe(alloc, need, available);
    
}