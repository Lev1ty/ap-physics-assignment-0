#include "Matrix.h"
#include <iomanip>
#include <numeric>
#include <string>

template <typename T> void ConfirmInput(const T &t) {
	std::cout << "This is a confirmation: you entered "
		<< std::quoted(std::to_string(t)) << "." << std::endl;
}

void Execute(const int);
