#if !defined(__CS303_MATRIX_HPP)
#define __CS303_MATRIX_HPP

#include <iomanip>
#include <iostream>

#include "vertex.hpp"

//@author: Robert Lewis 

namespace cs303 {
  template <typename T>
  class matrix {
    friend std::ostream &operator<<(std::ostream &os,  matrix<T> &A) {
      for (long int i = 0; i < A.num_rows(); i++) {
	for (long int j = 0; j < A.num_cols(); j++) {
	  os << std::setw(4) << A(i,j) << " ";
	}
	os << std::endl;
      }
      return os;
    }
  public:
    matrix () : nrows{0}, ncols{0}, a{nullptr} {}

    matrix (long int m, long int n) : nrows{m}, ncols{n} {a = new T[nrows*ncols];}

    ~matrix () {delete[] a;}

    // Copy semantics.
    matrix (matrix<T> &B) : nrows{B.nrows}, ncols{B.ncols} {a = new T[nrows*ncols];}
    matrix<T> &operator= (matrix<T> &B);

    // Move semantics.
    matrix (matrix<T> &&B) : nrows{B.nrows}, ncols{B.ncols} {a = B.a; B.a = nullptr; B.nrows = B.ncols = 0;}
    matrix<T> &operator= (matrix<T> &&B);

    inline long int num_rows() {return nrows;}
    inline long int num_cols() {return ncols;}

    inline T &operator() (long int i, long int j) {return a[j*nrows+i];}
  private:
    long int nrows, ncols;
    T *a;
  };
}
#endif
