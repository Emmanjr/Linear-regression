#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct error_storage {
	double error;
	double b0_storage;
	double b1_storage;
	bool operator>(error_storage var1) {
		return error > var1.error;
	}
	bool operator<(error_storage var1) {
		return error < var1.error;
	}
};

int main() {
	double x[] = { 1, 2, 3, 4, 5 };
	double y[] = { 1, 2, 3, 4, 5 };

	std::vector<error_storage>errors;
	double devi; // for calculating error on each stage,we name it devi(short for deviation) to //differentiate it from the error vector
	double b0 = 0; //this(the y intercept) is also known as the bias
	double b1 = 0;
	double learnRate = 0.01; //this controls how fast the machine learns, it has to be precise so the value //has to be low

	for (int i = 0; i < 20; i++) { //iterates 60 times
		int index = i % 5;
		double p = b0 + (b1 * x[index]); //basic linear regression implementation, using a value from 0 to 4 //as the coefficient
		devi = p - y[index]; //this calculated how much the resultant of the linear regression equation //deviates from the actual value it should be
		b0 = b0 - (learnRate * devi); //this subtracts b0 by how much it deviated * learnrate, if it was off the //mark before it will be slightly closer to it now
		//if devi is a negative number due to p being too low, there will be addition applied to p instead of //subtraction
		b1 = b1 - (learnRate * devi * x[index]); //this does the same for the second variable however also factors in what position index is on while doing it
		//if it gets it wrong on index=4, the correction will be *4 as harsh
		devi = fabs(devi);
		std::cout << "B0=" << b0 << " " << "B1=" << b1 << " " << "error=" << devi << std::endl;
		errors.push_back({ devi, b0, b1 });
	}
	std::sort(errors.begin(), errors.end());
	b0 = errors[0].b0_storage;
	b1 = errors[0].b1_storage;
	std::cout << "Optimal end values are: " << "B0=" << b0 << " " << "B1=" << b1 << " " << "error=" << errors[0].error << '\n';
	std::cout << "Enter a test x value\n";
	double test;
	std::cin >> test;
	double pred = b0 + b1 * test;
	std::cout << "\nThe value predicted by the model = " << pred;
	//the model would previously output a value roughly one less than the value inputted, however //making it iterate more and making it's index match with it's value helped
}