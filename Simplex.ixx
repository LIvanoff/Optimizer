module;
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

export module Simplex;

using namespace std;

export namespace Simplex {
	class Simplex
	{
	public:
		Simplex(double* x0, double epsilon, double sizeOfStep, int sizeOfSimplex);
		~Simplex();
		void calcDelta();
		void calcVertex();
		double calcFuncValue(double x, double y);
		void printArray();
		void sort();
		void calcGravityCenter();
		void calcNewVertex();
		void calcNewGravityCenter();
		bool stopCriteria();
		void getReduction();

	private:
		int sizeOfSimplex;
		int sizeOfArray;
		double** arrayOfSimplex;
		double epsilon;
		double delta[2];
		double sizeOfStep;
		double gravityCenter[2];
	};

	Simplex::Simplex(double* x0, double epsilon, double sizeOfStep, int sizeOfSimplex)
	{
		this->sizeOfSimplex = sizeOfSimplex;
		this->epsilon = epsilon;
		this->sizeOfStep = sizeOfStep;
		this->sizeOfArray = sizeOfSimplex + 1;
		this->arrayOfSimplex = new double* [sizeOfArray];

		for (int i = 0; i < sizeOfArray; i++)
		{
			this->arrayOfSimplex[i] = new double[sizeOfArray];
		}

		this->arrayOfSimplex[0][0] = x0[0];
		this->arrayOfSimplex[0][1] = x0[1];

		calcDelta();
		calcVertex();

		for (int i = 0; i < sizeOfArray; i++)
		{
			arrayOfSimplex[i][2] = calcFuncValue(arrayOfSimplex[i][0], arrayOfSimplex[i][1]);
		}

		printArray();

		while (!stopCriteria())
		{
			sort();
			calcGravityCenter();
			calcNewVertex();

			double newVertex = calcFuncValue(this->arrayOfSimplex[2][0], this->arrayOfSimplex[2][1]);

			if (newVertex > this->arrayOfSimplex[2][2])
			{
				getReduction();
			}
			else
			{
				this->arrayOfSimplex[2][2] = newVertex;
			}
			calcNewGravityCenter();
		}
		cout << "Конструктор отработал!\n";
	}

	Simplex::~Simplex()
	{
		for (int i = 0; i < sizeOfArray; i++)
		{
			delete[] this->arrayOfSimplex[i];
		}
		delete[] this->arrayOfSimplex;
		cout << "Деструктор отработал!\n";
	}

	void Simplex::calcDelta()
	{
		this->delta[0] = ((sqrt(this->sizeOfSimplex + 1) - 1) / (this->sizeOfSimplex * sqrt(2))) * this->sizeOfStep;
		cout << delta[0] << endl;
		this->delta[1] = ((sqrt(this->sizeOfSimplex + 1) + this->sizeOfSimplex - 1) / (this->sizeOfSimplex * sqrt(2))) * this->sizeOfStep;
		cout << delta[1] << endl;
	}

	void Simplex::calcVertex()
	{
		this->arrayOfSimplex[1][0] = arrayOfSimplex[0][0] + this->delta[0];
		cout << this->arrayOfSimplex[1][0] << endl;
		this->arrayOfSimplex[1][1] = arrayOfSimplex[0][1] + this->delta[1];
		cout << this->arrayOfSimplex[1][1] << endl;
		this->arrayOfSimplex[2][0] = arrayOfSimplex[0][1] + this->delta[1];
		cout << this->arrayOfSimplex[2][0] << endl;
		this->arrayOfSimplex[2][1] = arrayOfSimplex[0][0] + this->delta[0];
		cout << this->arrayOfSimplex[2][1] << endl;
	}

	double Simplex::calcFuncValue(double x, double y)
	{
		return pow(x, 2) - x * y + pow(y, 2) + 2 * x + 3 * y; // 2.8 * pow(y, 2) + 1.9 * x + 2.7 * pow(x, 2) + 1.6 - 1.9 * y;
	}

	void Simplex::printArray()
	{
		for (int i = 0; i < this->sizeOfArray; i++) {
			for (int j = 0; j < this->sizeOfArray; j++) {
				cout << right << setw(12) << this->arrayOfSimplex[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}

	void Simplex::sort()
	{
		for (int i = 0; i < this->sizeOfArray; i++)
		{
			bool flag = true;
			for (int j = 0; j < this->sizeOfArray - (i + 1); j++)
			{
				if (abs(this->arrayOfSimplex[j][2]) > abs(this->arrayOfSimplex[j + 1][2]))
				{
					flag = false;
					swap(this->arrayOfSimplex[j][2], this->arrayOfSimplex[j + 1][2]);
					swap(this->arrayOfSimplex[j][1], this->arrayOfSimplex[j + 1][1]);
					swap(this->arrayOfSimplex[j][0], this->arrayOfSimplex[j + 1][0]);
				}
			}
			if (flag)
			{
				break;
			}
		}
	}

	void Simplex::calcGravityCenter()
	{
		this->gravityCenter[0] = 1.0 / this->sizeOfSimplex * (this->arrayOfSimplex[0][0] + this->arrayOfSimplex[1][0]);
		this->gravityCenter[1] = 1.0 / this->sizeOfSimplex * (this->arrayOfSimplex[0][1] + this->arrayOfSimplex[1][1]);
	}

	void Simplex::calcNewVertex()
	{
		this->arrayOfSimplex[2][0] = 2.0 * this->gravityCenter[0] - this->arrayOfSimplex[2][0];
		this->arrayOfSimplex[2][1] = 2.0 * this->gravityCenter[1] - this->arrayOfSimplex[2][1];
	}

	void Simplex::calcNewGravityCenter()
	{
		this->gravityCenter[0] = (this->arrayOfSimplex[0][0] + this->arrayOfSimplex[1][0] + this->arrayOfSimplex[2][0]) / (this->sizeOfSimplex + 1);
		this->gravityCenter[1] = (this->arrayOfSimplex[0][1] + this->arrayOfSimplex[1][1] + this->arrayOfSimplex[2][1]) / (this->sizeOfSimplex + 1);
	}

	bool Simplex::stopCriteria()
	{
		double funcValue = calcFuncValue(this->gravityCenter[0], this->gravityCenter[1]);
		cout << " funcValue = " << funcValue << endl;
		for (int i = 0; i < this->sizeOfArray; i++)
		{
			cout << " " << abs(this->arrayOfSimplex[i][2] - funcValue) << " ?= " << this->epsilon << endl;
			if (abs(this->arrayOfSimplex[i][2] - funcValue) > this->epsilon)
			{
				printArray();
				return false;
			}
		}
		printArray();
		return true;
	}

	void Simplex::getReduction()
	{
		for (int i = 1; i < this->sizeOfArray; i++)
		{
			for (int j = 0; j < this->sizeOfArray - 1; j++)
			{
				arrayOfSimplex[i][j] = arrayOfSimplex[0][j] + 0.5 * (arrayOfSimplex[i][j] - arrayOfSimplex[0][j]);
			}
			this->arrayOfSimplex[i][2] = calcFuncValue(arrayOfSimplex[i][0], arrayOfSimplex[i][1]);
		}
	}
}
