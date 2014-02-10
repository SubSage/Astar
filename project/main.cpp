#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <graph.h>

using namespace std;

void parseInput(ifstream& inputFile, string action);
void buildNode(string name, double distance);

int main()
{
    ifstream inputFile;
    string dataAction;  // Determines what is done with the data
    
    weightedGraph graph;
    
    dataAction = "buildNodes";  // Input used to build Nodes
    parseInput(inputFile, dataAction, graph);
    dataAction = "buildEdges";  // Input used to build Edges
    parseInput(inputFile, dataAction, graph);
    
    return 0;
}

void parseInput(ifstream& inputFile, string dataAction, weightedGraph& graph)
{
    string data;
    string name;
    double value;
    vector<string> lineParts;
    string constructedLine;
    
    // Loads Table 1 file to build nodes with data
    if (dataAction == "buildNodes")
    {
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
	}	
	
	
    }

    // Loads Table 2 file with point to point information (Edges) and build edges.
    // between the created Nodes
    if (dataAction == "buildEdges")
    {
	inputFile.open("point_to_point.txt");

	// ******* Parse code for build WORK IN PROGRESS *******
	while ( getline(inputFile, data) )
	{

            // See if line contains a : to extract start node name, otherwise check next condition
	    if ( data.find(':') != string::npos )
	    {
		constructedLine = "";
		for (int i = 0; i < data.size(); i++)
		{
		    // Get name, take away the colon
		    
		}

		// DEBUG
		cout << "Found :" << endl;
	    }	
	    // See if line contains a - to see if it's a node path
	    else if ( data.find('-') != string::npos )
	    {
		constructedLine = "";
		for (int i = 0; i < data.size(); i++)
		{
		    
		    
		}

		// DEBUG
		cout << "Found -" << endl;
	    }
	    
	    // Line is blank
	    else
	    {
		// DEBUG
		cout << "Found blank line" << endl;

		continue;		
	    }
	}
    }      
	
    // DEBUG
    cout << "Name: \"" << name << "\" Value: " << value << endl;
        
    lineParts.clear();
    inputFile.close();
}

void buildNode(string name, double distance, weightedGraph& graph)
{
    graph.addVertex(name, distance);
}
