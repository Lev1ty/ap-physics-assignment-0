#include "Driver.h"

size_t data_size, poly_deg;
Matrix x, y, van;

int main(int argc, char **argv) {
  if (argc == 2) // for testing
    for (int i = 1; i <= std::stoi(argv[1]); i++)
      Execute(i);
  else
    Execute(0); // normal execution
}

void Execute(const int iteration) {
  // reset all static variables
  data_size = poly_deg = 0;
  x.Get().clear();
  y.Get().clear();
  van.Get().clear();
  if (iteration > 0) { // open test cases
    std::freopen((std::string("TestCaseIn") + std::to_string(iteration) +
                  std::string(".txt"))
                     .c_str(),
                 "r", stdin);
    std::freopen((std::string("TestCaseOut") + std::to_string(iteration) +
                  std::string(".txt"))
                     .c_str(),
                 "w", stdout);
  }
  // preamble
  std::cout << "Welcome to the Least Squares C Programming Assignment."
            << std::endl;
  std::cout << "This program was made by Adam Yu." << std::endl;
  std::cout << "You may enter arbitrary parameters for the degree of "
               "polynomial you wish to fit, etc., given reasonable bounds and "
               "limitations: machine precision and bounds."
            << std::endl;
  std::cout << std::endl;
  std::cout << "clang 4.0.1 was used to compile this program. This program was "
               "developed natively in Ubuntu 17.10."
            << std::endl;
  std::cout << std::endl;
  std::cout << "Let's begin." << std::endl;
  std::cout << std::endl;
  std::cout << "Please enter the number of data points you will input."
            << std::endl;
  std::cin >> data_size;
  ConfirmInput(data_size);
  std::cout
      << "Please enter you data points in the format of ordered pairs (x,y)."
      << std::endl;
  for (int i = 0; i < data_size; i++) { // read data points
    double a, b;
    std::cin >> a >> b;
    ConfirmInput(a);
    ConfirmInput(b);
    x.Get().emplace_back(std::vector<double>{std::move(a)});
    y.Get().emplace_back(std::vector<double>{std::move(b)});
  }
  std::cout << "Please enter the degree of the polynomial you wish to fit."
            << std::endl;
  std::cin >> poly_deg;
  ConfirmInput(poly_deg);
  for (const auto &a : x.Get()) { // generate vandermonde matrix
    std::vector<double> tmp;
    for (int i = poly_deg; i >= 0; i--)
      tmp.emplace_back(pow(a.front(), i));
    van.Get().emplace_back(std::move(tmp));
  }
  std::cout << std::endl;
  // print all required information
  std::cout << "This is the input data." << std::endl;
  for (int i = 0; i < data_size; i++)
    std::cout << "(x, y) = (" << x.Get().at(i).front() << ", "
              << y.Get().at(i).front() << ")" << std::endl;
  std::cout << std::endl;
  std::cout << "The degree polynomial you wish to fit is " << poly_deg << "."
            << std::endl;
  std::cout << std::endl;
  std::cout << "This is the Vandermonde Matrix." << std::endl;
  std::cout << van << std::endl;
  std::cout << "This is the Vandermonde Matrix Transposed." << std::endl;
  std::cout << van.Transpose() << std::endl;
  std::cout << "This is the product of the Vandermonde Matrix Transposed and "
               "the Vandermonde Matrix."
            << std::endl;
  std::cout << van.Transpose() * van << std::endl;
  std::cout << "This is the coefficient vector." << std::endl;
  // from vanBemmel 2017 lecture notes
  std::cout << (van.Transpose() * van).Inverse() * van.Transpose() * y
            << std::endl;
}
