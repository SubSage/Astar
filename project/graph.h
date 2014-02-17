#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
/*
Now this just wasn't fair! Luis (I) hadn't been formally introduced into graphs, and I pretty much recreated what a graph is
along with how it works and then Adan showed me some code he had from previous doings. Modified/revised by the both of us 
to fit the current project.

*/
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

		bool operator<(const Vertex & b)
		{
			return (h > b.h);
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

		// Get Value of roads considering distance, quality, riskiness to a naive effect
		double getRoadValue(Vertex* destination)
		{
			for(list<Edge*>::iterator it = adjList.begin(); it != adjList.end(); it++)
			{
				if ( (*it)->end == destination )
					return (*it)->distance / 10 * (*it)->roadQuality * (*it)->riskLevel * (*it)->riskLevel;
				// Distance itself not too much a factor, quality is standard, risk is very important.
			}
			return -1; // Distance never found
		}

		// DEBUG PRINT EDGES
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

			// DEBUG PRINT EDGE
			//cout << "Start Loc: \'" << start->locationName << "\' Path Dest: \'" << end->locationName << "\' Dist: " << distance2
			//	 << " RQual: " << roadQuality << " RiskLvl: " << riskLevel << endl;
		}

		// NOT USED FOR NOW
		/*
		Vertex* getEnd(string a)
		{
		if(a == start->locationName)
		{
		return end;
		} 
		else if (a == end->locationName)
		return start;
		return NULL;
		}
		*/


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
