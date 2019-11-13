#include "matrix.hpp"
//@author: Robert Lewis 

namespace cs303 {
  // Copy semantics.
  template <typename T>
  matrix<T> &matrix<T>::operator= (matrix<T> &B)
  {
    nrows = B.nrows;
    ncols = B.ncols;
    delete[] a;
    a = new T[nrows*ncols];
    for (long int i = 0; i < nrows*ncols; i++) {
      a[i] = B.a[i];
    }
    return *this;
  }

  // Move semantics.
  template <typename T>
  matrix<T> &matrix<T>::operator= (matrix<T> &&B)
  {
    delete[] a;

    a = B.a;
    nrows = B.nrows;
    ncols = B.ncols;
    
    B.a = nullptr;
    B.nrows = 0;
    B.ncols = 0;
    
    return *this;
  }

  template class matrix<char>;
  template class matrix<int>;
  template class matrix<unsigned int>;
  template class matrix<long int>;
  template class matrix<unsigned long int>;
  template class matrix<float>;
  template class matrix<double>;
}
