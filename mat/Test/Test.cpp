#include <experimental/random>
#include <iostream>
#include <string>

void Execute(const int iteration) {
  std::freopen((std::string("../TestCaseIn") + std::to_string(iteration) +
                std::string(".txt"))
                   .c_str(),
               "w", stdout);
  auto num_points = std::experimental::randint(10, 20);
  std::cout << num_points << std::endl;
  for (int i = 0; i < num_points; i++)
    std::cout << std::experimental::randint(-100, 100) << ' '
              << std::experimental::randint(-100, 100) << std::endl;
  std::cout << std::experimental::randint(1, 5) << std::endl;
}

int main(int argc, char **argv) {
  for (int i = 1; i <= std::stoi(argv[1]); i++)
    Execute(i);
}
