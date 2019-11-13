#if !defined(__CS303_EDGE_HPP)
#define __CS303_EDGE_HPP

#include <iostream>
#include <stdexcept>

#include "vertex.hpp"

//@author: Robert Lewis 

namespace cs303 {
  // A class for undirected weighted edges.
  class Weighted_Edge {
    friend std::istream &operator>>(std::istream &is, Weighted_Edge &e) {
      is >> e.v >> e.w >> e.wt;
      return is;
    };
    friend std::ostream &operator<<(std::ostream &os, const Weighted_Edge &e) {
      os << e.v << "--" << e.w << " (" << e.wt << ")";
      return os;
    };

  public:
    Weighted_Edge () {};
    Weighted_Edge (Vertex v, Vertex w, double weight) : v{v}, w{w}, wt{weight} {};
    Weighted_Edge (const Weighted_Edge &e) : v{e.v}, w{e.w}, wt{e.wt} {};

    inline double weight(void) const {return wt;}  // Return the weight of the edge.
    inline Vertex either(void) const {return v;}   // Return endpoint v of the edge.
    Vertex other(const Vertex vertex) const {      // Given one endpoint, return the other.
      return ( (vertex == v) ? w : ( (vertex == w) ? v : throw std::runtime_error("Invalid edge!") ) );
    }

  private:
    Vertex v, w;  // The vertices connected by the edge.
    double wt;    // The weight of the edge.
  };

  std::istream &operator>>(std::istream &is, Weighted_Edge &e);
  std::ostream &operator<<(std::ostream &os, const Weighted_Edge &e);
}
#endif
