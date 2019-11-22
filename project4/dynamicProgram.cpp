#include <fstream>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <string>
#include <vector>


void dynmaicHelperFunction() { 
} 

void isInterpolation(std::string, std::string, std::mergedString, std::ofstream outputFile) {
	// initialize 2d array	
	// call dynamicHelper function
	// check 0,0 position
	
}

int main() { 
	std::string fileName,  outFileName;
	std::cout << "Enter name of input file: ";
	std::cin >> fileName;
	std::cout << "Enter name of output file: ";
	std::cin >> outFileName;
	std::ifstream inputFile(fileName);
	std::string string1, string2, mergedString;
	std::ostream outputFile(outFileName);
	while(std::getline(inputFile, string1) 
		&&  std::getline(inputFile,string2)
		&&  std::getline(inputFile,mergedString))
	{
		isInterpolation(string1, string2, mergedString, outputFile);
		std::cout << "string 1 " << string1 <<" string 2 " <<string2 << " merge " << mergedString << "\n";
	}


} 
