#include "graph.hpp"

//@author: Robert Lewis, Joseph Palazzo

namespace cs303 {
  dijkstra_results Weighted_Graph::dijkstra (Vertex s) 
  {
    // The max priority queue pq stores the edges with the minimum element determined by the edge weights.
    std::priority_queue<vertex_distance> pq;
	std::vector<double> dist;  
    std::vector<Vertex> v; 	
	
    // The algorithm goes here...
    dijkstra_results results;
	dist[s] = 0;
	double inf = 1.0/0.0;
	
	for (auto &v: s)
	{
		dist[v] = inf;
	}
	
	pq.push(s, dist[s]);
	
	
	
	/*
	dist[s] = 0;
	
    for all v in v-{s}
       d i s t [v] = INFINITY
	   
    S = NULL
    
	pq.append( s , dist [s]) 
	
    while (pq != NULL && pq != INFINITY) 
      u = min(pq[v])
      pg.pop()
      for all v of u
        if ( dist[v] > dist [u] + weight (u ,v)) 
           dist[v] = dist[u] + weight , v )
           pg.append(v , d i s t [ v ])
	*/

    // Populate results here...

    return results;
  }
}
