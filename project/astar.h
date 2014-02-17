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
 *  Layout/structure and code of this file was made    *
 *  by Luis Martinez, modified/revised by Adan.        *
 *                                                     *
 *******************************************************/
#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <string>
#include <cstdio>
#include <queue>
#include <set>
#include "graph.h"
using namespace std;

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
    
    // Calculate and return vector of Vertices containing final path depending on step of problem performed
    vector<weightedGraph::Vertex*> findPath(weightedGraph& graph, string start, string end, int stepNumber)
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
	    current = getSmallestFScoreVertex(openSet);
	    
	    // If current vertex is the goal
	    if(current->locationName == end)
	    {
		path = finishUp(current);
		cout << "\nPath found!" << endl;
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
		    
		    // Current g-score + dist_between(current, neighbor) with step number to solve of A* Problem
		    double tentativeG = current->g + current->getRoadValue(*neighbor, stepNumber);
		    
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
	cout << "\nNo path found..." << endl;
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
#endif
