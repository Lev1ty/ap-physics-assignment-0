#include <cassert>
#include <vector>
#include <iostream>
#include <cmath>

class Matrix {
public:
  std::vector<std::vector<double>> &Get() noexcept;
  Matrix Transpose() const noexcept;
  double Determinant() const noexcept;
  Matrix Strip(const int, const int) const noexcept;
  Matrix Inverse() const noexcept;
  
  friend std::ostream &operator<<(std::ostream &, const Matrix &);
  friend Matrix operator*(const Matrix &, const Matrix &);
  friend Matrix operator/(const Matrix &, const double);

private:
  Matrix Minor() const noexcept;
  Matrix Cofactor() const noexcept;
  Matrix Adjugate() const noexcept;

  static double Determinant(const Matrix &) noexcept;

  void AssertIsNonEmpty() const noexcept;
  void AssertIsNonRagged() const noexcept;
  void AssertIsSquare() const noexcept;

  std::vector<std::vector<double>> matrix_;
};
