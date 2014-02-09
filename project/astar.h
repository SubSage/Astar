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
		graph;
	}

	vector<string> findPath(weightedGraph graph, string start, string end){
		set<string> closedSet;
		set<string> openSet;
		openSet.insert(start);



	}
};
/**
function A*(start,goal)
    closedset := the empty set    // The set of nodes already evaluated.
    openset := {start}    // The set of tentative nodes to be evaluated, initially containing the start node
    came_from := the empty map    // The map of navigated nodes.
 
    g_score[start] := 0    // Cost from start along best known path.
    // Estimated total cost from start to goal through y.
    f_score[start] := g_score[start] + heuristic_cost_estimate(start, goal)
 
    while openset is not empty
        current := the node in openset having the lowest f_score[] value
        if current = goal
            return reconstruct_path(came_from, goal)
 
        remove current from openset
        add current to closedset
        for each neighbor in neighbor_nodes(current)
            if neighbor in closedset
                continue
            tentative_g_score := g_score[current] + dist_between(current,neighbor)
 
            if neighbor not in openset or tentative_g_score < g_score[neighbor] 
                came_from[neighbor] := current
                g_score[neighbor] := tentative_g_score
                f_score[neighbor] := g_score[neighbor] + heuristic_cost_estimate(neighbor, goal)
                if neighbor not in openset
                    add neighbor to openset
 
    return failure
 
function reconstruct_path(came_from, current_node)
    if current_node in came_from
        p := reconstruct_path(came_from, came_from[current_node])
        return (p + current_node)
    else
        return current_node
//---------//

    Let P be the starting point
    Assign g, h, and f values to P
    Add P to the open list (at this point P is the only node on that list).
    Let B be the best node from the Open list (best == lowest f value)
        If B is the goal node -> quit, you found the path
        If the Open list is empty -> quit, no path exists
    Let C be a valid node connected to B
        Assign g, h, and f to C
        Check if C is on the Open or Closed List
            If yes, check whether new path is most efficient (lower f-value)
                If so, update the path
            Else add C to the Open List
        Repeat step 5 for all nodes connected to B
    Add B to the Closed list (we explored all neighbors)
    Repeat from step 4.

*/