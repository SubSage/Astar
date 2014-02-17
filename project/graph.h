/*******************************************************
 *                                                     *
 *  Name:       Adan Rodriguez, Luis Martinez          *
 *  Class:      CSCI 4350 - Artificial Intelligence    *
 *  Assignment: Program 1 - A* Search                  *
 *                                                     *
 *  Program Summary: Create graph from input files and *
 *  calculate a best path depending on step number     *
 *  specified to solve of A* assignment. Prints out    *
 *  final path if found.                               *
 *                                                     *
 ******************************************************/

/*******************************************************
 *                                                     * 
 *  Contributions:                                     *
 *  Now this just wasn't fair! Luis (I) hadn't been    *
 *  formally introduced into graphs, and I pretty much *
 *  recreated what a graph is along with how it works  *
 *  and then Adan showed me some code he had from      *
 *  previous doings.                                   *
 *                                                     *
 *  Modified/revised by the both of                    *
 *  us to fit the current project.                     *
 *                                                     *
 *******************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class weightedGraph
{
public:
    class Vertex;
    class Edge;
    
    class Vertex
    {
    public:
	string locationName;
	double g;
	double h;
	double f;
	Vertex* parent;
	list<Edge*> adjList;
	
	Vertex()
	{
	    g = 0;
	    h = 0;
	    f = 0;
	    locationName = "";
	    parent = NULL;
	}
	Vertex(string name, double h2)
	{
	    locationName = name;
	    h = h2;
	}
		
	//Returns neighboring nodes of the vertex
	vector<Vertex*> getNeighbors()
	{
	    vector<Vertex*> p;
	    for ( list<Edge*>::iterator it = adjList.begin(); it != adjList.end(); it++ )
	    {
		if(locationName == (*it)->start->locationName)
		{
		    p.push_back( (*it)->end );
		} 
		if (locationName == (*it)->end->locationName)
		    p.push_back( (*it)->start );
		
	    }
	    return p;
	}
	
	// Get value of roads using calculations from step 1 or from step 2 of problem.
	// Step 1: Distance
	// Step 2: Distance, Quality, Risk Level to a naive effect
	double getRoadValue(Vertex* destination, int stepNumber)
	{
	    for(list<Edge*>::iterator it = adjList.begin(); it != adjList.end(); it++)
	    {
		if ( (*it)->end == destination )
		{
		    // Distance only
		    if (stepNumber == 1)
			return (*it)->distance;

		    // Distance itself not too much a factor, quality is standard, risk is very important.
		    // (Distance / 10) * (roadQuality) * (riskLevel)^2
		    else if (stepNumber == 2)
			return ( (*it)->distance / 10 ) * (*it)->roadQuality * (*it)->riskLevel * (*it)->riskLevel;
		}
	    }
	    return -1; // Distance never found
	}
	
	// DEBUG: Print edges
	void printVectorEdges()
	{
	    for(list<Edge*>::iterator it = adjList.begin(); it != adjList.end(); it++)
	    {
		cout << "Start: \'" << (*it)->start->locationName << "\' End: \'" << (*it)->end->locationName << "\' Dist: " << (*it)->distance
		     << " RQual: " << (*it)->roadQuality << " RiskLvl: " << (*it)->riskLevel << endl;
	    }
	}
    };
    
    class Edge
    {
    public:
	Vertex* start;
	Vertex* end;
	double distance;
	double roadQuality;
	double riskLevel;
	
	Edge(Vertex* u, Vertex* v, double distance2, double roadQuality2, double riskLevel2)
	{
	    start = u;
	    end = v;
	    distance = distance2;
	    roadQuality = roadQuality2;
	    riskLevel = riskLevel2;	
	}
    };
    
    list<Vertex*> vertexList;
    
    // DEBUG: Print Vertexes and their adjacent edges
    void printVertexesAndAdjEdges()
    {
	for (list<Vertex*>::iterator it = vertexList.begin(); it != vertexList.end(); it++)
	{
	    cout << "Location Name: \'" << (*it)->locationName << "\'"<< endl;
	    (*it)->printVectorEdges();
	    cout << endl;
	}
    }
    
    // Find Vertex in vertex list
    Vertex * findVertex(string name)
    {
	for (list<Vertex*>::iterator it = vertexList.begin(); it != vertexList.end(); it++ )
	{
	    if ( (*it)->locationName == name)
		return (*it);
	}
	return NULL;
    }
    
    weightedGraph()
    {
    }
    
    // Create a Vertex and add to vertex list
    void addVertex(string name, double h)
    {
	vertexList.push_back( new Vertex(name, h) );
    }
    
    // Add an bidirectional edge between two Vertexes
    void addEdge(string a, string b, double distance, double roadQuality, double riskLevel)
    {
	Vertex* vertA = findVertex(a);
	Vertex* vertB = findVertex(b);
	
	// Create edge
	Edge* path = new Edge(vertA, vertB, distance, roadQuality, riskLevel);
	
	// Add bidirectional edge between the vertA and vertB
	vertA->adjList.push_back(path);
	vertB->adjList.push_back(path);	
    }  
};

#endif
