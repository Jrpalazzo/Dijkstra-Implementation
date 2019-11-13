#include "graph.hpp"
//@author: Robert Lewis 

namespace cs303 {
  static double inf = 1.0/0.0;

  //------------------------------------------------------------------------------------------------------------
  // The dijkstra_results class for returning the results of Dijkstra's algorithm.
  
  std::list<Vertex> dijkstra_results::path_to (Vertex t) {
    std::list<Vertex> path;
    if (dist[t] == inf) return path;
    path.push_front(t);
    Vertex v = t;
    while (v != s) {
      v = from[v];
      path.push_front(v);
    }
    return path;
  }

  //------------------------------------------------------------------------------------------------------------
  // The class for undirected weighted graphs.

  // Friend output function.
  std::ostream &operator<<(std::ostream &os, const Weighted_Graph &G) 
  {
    os << " no. of vertices: " << G.V << "\n";
    os << " no. of edges:    " << G.E << "\n";
    os << " adjacency list = {" << "\n";
    for (unsigned long int v = 0; v < G.V; v++) {
      os << "  " << v << ": ";
      for (auto &w : G.adj[v]) {
	os << w << " ";
      }
      os << std::endl;
    }
    os << " }" << std::endl;
    os << "}" << std::endl;

    return os;
  }

  Weighted_Graph::Weighted_Graph(char *edge_file)
  {
    std::ifstream in(edge_file);
    if (in.is_open()) { // Only try to read if we successfully opened the file.
      Weighted_Edge e;
      while (in >> e) {
	add_edge(e);
      }
      in.close();       // Clean up.
    }
    else {
      throw std::runtime_error("Unable to open file!");
    }
  }

  // Add an edge by adding it to edges[] and updating adj[], resizing either as needed.
  void Weighted_Graph::add_edge(const Weighted_Edge &e)
  {
    auto v = e.either();
    auto w = e.other(v);

    if (std::max(v,w) + 1 > adj.size()) {
      adj.resize(std::max(v,w)+1);
      V = std::max(v,w)+1;
    }

    adj[v].push_back(e);
    adj[w].push_back(e);

    if (v > w) {
      std::swap(v, w);
    }
    wt[std::tuple<Vertex,Vertex>(v, w)] = e.weight();

    edges.push_back(e);
    E++;
  }

  matrix<double> Weighted_Graph::floyd_warshall ()
  {
    // This function returns the matrix of APSP distances.
    // To do: also return the path data.
    
    matrix<double> d(V,V);
    matrix<Vertex> next(V,V);
    double inf = 1.0/0.0;

    for (unsigned long int j = 0; j < V; j++) {
      for (unsigned long int i = 0; i < V; i++) {
	d(i,j) = inf;
      }
      d(j,j) = 0;
    }
    
    for (unsigned long int i = 0; i < V; i++) {
      for (auto &e : adj[i]) {
	auto j = e.other(i);
	d(i,j) = weight(i,j);
	next(i,j) = j;
      }
    }
      
    for (unsigned long int k = 0; k < V; k++) {
      for (unsigned long int i = 0; i < V; i++) {
	for (unsigned long int j = 0; j < V; j++) {
	  if (d(i,k) + d(k,j) <= d(i,j)) { // Update the shortest path.
	    d(i,j) = d(i,k) + d(k,j);
	    next(i,j) = next(i,k);
	  }
	}
      }
    }

    // d[i][j] is now the shortest path distance from vertex i to vertex j.
    return d;
  }

  //------------------------------------------------------------------------------------------------------------
  // Undirected graphs whose edge weight correspond to a metric distance.
  
  Euclidean_Graph::Euclidean_Graph(char *edge_file, char *vertex_file) : x{0}, y{0}
  {
    std::ifstream e_in(edge_file);
    if (e_in.is_open()) { // Only try to read if we successfully opened the file.
      Weighted_Edge e;
      while (e_in >> e) {
	add_edge(e);
      }
      e_in.close();       // Clean up.
    }
    else {
      throw std::runtime_error("Unable to open file!");
    }

    std::ifstream v_in(vertex_file);
    if (v_in.is_open()) { // Only try to read if we successfully opened the file.
      Weighted_Edge e;
      unsigned long int k;
      double x_in, y_in;
      while (v_in >> k >> x_in >> y_in) {
	if (k == x.size()) {
	  x.push_back(x_in);
	}
	if (k == y.size()) {
	  y.push_back(y_in);
	}
      }
      v_in.close();       // Clean up.
    }
    else {
      throw std::runtime_error("Unable to open file!");
    }
  }

  double Euclidean_Graph::zero (const Vertex &u, const Vertex &v)
  {
    return 0.0;
  }

  double Euclidean_Graph::one_norm (const Vertex &u, const Vertex &v)
  {
    return fabs(x[u] - x[v]) + fabs(y[u] - y[v]);
  }

  double Euclidean_Graph::two_norm (const Vertex &u, const Vertex &v)
  {
    double sum = {pow(x[u] - x[v], 2) + pow(y[u] - y[v], 2)};
    return sqrt(sum);
  }

  double Euclidean_Graph::great_circle (const Vertex &u, const Vertex &v)
  {
    double lon1 = (M_PI/180) * x[u];
    double lon2 = (M_PI/180) * x[v];
    double dlon = fabs(lon1 - lon2);

    double lat1 = (M_PI/180) * y[u];
    double lat2 = (M_PI/180) * y[v];
      
    double r = 3959.0;
    return r * acos(sin(lat1)*sin(lat2) + cos(lat1)*cos(lat2)*cos(dlon));
  }
}
