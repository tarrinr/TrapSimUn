#include "Twin.h"

typedef std::vector<double> vec;

vec gvec(Twin&);
void dvec(Twin&, const vec&);
double trap(const double&, const double&, const double&);
double simp13(const double&, const double&, const double&, const double&);
double simp38(const double&, const double&, const double&, const double&, const double&);
double uneven(const int&, const vec&, const vec&);

int main() {

	Twin t("Uneven Trapezoidal/Simpson's Rule");

	vec x, y;
	int n;

	t.println("Enter number of subintervals n.");
	t.display();
	std::cin >> n;
	std::cin.ignore(1000, '\n');
	std::cin.clear();

	while (true) {

		t.println("Enter the first element of Vector x.");
		t.println("Example: 2.3");
		t.display();

		double el;
		std::cin >> el;
		std::cin.ignore(1000, '\n');
		std::cin.clear();
		x.push_back(el);

		for (int i = 1; i < n + 1; i++) {
			t.println("Vector x:");
			t.println();
			dvec(t, x);
			t.println("Enter the next element.");
			t.display();

			std::cin >> el;
			std::cin.ignore(1000, '\n');
			std::cin.clear();
			x.push_back(el);
		}

		t.println("Vector x:");
		t.println();
		dvec(t, x);
		t.println("Enter 'x' to save and continue.");
		t.display();

		char in;
		std::cin >> in;
		std::cin.ignore(1000, '\n');
		std::cin.clear();
		if (in == 'x' || in == 'X') break;
		else x.clear();

	}

	while (true) {

		t.println("Enter the first element of Vector y.");
		t.println("Example: 2.3");
		t.display();

		double el;
		std::cin >> el;
		std::cin.ignore(1000, '\n');
		std::cin.clear();
		y.push_back(el);

		for (int i = 1; i < n + 1; i++) {
			t.println("Vector y:");
			t.println();
			dvec(t, y);
			t.println("Enter the next element.");
			t.display();

			std::cin >> el;
			std::cin.ignore(1000, '\n');
			std::cin.clear();
			y.push_back(el);
		}

		t.println("Vector y:");
		t.println();
		dvec(t, y);
		t.println("Enter 'x' to save and continue.");
		t.display();

		char in;
		std::cin >> in;
		std::cin.ignore(1000, '\n');
		std::cin.clear();
		if (in == 'x' || in == 'X') break;
		else y.clear();

	}

	double answer = uneven(n, x, y);

	t.println("Integral = ");
	t.print(answer);
	t.println();
	t.println("Press enter to exit. . .");
	t.display();

	std::cin.ignore(1000, '\n');
	std::cin.clear();

	return EXIT_SUCCESS;
}

double uneven(const int& n, const vec& x, const vec& y) {

	double h = x[1] - x[0];
	int k = 1;
	double sum = 0;
	double hf;

	double check = 0;

	for (int i = 1; i <= n; i++) {

		if (i != n) hf = x[i + 1] - x[i];

		if (abs(h - hf) < .000001 && i != n) {

			if (k == 3) {
				sum += simp13(h, y[i - 3], y[i - 2], y[i - 1]);
				k--;
			}
			else k++;
		}
		else {

			if (k == 1)
				sum += trap(h, y[i - 1], y[i]);
			else {

				if (k == 2)
					sum += simp13(h, y[i - 2], y[i - 1], y[i]);
				else
					sum += simp38(h, y[i - 3], y[i - 2], y[i - 1], y[i]);

				k = 1;
			}

		}

		h = hf;
		std::cout << i << " " << sum - check << std::endl;
		check = sum;
	}

	return sum;

}

double trap(const double& h, const double& f0, const double& f1) {

	return h * (f0 + f1) / 2.0;
}

double simp38(const double& h, const double& f0, const double& f1, const double& f2, const double& f3) {

	return 3.0 / 8.0 * h * (f0 + 3.0 * (f1 + f2) + f3);

}

double simp13(const double& h, const double& f0, const double& f1, const double& f2) {

	return h / 3.0 * (f0 + 4.0 * f1 + f2);
}

vec gvec(Twin& t) {

	vec b;
	double in;
	std::string input;

	std::getline(std::cin, input);
	std::stringstream iss(input);
	iss >> in;
	b.push_back(in);

	while (true) {

		t.println("Vector:");
		t.println();
		dvec(t, b);
		t.println("Enter the next element.");
		t.println("Enter 'x' to save and continue.");
		t.display();

		std::getline(std::cin, input);
		std::stringstream iss(input);
		iss >> in;

		if (input == "x" || input == "X") return b;
		else b.push_back(in);

	}
}

void dvec(Twin& t, const vec& vec) {

	for (auto&& i : vec) {
		t.println("[ ");
		t.print(i);
		t.print(" ]");
	}

	t.println();
}