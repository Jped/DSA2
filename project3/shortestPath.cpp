#include <string>
#include <stdio.h>
#include <list>
#include <vector>
#include <iostream>

struct vertex {
	std::string vertexName;
	unsigned int cost;
};

struct adjList {
	std::vector<std::list<vertex>> vertexList;
};

adjList loadAdjacencyList(string fileName) {
	adjList graph;
	// open the file iterate line by line
	std::ifsteam graphFile(fileName);
	std::string line;
	int currentIndex = 0;
	while (std::getline(graphFile, line)) {
		//split the line get the starting vertex
		int firstSpacePos = line.find(" ")
		int secondSpacePos = line.find(" ", firstSpacePos + 1);
		std::string startingVertex = line.substr(0, firstSpacePos);
		std::string destinationVertex = line.substr(firstSpacePos + 1, secondSpacePos - firstSpacePos - 1);
		unsigned int cost = std::stoi(line.substr(secondSpacePos + 1, line.length() - secondSpacePos - 1));	
		std::cout << " we have read in source : " << startingVertex << " destination vertex : " << destinationVertex << " cost " << cost << std::endl;
		vertex v;
		v.vertexName = destinationVertex;
		v.cost = cost;
		// now we check if this exsists, if it does we add to the list otherwise we add a new entry
		if(graph.map.contains(startingVertex)) {
			int * index = graph.map.getPointer(startingVertex);
		       	adjList.vertexList[*index].push_back(v)	
		}else{
			// insert with pv being the index we are adding it to
			int * index = malloc(sizeof int);
			*index = currentIndex;
			if(graph.map.insert(startingVertex, index) != 0)
				perror("hash insert failed");
			adjList.vertexList[currentIndex].push_back(v);
			currentIndex++;
		}	
	}
	return graph;

}

int main () { 
	// prompt the user for information
	std::string fileName;
	std::cout << "Enter name of graph file: ";
	std::cin >> fileName;
	//struct adjList graph;
	//graph = loadAdjacencyList(fileName);
	//return 0;
}
