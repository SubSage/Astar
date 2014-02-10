#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <string>
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
		
		Vertex(){
			g=0;
			h=0;
			f=0;
			locationName="";
		
		}
		Vertex(string name, double h2)
		{
			locationName = name;
			h = h2;
		}

		bool operator<(const Vertex & b){
			return h > b.h;
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

    Vertex * findVertex(string name)
    {
		for each(Vertex * v in vertexList)
		{
			if (v->locationName == name)
				return v;
		}
	return NULL;
    }
    
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