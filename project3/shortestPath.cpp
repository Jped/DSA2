#include <ctime>
#include <climits>
#include <stdio.h>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include "heap.h"

struct edge {
	std::string vertexName;
	int cost;
};

struct vertex {
	std::string vertexName;
	int distance;
	bool known = false;
	vertex * previous = NULL;
	std::list<edge> adjEdges;
};

struct adjList {
	std::vector<vertex> vertexList;
	hashTable * map = NULL;
	heap *	vertices;
	int numVertices=0;
};




adjList loadGraph(adjList graph, std::ifstream &graphFile) {
	// open the file iterate line by line
	std::string line;
	int currentIndex = 0;
	while (std::getline(graphFile, line)) {
		//split the line get the starting vertex
		int firstSpacePos = line.find(" ");
		int secondSpacePos = line.find(" ", firstSpacePos + 1);
		std::string startingVertex = line.substr(0, firstSpacePos);
		std::string destinationVertex = line.substr(firstSpacePos + 1, secondSpacePos - firstSpacePos - 1);
		// insert both into heap (disregard if already in the heap)
		graph.vertices -> insert(startingVertex, INT_MAX);
		graph.vertices -> insert(destinationVertex, INT_MAX);
		edge e;
		e.vertexName = destinationVertex;
		e.cost = std::stoi(line.substr(secondSpacePos + 1, line.length() - secondSpacePos - 1));
		// now we check if this exsists, if it does we add to the list otherwise we add a new entry
		int * index;
		if(graph.map->contains(startingVertex)) {
			index = (int *) graph.map->getPointer(startingVertex);
		       	graph.vertexList[*index].adjEdges.push_back(e);	
		}else{
			// insert with pv being the index we are adding it to
			index = (int *) malloc(sizeof (int));
			*index = currentIndex;
			if(graph.map->insert(startingVertex, index) != 0)
				perror("hash insert failed");
			vertex v;
			v.vertexName = startingVertex;
			v.distance = INT_MAX;
			v.previous = NULL;
			v.adjEdges.push_back(e);
			graph.vertexList[currentIndex] = v;
			currentIndex++;
			graph.numVertices++;
		}
		if(!graph.map->contains(destinationVertex)){
			index = (int *) malloc(sizeof (int));
			*index = currentIndex;
			if(graph.map->insert(destinationVertex, index) != 0)
				perror("hash insert failed");

			vertex v;
			v.vertexName = destinationVertex;
			v.distance = INT_MAX;
			v.previous = NULL;
			graph.vertexList[currentIndex] = v;
			currentIndex++;
			graph.numVertices++;
		}
		
	}
	return graph;

}


void printAdjList(adjList graph) {
	for (int i=0; i<graph.numVertices; i++){
			std::cout << "Vertex " << graph.vertexList[i].vertexName << " at location " << i << '\t';
			for(auto const& i: graph.vertexList[i].adjEdges){
				std::cout << " -> " << i.vertexName << " " << i.cost;
			}	
		std::cout << "\n";
	}
}

	
adjList performDijkstra(adjList graph, std::string startingVertex) {
	std::string * currVertexName = new std::string;
	int * distance = new int;
	int destinationIndex, newDistance, index;
	graph.vertices -> setKey(startingVertex, 0);
	index =  * ((int *) graph.map->getPointer(startingVertex));
	graph.vertexList[index].distance = 0;
	graph.vertexList[index].known = true;
	while(graph.vertices->deleteMin(currVertexName,distance) == 0){
		// iterate through all of its children update their distances
		// both in the heap and in the main vertexList (also change prev) 	
		index =  * ((int *) graph.map->getPointer(*currVertexName));
		graph.vertexList[index].known = true;
		for(auto const& edge: graph.vertexList[index].adjEdges){
			//account for overflow
			if(*distance == INT_MAX)
				newDistance = INT_MAX;
			else
				newDistance = *distance + edge.cost;
			// get index for destination vertex
			destinationIndex = * ((int *) graph.map->getPointer(edge.vertexName)); 
			if (!graph.vertexList[destinationIndex].known && newDistance < graph.vertexList[destinationIndex].distance){
				graph.vertices -> setKey(edge.vertexName, newDistance);
				graph.vertexList[destinationIndex].distance = newDistance;
				graph.vertexList[destinationIndex].previous = &graph.vertexList[index];
			}
		}
	}	
	return graph;
}

void printShortestPath(adjList graph, std::string startingVertex, std::string outFileName) {
	std::ofstream outFile;
	outFile.open(outFileName);	
	for(int i=0; i<graph.numVertices; i++){
		std::string path = "";
		vertex * pv = graph.vertexList[i].previous;
		// do this check to prevent infinite loop with setting pv to itself
		if (graph.vertexList[i].vertexName == startingVertex) {
			outFile << startingVertex + ": 0 [" + startingVertex  + "]\n";
			continue;
		}else if (pv == NULL) {
			outFile << graph.vertexList[i].vertexName + ": NO PATH\n";
			continue;	
		}
		while (pv != NULL){
			path = pv->vertexName +", " + path;
			pv = pv->previous;	
		}
		outFile << graph.vertexList[i].vertexName <<  ": " << graph.vertexList[i].distance  << " [" << path << graph.vertexList[i].vertexName << "]\n";
	}	
	outFile.close();
}

int main () { 
	// prompt the user for information
	std::string fileName,  outFileName;
	std::cout << "Enter name of graph file: ";
	std::cin >> fileName;
	//get lines
	std::ifstream graphFile(fileName);
	std::string line;
	int capacity = 0; 
	while(getline(graphFile,line))
		capacity++;
	capacity *=2;
	graphFile.clear();
	graphFile.seekg(0, std::ios::beg);
	adjList graph;
	hashTable mapping(capacity);
      	graph.map = &mapping;	
	heap vertices(capacity);
	graph.vertices = &vertices;
	graph.vertexList.resize(capacity);
	graph = loadGraph(graph, graphFile);
	std::string startingVertex;
	int index;
	do{
		std::cout << "Enter valid starting vertex: ";
		std::cin >> startingVertex;
	}while(!graph.map->contains(startingVertex));
	clock_t t1 = clock();
	graph = performDijkstra(graph, startingVertex);
	clock_t t2 = clock();
	double time = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
	std::cout << "Total time (in seconds) to apply Dijkstra's: " << time <<"\n"; 
	std::cout << "Enter name of output file: ";
	std::cin >> outFileName;
	printShortestPath(graph, startingVertex, outFileName);
	return 0;
}
