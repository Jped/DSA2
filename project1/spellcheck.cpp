#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include "hash.h"
#include <string>

using namespace std;


hashTable loadDictionary(hashTable dict, string fileName) {
	string line;
	ifstream dictFile(fileName);
	if(dictFile.is_open()) {
		while(getline(dictFile, line)) {
			transform(line.begin(), line.end(), line.begin(), ::tolower);
			dict.insert(line);
		}
		dictFile.close();
	} else {
		cout << "Error opening dictionary file " << fileName << endl;;
	}
	return dict;
}

void checkFile(hashTable dict, string inputFile, string outputFile) {
	string wordBuffer;
	char c;
	char fileBuffer[4096];
	int numRead=0;
	int line=1;
	bool response, isDigit, isTwenty;
	ifstream inputF;
	ofstream outputF;
	inputF.open(inputFile);
	inputF.getline(fileBuffer, 4096);
	outputF.open(outputFile);
	// start moving through the input file
	while ((numRead = inputF.gcount()) > 0){
		for (int i=0; i<numRead; i++){
			c = tolower(fileBuffer[i]);
			// check if it is valid
			// not valid dump the wordBuffer make sure sure it is correct	
			if(islower(c) || isdigit(c) || c == 45 || c == 39) {
				wordBuffer += c;
				if(wordBuffer.size() == 21 && !isTwenty){
					isTwenty = true;
					outputF << "Long word at line " << line << ", starts: " <<  wordBuffer.substr(0,20) << endl;
				}if(isdigit(c))
					isDigit = true;
			} else {
				// check if the word is correct, if not print error
				if(wordBuffer.size() > 0 && !isTwenty && !isDigit) {
					response = dict.contains(wordBuffer);
					if(!response)
						outputF << "Unknown word at line " << line << ": " << wordBuffer <<endl;
				}
				wordBuffer.clear();	
				isDigit = false;
				isTwenty = false;

			}
		}
		line++;
		inputF.getline(fileBuffer, 4096);
	};
	inputF.close();
	outputF.close();	
}

int main() {
       	std::string dictionaryFile, inputFile, outputFile;
	hashTable dict;
	cout << "Enter name of dictionary: ";
	cin >> dictionaryFile;	
	// load in file here and print out time
	clock_t t1 = clock();
	dict = loadDictionary(dict, dictionaryFile);
	clock_t t2 = clock();
	double time = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to load dictionary: " << time <<endl;;
	cout << "Enter name of input file: ";
	cin >> inputFile;
	cout << "Enter output file: ";
	cin >> outputFile;
	// do check and print out total time;
	t1 = clock();
	checkFile(dict, inputFile, outputFile);
	t2 = clock();
	time = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to check document: " << time << endl;;
}

