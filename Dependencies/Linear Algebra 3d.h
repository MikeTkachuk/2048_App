#ifndef Linear_Algebra_3d
#define Linear_Algebra_3d

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>


using namespace std;

class vect {

private:
	double* root;
	int len;
public: 
	vect() {
		root = new double[3]{ 0 };
		len = 3;
	}
	void Init() {
		root = new double[3]{ 0 };
		len = 3;
	}

	vect(int length) {
		Init(length);
	}
	void Init(int length) {
		root = new double[length] {0};
		len = length;
	}

	vect(int length, double* value) {
		Init(length, value);
	}
	void Init(int length, double* value) {
		root = new double[length];
		for (int i = 0; i < length; i++) {
			root[i] = value[i];
		}
		len = length;
	}

	vect(double x, double y, double z) {
		Init(x, y, z);
	}
	void Init(double x, double y, double z) {
		if (root != 0)
			delete[] root;
		root = new double[3];
		root[0] = x;
		root[1] = y;
		root[2] = z;
		len = 3;
	}

	vect(double* value) {
		Init(value);
	}
	void Init(double* value) {
		root = new double[3];
		for (int i = 0; i < 3; i++) {
			root[i] = value[i];
		}
		len = 3;
	}

	vect& randomize(double norma) {
		double b;
		double c;
		double temp;
		b = (rand() % 3600) / 10.0 / 360.0 * 3.14159256;
		c = (rand() % 3600) / 10.0 / 360.0 * 3.14159256;
		root[0] = norma * cos(c);
		for (int i = 1; i < len - 1; i++) {

			root[i] = root[i - 1] / cos(c) * sin(c);
			b = (rand() % 3600) / 10.0 / 360.0 * 3.14159256;
			c = (rand() % 3600) / 10.0 / 360.0 * 3.14159256;
			root[i] *= cos(c);
		}
		root[len - 1] = root[len - 2] / cos(c) * sin(c);

		for (int i = 0; i < ceil(len / 2); i++) {
			c = rand() % len;
			b = rand() % len;
			while (b == c)
				b = rand() % len;
			temp = this->root[(int)c];
			this->root[(int)c] = this->root[(int)b];
			this->root[(int)b] = temp;
		}
		return *this;
	}


	//COPY CONSTRUCTOR
	vect(const vect& t) {
		root = 0;
		Init(t);
	}
	void Init(const vect& t) {
		removeRoot();
		len = t.len;
		root = new double[t.len];
		for (int i = 0; i < t.len; i++) {
			root[i] = t.root[i];
		}
	}


	//ACCESS FUNCTIONS
	int getLen() {
		return len;
	}
	double operator [] (int x) {
		if (x > len - 1 || x < 0) {
			cout << "Error accessing vector coordinate with invalid index.\n";
			system("pause");
			abort();
		}
			return root[x];
	}
	

	//ASSIGNMENT OPERATOR
	vect& operator = (const vect& X) {
		removeRoot();
		len = X.len;
		root = new double[len];
		for (int i = 0; i < X.len; i++) {
				root[i] = X.root[i];
		}
		return *this;
	}

	//BINARY ADDITION
	vect operator + (const vect& X) {
		if (len != X.len) {
			cout << "Failed to add two vectors of different length.\n";
			system("pause");
			abort();
		}
		vect O(X.len);
		for (int i = 0; i < X.len; i++) {
			O.root[i] = root[i] + X.root[i];
		}

		return O; 
	}

	//BINARY SUBSTRACTION
	vect operator - (const vect& X) {
		if (len != X.len) {
			cout << "Failed to substract two vectors of different length.\n";
			system("pause");
			abort();
		}
		vect O(X.len);
		for (int i = 0; i < X.len; i++) {
			O.root[i] =root[i] - X.root[i];
		}
		return O; 
	}

	//UNARY SUBSTRACTION
	vect operator - () {
		vect O(len);
		for (int i = 0; i < len; i++) {
			O.root[i] = -root[i];
		}

		return O; 
	}

	//VECTOR - DOUBLE OPERATORS

	vect operator * (double a) {
		vect O(*this);
		for (int i = 0; i < len; i++) {
			O.root[i] *= a;
		}
		return O;
	}
	friend vect operator *(double a, vect X) {
		return X * a;
	}

	vect operator / (double a) {
		if (a == 0) {
			cout << "Error dividing a vector by zero\n";
			system("pause");
			abort();
		}
		vect O(*this);
		for (int i = 0; i < len; i++) {
			O.root[i] /= a;
		}
		return O;
	}
	friend vect operator /(double a, vect X) {
		return X * a;
	}

	//BOOLEAN OPERATORS
	bool  operator == (const vect& X) {
		if (len != X.len)
			return false;
		for (int i = 0; i < len; i++) {
			if (root[i] != X.root[i]) {
				return false;
			}
		}
		return true;

	}

	bool  operator != (const vect& X) {
		return !(*this==X);
	}

	//STREAM OPERATORS

	friend ostream& operator << (ostream& out, const vect& X) {
		for (int i = 0; i < X.len; i++) {
			cout << X.root[i] << " ";
		}
		cout << "\n";
		return out;
	}

	void printVect() {
		for (int i = 0; i < this->len; i++) {
			cout << root[i] << " ";
		}
		cout << "\n";
	}

	vect Floor() {
		vect O(len);
		for (int i = 0; i < len; i++) {
			O.root[i] = floor(root[i]);
		}
		return O;
	}
	
	double Norma_E() {
		double x = 0;
		for (int i = 0; i < len; i++) {
			x += pow(root[i], 2);
		}

		return sqrt(x);
	}
	
	double scalMult(const vect& X) {
		double x = 0;
		if (len != X.len) {
			cout << "Failed to scalar multiply two vectors of different length.\n";
			system("pause");
			abort();
		}

		for (int i = 0; i < X.len; i++) {
			x += root[i] * X.root[i];
		}

		return x;
	}

	vect vectMult(const vect& X) {
		if (len != X.len || X.len != 3) {
			cout << "Failed to vector multiply two vectors of length other than 3.\n";
			system("pause");
			abort();
		}
		vect O(X.len);
		O.root[0] = root[1] * X.root[2] - root[2] * X.root[1];
		O.root[1] = root[2] * X.root[0] - root[0] * X.root[2];
		O.root[2] = root[0] * X.root[1] - root[1] * X.root[0];


		return O;
	}

	vect ort() {
		vect O(*this);
		double a = Norma_E();
		return O/a;
	}

	double mixMult(vect B, vect C) {
		double x = 0;
		x = (B.vectMult(C)).scalMult(*this);

		return x;
	}

	double angle(vect A) {
		double x = 0;
		x = acos(scalMult(A) / (Norma_E() * A.Norma_E()));

		return x;
	}

	double Cos(vect A) {
		double x = 0;
		x = scalMult(A) / (Norma_E() * A.Norma_E());

		return x;
	}

	void removeRoot() {
		if (root != 0)
			delete[] root;
	}
	~vect() {
		if(root!=0)
			delete[] root;
	}
};


#endif // Linear_Algebra_3d


#pragma once
