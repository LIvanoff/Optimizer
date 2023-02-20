import Simplex;

#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	int sizeOfSimplex = 2;
	double x0[2] = { -15.0, -15.0 }; // 1.0, 1.0
	double epsilon = 0.01;
	double sizeOfStep = 0.1;

	Simplex::Simplex smp(x0, epsilon, sizeOfStep, sizeOfSimplex);
	system("pause");
	return 0;
}