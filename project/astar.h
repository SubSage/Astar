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
    weightedGraph::Vertex* getSmallestFScoreVertex(set<weightedGraph::Vertex*> s){
	weightedGraph::Vertex* x;
	for (set<weightedGraph::Vertex*>::iterator i = s.begin(); i != s.end(); i++) {
	    if( (*i)->f < x->f )
		x = *i;
	}
	return x;
    }

    vector<weightedGraph::Vertex*> findPath(weightedGraph& graph, string start, string end)
    {
	set<weightedGraph::Vertex*> closedSet;
	set<weightedGraph::Vertex*> openSet;
	openSet.insert(graph.findVertex(start));

	// DEBUG
	cout << "IN FINDPATH FUNCTION" << endl;

	while(!openSet.empty()){
			
	    weightedGraph::Vertex* current;
	    current = getSmallestFScoreVertex(openSet);

	    if(current->locationName == end)
		return finishUp(current);

	    openSet.erase(current);
	    closedSet.insert(current);
	    
	    // DEBUG
	    cout << "NOW HERE" << endl;

	    vector<weightedGraph::Vertex*> neighbors = current->getNeighbors();
			
	    for (vector<weightedGraph::Vertex*>::iterator it = neighbors.begin(); it != neighbors.end(); it++){
		    if(closedSet.count(*it) != 0)
		    {
			continue;
		    }
		    double temp = current->g + (*it)->h;

		    if(openSet.count(*it)==0 || temp < (*it)->g)
		    {
			(*it)->parent = current;
			(*it)->g = temp;
			(*it)->f = (*it)->h + (*it)->g;

			if(openSet.count(*it) == 0)
			{
			    openSet.insert(*it);
			}
		    }
		}
	    cout << "no path" << endl;
	    //return NULL;
	}
    }

    //Given a vertex with each parent pointing up, returns vector with full path from start to goal
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
	//Rant....c++ seems dumb sometimes, why wasn't I able to insert s to p? I just don't get it...maybe I do.
	//Seems like they leave things like that for programmers to be efficient. Such as there being no contains method
	//because then one would invoke get method thus being O(2n) when they could just get it in O(n) with find method/function -Luis
    }
};
