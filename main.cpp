#include "unistd.h"
#include <string>

#include "graph.hpp"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

//@authors: Robert Lewis, Joseph Palazzo

// A driver to test Dijkstra's algorithm.  You can enable Floyd-Warshall for small graphs to check results.
int main (int argc, char **argv)
{
  // The first command line argument is the file that contains the edges.  There is one edge per line,
  // formatted as
  //   v1 v2 weight,
  // where v1 and v2 are the endpoints and weight the associated edge.
  if (argc == 1) {
    cout << "Usage: " << argv[0] << " edge_file" << endl;
    return 0;
  }
  char *edge_file = argv[1];

  // Prompt the user.
  cs303::Vertex s, t;
  cout << "Enter the start vertex: ";
  cin >> s;
  cout << "Enter the destination vertex: ";
  cin >> t;

  // Build the graph object.
  //cerr << "Reading the data...";
  cs303::Weighted_Graph G(edge_file);
  cout << "...done!" << endl << endl;

  // Remember: Floyd-Warshall requires V^2 space and V^3 time, so don't run it
  // if the number of vertices V is large.
  cs303::matrix<double> d = G.floyd_warshall();
  cout << d << endl;

  // Apply 
  cout << "Dijkstra..." << endl;
  
  auto dijkstra = G.dijkstra(s);
  auto path = dijkstra.path_to(t);
  for (auto &node : path) {
    cout << node << endl;
  }
  cout << "distance:              " << dijkstra.distance(t) << endl;
  cout << "no. of nodes on path:  " << path.size() << endl;
  cout << "no. of nodes relaxed:  " << dijkstra.num_nodes_relaxed() << endl;
  cout << "max. queue length:     " << dijkstra.max_queue_length() << endl;
  cout << "no. of nodes enqueued: " << dijkstra.total_nodes_enqueued() << endl <<endl;
  

  return 0;
}
