#ifndef BANKERSUTILS_HPP
#define BANKERSUTILS_HPP

#include <iostream>
#include <fstream>
#include <map>

const int RESCOURCES = 3;
const int PROCESSES = 5;

// Reads in resource and process values from input.txt and stores in the appropriate matrix/arrays
void inputFileRead(char *inputFile, int alloc[][RESCOURCES], int max[][RESCOURCES], int available[]);

// Prints the matrixs' and arrays'. Used for debug purposes
void printMatrix(int alloc[][RESCOURCES], int max[][RESCOURCES], int available[], int need[][RESCOURCES]);

// Calculates need which is Max - allocation
void calculateNeed(int max[][RESCOURCES], int alloc[][RESCOURCES], int need[][RESCOURCES]);

//Check the sequence to see if system is in a safe state
bool isSafe(int alloc[][RESCOURCES], int need[][RESCOURCES], int available[]);

#endif