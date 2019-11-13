#if !defined(__CS303_GRAPH_HPP)
#define __CS303_GRAPH_HPP

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "edge.hpp"
#include "matrix.hpp"
#include "vertex.hpp"

//@author: Robert Lewis 

namespace cs303 {
  //------------------------------------------------------------------------------------------------------------
  // The dijkstra_results class for returning the results of Dijkstra's algorithm.

  class dijkstra_results {
    friend class Weighted_Graph;
    friend class Euclidean_Graph;
  public:
    Vertex source() {return s;}                     // Return the source node s.
    double distance (Vertex t) {return dist[t];}    // Return the s-t distance.
    std::vector<double> distances () {return dist;} // Return the entire distance array.
    std::list<Vertex> path_to (Vertex t);           // Return a shortest s-t path.

    unsigned long int num_nodes_relaxed ()    {return num_relaxed;}
    unsigned long int max_queue_length ()     {return max_enqueued;}
    unsigned long int total_nodes_enqueued () {return num_enqueued;}
  private:
    Vertex s;                       // The source node.
    std::vector<double> dist;       // dist[t] is the distance from s to t.
    std::vector<Vertex> from;       // from[t] is the node that precedes t on a shorted s-t path.
    unsigned long int num_relaxed;  // The number of nodes relaxed in the algorithm.
    unsigned long int num_enqueued; // The number of nodes enqueued in the algorithm; some nodes may be enqueued more than once.
    unsigned long int max_enqueued; // The maximum length of the queue encountered in the algorithm.
  };

  //------------------------------------------------------------------------------------------------------------
  // The a_star_results class for returning the results of the A* algorithm.
  
  class a_star_results {
    friend class Weighted_Graph;
    friend class Euclidean_Graph;
  public:
    Vertex source()      {return s;}    // Return the source node s.
    Vertex destination() {return t;}    // Return the destination node t.
    double distance ()   {return dist;} // Return the s-t distance.
    unsigned long int num_nodes_relaxed ()    {return num_relaxed;}
    unsigned long int max_queue_length ()     {return max_enqueued;}
    unsigned long int total_nodes_enqueued () {return num_enqueued;}
    std::list<Vertex> path_to ()     {return path;}
  private:
    Vertex s, t;                    // The source and destination nodes.
    double dist;                    // The distance from s to t.
    std::list<Vertex> path;         // A shortest path from s to t, starting with s and ending with t.
    unsigned long int num_relaxed;  // The number of nodes relaxed in the algorithm.
    unsigned long int num_enqueued; // The number of nodes enqueued in the algorithm; some nodes may be enqueued more than once.
    unsigned long int max_enqueued; // The maximum length of the queue encountered in the algorithm.
  };

  //------------------------------------------------------------------------------------------------------------
  // The class for undirected weighted graphs.
  
  class Weighted_Graph {
    friend class vertex_distance;
    friend std::ostream &operator<<(std::ostream &os, const Weighted_Graph &G);
  public:
    // Constructors.
    Weighted_Graph() : E{0}, V{0} {}
    Weighted_Graph(char *edge_file);
  
    inline long int num_edges() const    {return E;}
    inline long int num_vertices() const {return V;}

    // Return the weight the edge connecting v and w.
    double weight (Vertex v, Vertex w) 
    {
      if (v > w) std::swap(v, w); // Order things so v < w.
      return wt[std::tuple<Vertex,Vertex>(v, w)];
    }

    void add_edge(const Weighted_Edge &e);

    // Path and distance finding methods.
    dijkstra_results dijkstra(Vertex s);
    matrix<double>   floyd_warshall();

    // MST methods.
    // MST prim(std::string name = "T") const;
    // MST kruskal(std::string name = "T") const;

  protected:
    // Class for enqueueing vertex-distance pairs in the path-finding methods.
    class vertex_distance {
    public:
      vertex_distance(Vertex v, double d) : v{v}, d{d} {}
      
      Vertex v;
      double d;

      // The STL priority queue is a maximum priority queue.  Thus, in order for the queue's "maximum"
      // to be the minimum weight edge, we need to reverse the < operator.
      bool operator< (const vertex_distance &v) const {return (d > v.d);}
    };

    unsigned long int E;                             // The number o' edges.
    unsigned long int V;                             // The number o' vertices.
    std::vector<std::list<Weighted_Edge>> adj;       // The adjacency list.
    std::vector<Weighted_Edge> edges;                // The edges.
    std::map<std::tuple<Vertex, Vertex>, double> wt; // The edge weights, stored in a map with the edge endpoints as keys.
  };

  //------------------------------------------------------------------------------------------------------------
  // Undirected graphs whose edge weight correspond to a metric distance.

  // This class is derived from Weighted_Graph.
  class Euclidean_Graph : public Weighted_Graph {
  public:
    Euclidean_Graph() {};
    Euclidean_Graph(char *edge_file, char *vertex_file);

    // An enum for specifying the heuristic to be used in A*.
    enum heuristic {none, manhattan_norm, euclidean_norm, geodesic};

    a_star_results A_star (Vertex s, Vertex t, enum heuristic choice);
  private:
    std::vector<double> x, y; // The coordinates of the vertices.

    double zero (const Vertex &u, const Vertex &v);
    double one_norm (const Vertex &u, const Vertex &v);
    double two_norm (const Vertex &u, const Vertex &v);
    double great_circle (const Vertex &u, const Vertex &v);
  };

  std::ostream &operator<<(std::ostream &os, const Weighted_Graph &G);
  std::istream &operator>>(std::ostream &is,       Weighted_Graph &G);
  std::istream &operator>>(std::ostream &is,       Euclidean_Graph &G);
}
#endif
