#include "Matrix.h"

// return mutable reference to matrix_
std::vector<std::vector<double>> &Matrix::Get() noexcept { return matrix_; }

// calculate matrix transpose
Matrix Matrix::Transpose() const noexcept {
  AssertIsNonRagged();
  Matrix ret;
  ret.matrix_.resize(matrix_.front().size(),
                     std::vector<double>(matrix_.size()));
  for (int i = 0; i < matrix_.size(); i++)
    for (int j = 0; j < matrix_.front().size(); j++)
      ret.matrix_.at(j).at(i) = matrix_.at(i).at(j); // invert dimensions
  return ret;
}

// entry fx to calculate static recursive determinant fx
double Matrix::Determinant() const noexcept { return Determinant(*this); }

// utility to print matrix
std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
  for (const auto &a : matrix.matrix_) {
    for (const auto &b : a)
      os << b << '\t';
    os << std::endl;
  }
  return os;
}

// discards any elements in row row or column col
Matrix Matrix::Strip(const int row, const int col) const noexcept {
  AssertIsNonRagged();
  Matrix ret;
  for (int i = 0; i < matrix_.size(); i++) {
    if (i == row) // skip row
      continue;
    std::vector<double> tmp; // tmp vector to be moved
    for (int j = 0; j < matrix_.front().size(); j++) {
      if (j == col) // skip col
        continue;
      tmp.push_back(matrix_.at(i).at(j));
    }
    ret.matrix_.emplace_back(std::move(tmp));
  }
  return ret;
}

// entry fx to calculate inverse
Matrix Matrix::Inverse() const noexcept { return Adjugate() / Determinant(); }

// matrix inner product
Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
  lhs.AssertIsNonRagged();
  rhs.AssertIsNonRagged();
  assert(lhs.matrix_.front().size() ==
         rhs.matrix_.size()); // check inner dimensions
  Matrix ret;
  ret.matrix_.resize(lhs.matrix_.size(),
                     std::vector<double>(rhs.matrix_.front().size()));
  for (int i = 0; i < lhs.matrix_.size(); i++)           // row size of lhs
    for (int j = 0; j < rhs.matrix_.front().size(); j++) // col size of rhs
      for (int k = 0; k < rhs.matrix_.size(); k++)       // row size of rhs
        ret.matrix_.at(i).at(j) +=
            lhs.matrix_.at(i).at(k) * rhs.matrix_.at(k).at(j);
  return ret;
}

// divide matrix by scalar
Matrix operator/(const Matrix &lhs, const double rhs) {
  Matrix ret;
  ret.matrix_ = lhs.matrix_; // copy construct ret
  for (auto &&a : ret.matrix_)
    for (auto &&b : a)
      b /= rhs;
  return ret;
}

// generate minor matrix
Matrix Matrix::Minor() const noexcept {
  AssertIsSquare();
  Matrix ret;
  ret.matrix_.resize(matrix_.size(),
                     std::vector<double>(matrix_.front().size()));
  for (int i = 0; i < matrix_.size(); i++)
    for (int j = 0; j < matrix_.front().size(); j++)
      ret.matrix_.at(i).at(j) =
          Strip(i, j).Determinant(); // definition of minor from wikipedia
  return ret;
}

// generate cofactor matrix
Matrix Matrix::Cofactor() const noexcept {
  AssertIsSquare();
  Matrix ret = Minor(); // derived from minor
  for (int i = 0; i < ret.matrix_.size(); i++)
    for (int j = 0; j < ret.matrix_.front().size(); j++)
      ret.matrix_.at(i).at(j) *=
          pow(-1, i + j); // definition of cofactor from wikipedia
  return ret;
}

// generate adjugate matrix a.k.a. transposed cofactor
Matrix Matrix::Adjugate() const noexcept {
  AssertIsSquare();
  return Cofactor().Transpose(); // definition of adjugate from wikipedia
}

// static recursive implementation of determinant
double Matrix::Determinant(const Matrix &matrix) noexcept {
  matrix.AssertIsSquare();
  if (matrix.matrix_.size() == 1) // base case of 1*1 matrix
    return matrix.matrix_.front().front();
  if (matrix.matrix_.size() == 2) // base case of 2*2 matrix
    return matrix.matrix_.front().front() * matrix.matrix_.back().back() -
           matrix.matrix_.front().back() * matrix.matrix_.back().front();
  double ret = 0;
  for (int i = 0; i < matrix.matrix_.front().size(); i++)
    ret += pow(-1, i) * matrix.matrix_.front().at(i) *
           matrix.Strip(0, i).Determinant(); // recurse
  return ret;
}

// assert non-empty matrix
void Matrix::AssertIsNonEmpty() const noexcept {
  assert(!matrix_.empty()); // assert matrix is not empty
}

// assert rectangular matrix
void Matrix::AssertIsNonRagged() const noexcept {
  AssertIsNonEmpty(); // check null case before access
  const auto row_size = matrix_.front().size();
  for (const auto &a : matrix_)
    assert(a.size() == row_size); // assert each row size is equal
}

// assert square matrix
void Matrix::AssertIsSquare() const noexcept {
  AssertIsNonRagged(); // check general rectangular case
  assert(matrix_.size() ==
         matrix_.front().size()); // special rectangle matrix case
}
