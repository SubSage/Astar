#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "graph.h"
#include "astar.h"
using namespace std;
//Adan's work, Luis gave input on some of it for structure's sake

void parseInput(ifstream& inputFile, string action, weightedGraph& graph);
void buildNode(string name, double distance, weightedGraph& graph);
void buildEdge(string loc1, string loc2, double dist, double roadQlty, double riskLvl, weightedGraph& graph);

int main()
{
	//Getting instructions from system/user, build nodes or edges?
	ifstream inputFile;
	string inputOption;

	weightedGraph graph;
	vector<weightedGraph::Vertex*> path;

	inputOption = "buildNodes";
	parseInput(inputFile, inputOption, graph);

	inputOption = "buildEdges";
	parseInput(inputFile, inputOption, graph);

	// Performing A* Pathfinding
	astar algo;
	path = algo.findPath(graph, "Blue Mountains", "Iron Hills");

	// Printing out results of A*, possibility of no path if screen has "no path"

	cout << "=== Path ===" << endl;
	for (vector<weightedGraph::Vertex*>::reverse_iterator it = path.rbegin(); it != path.rend(); it++)
	{
		cout << (*it)->locationName;
		if ( !((*it)->locationName == "Iron Hills") )
			cout << " -> ";
		else
			cout << endl;
	}

	return 0;
}

void parseInput(ifstream& inputFile, string dataAction, weightedGraph& graph)
{
	string data;

	// Loads Table 1 file to build nodes with data
	if (dataAction == "buildNodes")
	{
		string name;
		double value;
		vector<string> lineParts;
		string constructedLine;

		inputFile.open("dist_to_iron_hills.txt");

		while ( getline(inputFile, data) )
		{
			constructedLine = "";
			for (int i = 0; i < data.size(); i++)
			{
				if (data[i] != '-')
					constructedLine += data[i];
				else
				{
					if (constructedLine != "")
					{
						lineParts.push_back(constructedLine);
						constructedLine = "";
					}
				}
			}
			// Adds distance value from Table 1
			lineParts.push_back(constructedLine); 

			name = lineParts[0];
			value = atof(lineParts[1].c_str());

			// Build nodes here
			buildNode(name, value, graph);

			lineParts.clear();
		}		
	}

	// Loads Table 2 file with point to point information (Edges) and build edges.
	// between the created Nodes
	if (dataAction == "buildEdges")
	{
		string locationOneName;
		string locationTwoName;
		double pathDistance;
		double pathRoadQuality;
		double pathRiskLevel;
		vector<string> lineParts;
		string constructedLine;

		inputFile.open("point_to_point.txt");

		while ( getline(inputFile, data) )
		{	    
			lineParts.clear();

			// See if line contains a : to extract start node name, otherwise check next condition
			if ( data.find(':') != string::npos )
			{
				int pos;  // Store position of colon

				locationOneName = "";
				constructedLine = "";

				// Subtract 1 from data.size() to exclude colon
				for (int i = 0; i < data.size() - 1; i++)
				{
					// Get name
					constructedLine += data[i];
				}

				// Add word to locationOneName
				locationOneName = constructedLine;
			}	
			// See if line contains a - to see if it's a node path
			else if ( data.find('-') != string::npos )
			{
				lineParts.clear();
				constructedLine = "";

				for (int i = 0; i < data.size(); i++)
				{
					if (data[i] != '-')
					{
						constructedLine += data[i];
					}
					else if (constructedLine != "")
					{
						// Push in constructed substrings that are not '-' in lineParts
						lineParts.push_back(constructedLine);
						constructedLine = "";
					}
				}
				// Push in last substring since no '-' exists after Risk Level value
				lineParts.push_back(constructedLine);

				locationTwoName = lineParts[0];
				pathDistance = atof(lineParts[1].c_str());
				pathRoadQuality = atof(lineParts[2].c_str());
				pathRiskLevel = atof(lineParts[3].c_str());

				// Build edge
				buildEdge(locationOneName, locationTwoName, pathDistance, pathRoadQuality, pathRiskLevel, graph);
			}

			// Line is blank
			else
			{
				continue;		
			}
		}
	}      

	inputFile.close();
}

void buildNode(string name, double distance, weightedGraph& graph)
{
	graph.addVertex(name, distance);
}

void buildEdge(string location1, string location2, double distance, double roadQuality, double riskLevel, weightedGraph& graph)
{
	graph.addEdge(location1, location2, distance, roadQuality, riskLevel);
}
