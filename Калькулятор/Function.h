#include "iostream"
#include "fstream"

using namespace std;

enum Method { iter = 0, newton = 1, division = 2 };

class FunctionData {
public:
	double x1 = 0;
	double x2 = 0;
	double x3 = 0;

	FunctionData() {};
	FunctionData(double x1, double x2, double x3) {
		this->x1 = x1;
		this->x2 = x2;
		this->x3 = x3;
	}
};

class EquationData {
public:
	FunctionData func;
	double left = 0;
	double right = 0;
	double eps = 0.1;
	Method method;

	EquationData(FunctionData f, double l, double r, double e, int m) {
		func = f;
		left = l;
		right = r;
		eps = e;

		switch (m) {
		case division: method = division; break;
		case newton: method = newton; break;
		case iter: method = iter; break;
		}

		fstream fsout("test.txt", ios::out);
		fsout.close();
		fstream fs;
		fs.open("test.txt", fstream::in | fstream::app);
		if (fs.is_open()) {
			fs << "(" << func.x1 << ")*x^2 + (" << func.x2 << ")*x + (" << func.x3 << ")" << endl;
			fs << "[" << left << " : " << right << "]" << endl;
			fs << "eps = " << eps << endl;
		}
	}
};

double findNewton(EquationData);
double findDiv(EquationData);
double findIter(EquationData);
void save(double x);

void save(double x) {
	fstream fs;
	fs.open("test.txt", fstream::in | fstream::app);
	if (fs.is_open()) fs << x << endl;
	fs.close();
}

double solve(EquationData data) {
	double x;
	switch (data.method) {
	case iter: x = findIter(data); break;
	case newton: x = findNewton(data); break;
	case division: x = findDiv(data); break;
	}

	return x;
}

double equation(FunctionData func, double x) {
	return ((func.x1 * x * x) + (func.x2 * x) + func.x3);
}

double derivative(FunctionData func, double x) {
	double h, fc;
	h = 0.01; // шаг, с которым вычисляем производную
	fc = (equation(func, x + h) - equation(func, x - h)) / (2 * h); // центральная
	return fc;
}

double findNewton(EquationData data) {
	double f, df, x0;
	double x = data.right;
	int iter = 0;

	FunctionData func = data.func;
	do {
		x0 = x;
		f = equation(func, x);
		df = derivative(func, x);
		x = x - f / df;
		save(x);
		iter++;
	} while (fabs(x - x0) > data.eps&& iter < 20000);

	return x;
}

double findDiv(EquationData data) {
	FunctionData func = data.func;

	double x = 0;
	int iter = 0;
	if (equation(func, data.right) * equation(func, data.left) > 0) {
		while ((data.right - data.left) > data.eps&& iter < 20000) {
			x = (data.left + data.right) / 2;
			save(x);
			if (equation(func, data.right) * equation(func, x) < 0) data.left = x;
			else data.right = x;
			iter++;
		}
	}
	else {
		throw "Нет корней";
	}

	return x;
}

double findIter(EquationData data) {
	FunctionData func = data.func;
	double x0;
	double x = (fabs(data.right) - fabs(data.left)) / 2;
	int iter = 0;
	do {
		x0 = x;
		x = x0 - 0.2 * equation(func, x0);
		save(x);
		iter++;
	} while (fabs(x0 - x) > data.eps&& iter < 20);

	return x;
}


