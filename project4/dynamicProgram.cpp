#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>


std::vector<std::vector<int>> dynamicHelperFunction(std::vector<std::vector<int>> dpMatrix, std::string string1, std::string string2, std::string mergedString) { 
	if (mergedString.length() == 0 || (mergedString.back() != string1.back() && mergedString.back()!= string2.back())) {
		// can't proceed from here.
		return dpMatrix;
	}
	int string1Length = string1.length()-1;
	int string2Length = string2.length()-1;
	//std::cout << "STRING 1 " << string1 << " STRING 2 " << string2 << " MERGEDSTRING " << mergedString << "\n"; 
	// check to call the dynamicHelper again
	if (string1Length != 0 && mergedString.back() == string1.back() && dpMatrix[string1Length-1][string2Length] != 1){
		//std::cout << " match 1 \n ";
		dpMatrix[string1Length-1][string2Length] = 1;
		dpMatrix = dynamicHelperFunction(dpMatrix, string1.substr(0,string1Length), string2, mergedString.substr(0, mergedString.length()-1));
	}
	if (string2Length !=0 && mergedString.back() == string2.back() && dpMatrix[string1Length][string2Length-1] != 1){
		//std::cout << " match 2 \n";
		dpMatrix[string1Length][string2Length-1] = 1;
		dpMatrix = dynamicHelperFunction(dpMatrix,string1, string2.substr(0,string2Length), mergedString.substr(0, mergedString.length()-1));
	}
	return dpMatrix;
} 

std::string printSolution(std::vector<std::vector<int>> dpMatrix, std::string string1, std::string string2){}


void isInterpolation(std::string string1, std::string string2, std::string mergedString, std::string outFileName) {
	// initialize 2d array	
	std::vector<std::vector<int>> dpMatrix;
	dpMatrix.resize(string1.length());
	for (int i=0; i<string1.length(); i++)
		dpMatrix[i].resize(string2.length());
	// call dynamicHelper function
	dpMatrix = dynamicHelperFunction(dpMatrix, string1, string2, mergedString);
	// check 0,0 position
	std::ofstream outputFile(outFileName);
	for (int i=0; i<string1.length(); i++){
		std::cout << "----------------------------------\n";
		std::cout << "| ";
		for(int j=0; j<string2.length(); j++) {
			std::cout << dpMatrix[i][j] << " | ";
		}
		std::cout <<"\n";
	}
	if (dpMatrix[0][0] == 1)
		outputFile << printSolution(dpMatrix, string1, string2);
	else
		std::cout << "*** NOT A MERGE ***\n";
	outputFile.close();
}

int main() { 
	std::string fileName,  outFileName;
	std::cout << "Enter name of input file: ";
	std::cin >> fileName;
	std::cout << "Enter name of output file: ";
	std::cin >> outFileName;
	std::ifstream inputFile(fileName);
	std::string string1, string2, mergedString;
	while(std::getline(inputFile, string1) 
		&&  std::getline(inputFile,string2)
		&&  std::getline(inputFile,mergedString))
		isInterpolation(string1, string2, mergedString, outFileName);
	inputFile.close();
} 
