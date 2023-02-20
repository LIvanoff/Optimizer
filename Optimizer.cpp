import Simplex;

#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	int sizeOfSimplex = 2;
	double x0[2] = { 0.0, 0.0 }; // 1.0, 1.0
	double epsilon = 0.01;
	double sizeOfStep = 1;

	Simplex::Simplex smp(x0, epsilon, sizeOfStep, sizeOfSimplex);
	return 0;
}