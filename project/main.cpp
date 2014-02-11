#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "graph.h"
#include "astar.h"
using namespace std;

void parseInput(ifstream& inputFile, string action, weightedGraph& graph);
void buildNode(string name, double distance, weightedGraph& graph);
void buildEdge(string loc1, string loc2, double dist, double roadQlty, double riskLvl, weightedGraph& graph);

int main()
{
    ifstream inputFile;
    string d;  // Determines what is done with the data
    
    weightedGraph graph;
    
    d = "buildNodes";  // Input used to build Nodes
    parseInput(inputFile, d, graph);
    d = "buildEdges";  // Input used to build Edges
    parseInput(inputFile, d, graph);

    // Use Astar
    astar algo;
    algo.findPath(graph, "Blue Mountains", "Iron Hills");

    //system("pause");
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
	    lineParts.push_back(constructedLine); // Adds distance value from Table 1
	    
	    name = lineParts[0];
	    value = atof(lineParts[1].c_str());
	    
	    // Build nodes here
	    buildNode(name, value, graph);
	     // DEBUG
	    cout << "Name: \"" << name << "\" Value: " << value << endl;

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
	
	// ******* Parse code for build WORK IN PROGRESS *******
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
		
		// DEBUG
		cout << "Found " + constructedLine + ":" << endl;

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

		// DEBUG
		cout << "Start Loc: \'" << locationOneName << "\' Path Dest: \'" << locationTwoName << "\' Dist: " << pathDistance
		     << " RQual: " << pathRoadQuality << " RiskLvl: " << pathRiskLevel << endl;
	    }
	    
	    // Line is blank
	    else
	    {
		// DEBUG
		cout << endl;
		
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
