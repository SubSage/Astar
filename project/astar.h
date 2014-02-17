#include <iostream>
#include <string>
#include <cstdio>
#include <queue>
#include <set>
#include "graph.h"
using namespace std;
/*
Layout/structure and code of this file was made by Luis Martinez, modified/revised by Adan.
G++ is weird :D

*/
class astar
{
public:
	astar()
	{

	}

	//Returns vertex with smallest F in a set
	weightedGraph::Vertex* getSmallestFScoreVertex(set<weightedGraph::Vertex*> s)
	{
		weightedGraph::Vertex* smallestF = NULL;

		for (set<weightedGraph::Vertex*>::iterator it = s.begin(); it != s.end(); it++) 
		{
			// Initialize smallestF with first Vertex in set
			if (smallestF == NULL)  
				smallestF = *it;
			// If current Vertex's Fscore is smaller than smallestF's Fscore
			if( (*it)->f < smallestF->f ) 
				smallestF = *it;
		}
		return smallestF;
	}

	vector<weightedGraph::Vertex*> findPath(weightedGraph& graph, string start, string end)
	{
		set<weightedGraph::Vertex*> closedSet;
		set<weightedGraph::Vertex*> openSet;
		vector<weightedGraph::Vertex*> path;
		weightedGraph::Vertex* current;

		weightedGraph::Vertex* startVertex = graph.findVertex(start);

		openSet.insert( startVertex );

		// Cost from start along best known path
		startVertex->g = 0;  

		// Estimated total cost from start to goal
		startVertex->f = startVertex->g + startVertex->h;


		while(!openSet.empty())
		{
			// print openSet
			cout << "Openset: ";
			for ( set<weightedGraph::Vertex*>::iterator it = openSet.begin(); it != openSet.end(); it++)
			{
				cout << (*it)->locationName << " ";
			}
			cout << endl;

			current = getSmallestFScoreVertex(openSet);

			// If current vertex is the goal
			if(current->locationName == end)
			{
				path = finishUp(current);
				cout << "Path found!" << endl;
				return path;
			}
			else
			{
				// Remove current from open set
				openSet.erase(current);

				// Add current to closed set
				closedSet.insert(current);

				// Get neighbors vertexes of current vertex
				vector<weightedGraph::Vertex*> neighbors = current->getNeighbors();

				// For each adjacent neighbor of current
				for (vector<weightedGraph::Vertex*>::iterator neighbor = neighbors.begin(); neighbor != neighbors.end(); neighbor++)
				{
					// If neighbor is in closed set
					if (!closedSet.count(*neighbor) == 0)
						continue;

					// Current g-score + dist_between(current, neighbor)
					double tentativeG = current->g + current->getRoadValue(*neighbor);

					if(openSet.count(*neighbor) == 0 || tentativeG < (*neighbor)->g)
					{
						(*neighbor)->parent = current;
						(*neighbor)->g = tentativeG;
						(*neighbor)->f = (*neighbor)->g + (*neighbor)->h;

						// If neighbor not in open set
						if(openSet.count(*neighbor) == 0)
						{
							openSet.insert(*neighbor);
						}
					}
				}
			}
		}
		cout << "no path" << endl;
		return path;
	}

	//Returns linked path of Vertex's pointing towards their origins from goal to root
	vector<weightedGraph::Vertex*> finishUp(weightedGraph::Vertex* s)
	{
		vector<weightedGraph::Vertex*> pp;
		while( s->parent != NULL)
		{
			pp.push_back(s);
			s=s->parent;
		}
		pp.push_back(s);
		return pp;
	}
};
