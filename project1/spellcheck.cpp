#include <iostream>
#include <algorithm>
#include <ctime>
#include <fstream>
#include "hash.h"

using namespace std;


hashTable loadDictionary(hashTable dict, char * fileName) {
	string line;
	ifstream dictFile(fileName);
	if(dictFile.is_open()) {
		while(getline(dictFile, line)) {
			transform(line.begin(), line.end(), line.begin(), ::tolower);
			dict.insert(line);
		}
		dictFile.close();
	} else {
		cout << "Error opening dictioanry " << fileName << endl;;
	}
	return dict;
}

void checkFile(hashTable dict, char * inputFile, char * outputFile) {
	char wordBuffer[20];
	char c;
	char fileBuffer[4096];
	int numRead;
	int j=0;
	int line=1;
	bool response;
	// open each file
	FILE * inputF = fopen(inputFile, "r");
	FILE * outputF = fopen(outputFile, "w");
	// start moving through the input file
	while((numRead = fread(fileBuffer, 1, 4096, inputF)) > 0) {
		for (int i=0;i<numRead;i++){
			c = tolower(fileBuffer[i]);
			// check if it is valid
			// not valid dump the wordBuffer make sure sure it is correct	
			if(islower(c) || isdigit(c) || c == 45 || c == 39) {
				if(j<20)
					wordBuffer[j] = c;
				if(j == 20)
				       	fprintf(outputF, "Long word at line %d, starts: %s\n", line, wordBuffer);
				j++;
			} else {
				// check if the word is correct, if not print error
				// make it equal to 20 for 19 letter word that gets j++
				if(j>0 && j<=20) {
					response = dict.contains(wordBuffer);
					if(!response)
						fprintf(outputF, "Unknown word at line %d: %s\n", line, wordBuffer);
				}
				for(int i=0;i<=j;i++)
					wordBuffer[i]='\0';
				j=0;
				if(c == 10)
					line++;

			}

		}
	};

}

int main() {
       	char dictionaryFile[1024], inputFile[1024], outputFile[1024];	
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
	cout << "Total time (in seconds) to check document: " << time <<endl;;

}

