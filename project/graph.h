#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <string>
using namespace std;

class weightedGraph
{

    class Vertex;
    class Edge;

    class Vertex
    {
    public:
	string locationName;
	double g;
	double h;
	double f;
	list<Edge*> adjList;

	Vertex(string name, double h)
	{
	    locationName = name;
	    this.h = h;
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

	Edge(Vertex* u, Vertex* v, double distance, double roadQuality, double riskLevel)
	{
	    start = u;
	    end = v;
	    this.distance = distance;
	    this.roadQuality = roadQuality;
	    this.riskLevel = riskLevel;
	}
    };

    list<Vertex*> vertexList;

    Vertex * findVertex(string name)
    {
	for each(Vertex * v in vertexList)
	{
	    if (v->locationName == name)
		return v;
	}
	return NULL;
    }
    
public:
    weightedGraph()
    {
	
    }

    void addVertex(string name, double h)
    {
	vertexList.push_back( new Vertex(name, h) );
    }

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
