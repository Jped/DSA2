#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>


int dynamicHelperFunction(std::vector<std::vector<int>> * dpMatrix, std::string string1, std::string string2, std::string mergedString) { 
	if (mergedString.length() == 0 && string1.length() == 0 && string2.length() == 0) {
		// done
		return 1;
	} else if (mergedString.length() == 0 || (mergedString.back() != string1.back() && mergedString.back()!= string2.back())) {
		// can't proceed from here.
		return -1;
	}
	int string1Length = string1.length();
	int string2Length = string2.length();
	// check to call the dynamicHelper again
	if (string1Length != 0 && mergedString.back() == string1.back() && dpMatrix[string1Length-1][string2Length] != 1){
		dpMatrix[string1Length-1][string2Length] = 1;
		dpMatrix = dynamicHelperFunction(dpMatrix, string1.substr(0,string1Length-1), string2, mergedString.substr(0, mergedString.length()-1));
	}
	if (string2Length !=0 && mergedString.back() == string2.back() && dpMatrix[string1Length][string2Length-1] != 1){
		dpMatrix[string1Length][string2Length-1] = 1;
		dpMatrix = dynamicHelperFunction(dpMatrix,string1, string2.substr(0,string2Length-1), mergedString.substr(0, mergedString.length()-1));
	}
	return status;
} 

std::string printSolution(std::vector<std::vector<int>> dpMatrix, std::string string1, std::string string2){
	std::string solution;
	int i=0;
	int j=0;
	while(1){
		//always perfer to go down the rows
		if(i<string1.length() && dpMatrix[i+1][j]){
			solution.push_back(toupper(string1[i]));
			i++;
		}else if (j<string2.length() && dpMatrix[i][j+1]){
			solution.push_back(string2[j]);
			j++;
		}else{
			break;
		}
	}
	if (i < string1.length())
		solution.push_back(toupper(string1[i]));
	if (j < string2.length())
		solution.push_back(string2[j]);
	return solution;
}


void isInterpolation(std::string string1, std::string string2, std::string mergedString, std::string outFileName) {
	// initialize 2d array	
	std::vector<std::vector<int>> dpMatrix;
	dpMatrix.resize(string1.length() + 1);
	for (int i=0; i<=string1.length(); i++)
		dpMatrix[i].resize(string2.length()+1);
	// call dynamicHelper function
	if (string1.length() + string2.length() == mergedString.length())
		dpMatrix = dynamicHelperFunction(dpMatrix, string1, string2, mergedString);
	std::ofstream outputFile(outFileName, std::ofstream::out | std::ofstream::app);
	/*for (int i=0; i<=string1.length(); i++){
		std::cout << "----------------------------------\n";
		std::cout << "| ";
		for(int j=0; j<=string2.length(); j++) {
			std::cout << dpMatrix[i][j] << " | ";
		}
		std::cout <<"\n";
	}*/
	if (dpMatrix[0][0] == 1)
		outputFile << printSolution(dpMatrix, string1, string2) << "\n";
	else
		outputFile << "*** NOT A MERGE ***\n";
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
