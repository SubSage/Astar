#include <iostream>
#include <string>
#include <list>
using namespace std;

class weightedGraph
{
protected:
	//because this is c++....
	class vertex;
	class edge;

	class vertex
	{
	public:
		//in general, could be anything
		string data;
		list<edge*> adjacencyList;

		vertex(string a)
		{
			data = a;
		}
	};

	class edge
	{
	public:
		vertex* start;
		vertex* end;
		double weight;

		edge(vertex* s, vertex* e, double w)
		{
			start=s;
			end=e;
			weight=w;
		}
	};


	list<vertex*> vertexList;
	
	vertex* findVertex(string a)
	{
		for each( vertex* v in vertexList )
		{
			if( v->data == a )
				return v;
		}
		return NULL;
	}

	//return true if there is an edge from u to v
	//, false otherwise
	bool existsEdge(vertex* u, vertex* v)
	{
		for each(edge* x in u->adjacencyList)
		{
			if( v == x->end )
				return true;
		}
		return false;
	}

public:
	weightedGraph()
	{
	}

	//add vertex with data a to graph
	void addVertex(string a)
	{
		vertexList.push_back( new vertex(a) );
	}

	//add edge going from a to b in the graph
	void addWeightedEdge(string a, string b, double w)
	{
		vertex* vertA = findVertex(a);
		vertex* vertB = findVertex(b);

		if( vertA != NULL && vertB != NULL )
			vertA->adjacencyList.push_back( new edge(vertA,vertB,w) );
	}

	//add an edge with weight 1
	void addEdge(string a, string b)
	{
		addWeightedEdge(a,b,1);
	}

	//return edge (pointer) from a to b,
	//return NULL if no edge exists
	edge* getEdge(vertex* a, vertex* b)
	{
		for each(edge* e in a->adjacencyList)
		{
			if( e->end == b )
				return e;
		}
		return NULL;
	}

};