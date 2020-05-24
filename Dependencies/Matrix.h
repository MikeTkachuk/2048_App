#ifndef Matrix
#define Matrix
#include <iostream>
#include <cmath>
#include "Linear Algebra 3d.h"

using namespace std;



class matrix {
private:
	double** root;
	int row;
	int col;

public:
	matrix() {
		root = 0;
		row = 0;
		col = 0;
	}

	//RANDOM CONSTRUCTOR

	//create a null matrix
	matrix(int a, int b) {
		root = 0;
		Init(a, b);
	}
	//create a null matrix
	void Init(int a, int b) {
		if (root != 0)
			delete_root();
		row = a;
		col = b;
		root = new double* [a];
		for (int i = 0; i < a; i++) {
			root[i] = new double[b] {0};
		}
	}

	//create a  n - one, r - random, s - special for NT weights, zero by default matrix
	matrix(int a, int b, char par) {  
		root = 0;
		Init(a, b, par);
		
	}
	//create a  n - one, r - random, s - special for NT weights, zero by default matrix
	void Init(int a, int b, char par) {  
		if (root != 0)
			delete_root();

		row = a;
		col = b;
		double maxW = (1 / sqrt(5)) * 1000;		//(max allowed weight)*1000
		int simple_rand = 5;					//whole part of the simple rand
		int div = 1;							//divisor of the simple rand
		switch (par) {

		case 's':

			root = new double* [a];
			for (int i = 0; i < a; i++) {
				root[i] = new double[b] {0};
				for (int k = 0; k < b; k++)
					root[i][k] = (double)(rand() % (int)(2 * maxW) - maxW) / (double)1000;
			}
			break;

		case 'r':
			root = new double* [a];
			for (int i = 0; i < a; i++) {
				root[i] = new double[b];
				for (int k = 0; k < b; k++)
					root[i][k] = (rand() % (2 * simple_rand) - simple_rand) / (double)div;
			}
			break;
		case 'n':
			root = new double* [a];
			for (int i = 0; i < a; i++) {
				root[i] = new double[b];
				for (int k = 0; k < b; k++) {
					root[i][k] = 1;
				}
			}
			break;
		default:
			root = new double* [a];
			for (int i = 0; i < a; i++) {
				root[i] = new double[b] {0};
			}
			break;
		}
	}  

	//CONSTRUCTOR BY THE GIVEN VALUES

	matrix(const matrix& t) {
		root = 0;
		Init(t);
	}
	void Init(const matrix& t) {
		if (root != 0) {
			delete_root();
		}
		row = t.row;
		col = t.col;
		if (t.root != 0) {
			root = new double* [row];
			for (int i = 0; i < row; i++) {
				root[i] = new double[col];
				for (int k = 0; k < col; k++) {
					root[i][k] = t.root[i][k];
				}
			}
		}
		else
			root = 0;
	}

	 //to init ROWS from three 3d vectors
	matrix( vect a,  vect b,  vect c) {
		Init(a, b, c);
	}
	//to init ROWS from three 3d vectors
	void Init(vect a, vect b, vect c) {
		if (root != 0) {
			delete_root();
		}
		row = 3;
		col = 3;
		root = new double* [row];
		
			
		root[0] = new double[col];
		for (int k = 0; k < col; k++) {
			root[0][k] = a[k];	
		}
		root[1] = new double[col];
		for (int k = 0; k < col; k++) {
			root[1][k] = b[k];
		}
		root[2] = new double[col];
		for (int k = 0; k < col; k++) {
			root[2][k] = c[k];
		}


	}


	matrix(int a, int b, double** X) {
		root = 0;
		Init(a, b, X);
	}
	void Init(int a, int b, double** X) {
		if (root != 0)
			delete_root();
		row = a;
		col = b;
		root = new double* [a];
		for (int i = 0; i < row; i++) {
			root[i] = new double[col];
			for (int k = 0; k <col; k++) {
				root[i][k] = X[i][k];
			}
		}
	}

	matrix(int a, int b, int** X) {
		root = 0;
		Init(a, b, X);
	}
	void Init(int a, int b, int** X) {
		if (root != 0)
			delete_root();
		row = a;
		col = b;
		root = new double* [a];
		for (int i = 0; i < row; i++) {
			root[i] = new double[col];
			for (int k = 0; k < col; k++) {
				root[i][k] = X[i][k];
			}
		}
	}

	//RETURN FUNCTIONS

	int getRow() {
		return row;
	}
	int getCol() {
		return col;
	}

	vect operator[](int a) {
		vect O(col,root[a]);
		return O;
	}

	double getMax_el() {
		if (root == 0 || row == 0 || col == 0) {
			cout << "Can't process an empty matrix.";
			system("pause");
			return -INFINITY;
		}
		double max = -INFINITY;
		
		for (int i = 0; i < row; i++) {
			for (int k = 0; k < col; k++) {
				if (root[i][k] > max) {
					max = root[i][k];
				}
			}
		}

		return max;
	}

	//FAST REFERENCE FUNCTIONS

	void Write(int i, int k, double val){
		if (root != 0) {
			root[i][k] = val;
		}
	}
	void Write(int i, vect val) {
		if (root != 0) {
			for(int r=0;r<row;r++)
				root[i][r] = val[r];
		}
	}

	//ASSIGNMENT

	matrix& operator = (const matrix& X) {
		if (root!=0) {
			this->delete_root();
		}
		row = X.row;
		col = X.col;
		root = new double* [X.row];
		for (int i = 0; i < X.row; i++) {
			root[i] = new double[X.col];
			for (int k = 0; k < X.col; k++) {
				root[i][k] = X.root[i][k];
			}
		}
		return *this;
	}

	//BOOL OPERATORS

	bool operator == (matrix X) {
		if (row != X.row || col != X.col)
			return false;
		for (int i = 0; i < row; i++) {
			for (int k = 0; k < col; k++) {
				if (root[i][k] != X[i][k]) {
					return false;
				}
			}
		}
		return true;
	}

	bool operator !=(matrix X) {
		return !(*this == X);
	}

	//BINARY PLUS

	matrix operator + (const matrix& X){

		matrix O;
		

		if (row != X.row || col != X.col) {
			cout << "Error adding matrixes of different size.";
			system("pause");
			return O;
		}
		if (root == 0 || X.root == 0 || row == 0 || col == 0)
			return O;

		double**temp = new double*[X.row];
		
		for (int i = 0; i < X.row; i++) {
			temp[i] = new double[X.col];
			for (int k = 0; k < X.col; k++) {
				temp[i][k] = root[i][k] + X.root[i][k];
			}
		}
		O.Init(X.row, X.col, temp);

		for (int i = 0; i < row; i++)
			delete[] temp[i];
		delete[] temp;

		return O;

	}

	//CORE UNARY MINUS
	friend  matrix operator - (const matrix& X) {
		matrix O;
		if (X.root == 0||X.row==0||X.col==0)
			return O;
		double** temp = new double* [X.row];
		
		for (int i = 0; i < X.row; i++) {
			temp[i] = new double[X.col];
			for (int k = 0; k < X.col; k++) {
				temp[i][k] =- X.root[i][k];
			}
		}
		O.Init(X.row, X.col, temp);

		for (int i = 0; i < X.row; i++)
			delete[] temp[i];
		delete[] temp;

		return O;
	}

	//BINARY MINUS
	matrix operator - (const matrix& X) {

		matrix O = -X + *this;

		return O;
	}

	//BINARY MULTIPLICATION

	matrix operator * (const matrix& X) {
		matrix O;
		
		if (col != X.row) {	
			cout << "Error multiplying matrixes of the wrong size.";
			system("pause");
			return O;
		}
		if (root == 0 || X.root == 0 || X.row == 0 || X.col == 0 || row==0)
			return O;
		double** temp = new double* [row];
		
		for (int i = 0; i < row; i++) {
			temp[i] = new double[X.col]{ 0 };
			for (int k = 0; k < X.col; k++) {
				for (int p = 0; p < X.row; p++) {
					temp[i][k] += root[i][p] * X.root[p][k];

				}
			}
		}
		O.Init(row, X.col, temp);

		for (int i = 0; i < row; i++)
			delete[] temp[i];
		delete[] temp;

		return O;

	}

	vect operator *(vect X) {
		if (col != X.getLen()) {
			cout << "Error multiplying the matrix by vector.\n";
			system("pause");
			abort();
		}
		double* temp = new double[row] {0};
		for (int i = 0; i < row; i++) {
			for (int k = 0; k < col; k++) {
				temp[i] += root[i][k] * X[k];
			}
		}
		vect O(row,temp);

		delete[] temp;
		
		return O;
	}

	friend vect operator * (vect A, matrix B) {
		if (B.row != A.getLen()) {
			cout << "Error multiplying the matrix by vector.\n";
			system("pause");
			abort();
		}
		double* temp = new double[B.col] {0};
		
		for (int k = 0; k < B.col; k++) {
			for (int i = 0; i < B.row; i++) {
				temp[i] += B.root[i][k] * A[i];
			}
		}
		vect O(B.col, temp);

		delete[] temp;

		return O;
	}

    matrix operator * (double a) {
		matrix O;
		double** temp = new double* [row];
	
		for (int i = 0; i < row; i++) {
			temp[i] = new double[col];
			for (int k = 0; k < col; k++) {
				temp[i][k] = a*root[i][k];
			}
		}

		for (int i = 0; i < row; i++)
			delete[] temp[i];
		delete[] temp;

		O.Init(row, col, temp);
		return O;
	}

	friend matrix operator * (double a,  matrix& X) {
		matrix O = X * a;
		return O;
	}

	//STANDART MATRIX FUNCTIONS

	matrix Trans() {
		matrix O;
		if (root == 0)
			return O;
		double** temp = new double* [col];
		for (int i = 0; i < col; i++) {
			temp[i] = new double[row];
			for (int k = 0; k < row; k++) {
				temp[i][k] = root[k][i];
			}
		}
		O.Init(col, row, temp);

		for (int i = 0; i < row; i++)
			delete[] temp[i];
		delete[] temp;

		return O;

	}

	friend matrix Trans(matrix X) {
		return X.Trans();
	}

	matrix toPow(int x) {
		matrix O;
		if (root == 0 )
			return O;
		if (col != row) {
			cout << "Error multiplying matrixes of the wrong size.";
			system("pause");
			return O;
		}
		if (x <= 0) {
			cout << "Error raising matrix to the non-natural number.";
			system("pause");
			return O;
		}
		O.Init(*this);

		for (int i = 1; i < x; i++) {
			O = O * *this;
		}
		return O;

	}

	double det() {

		matrix X(*this);
		double D = 1;

		if (X.row != X.col) {
			cout << "Can't compute the determinant of a non-square matrix.";
			system("pause");
			return 0;
		}

		if (X.root == 0) {
			cout << "Can't process an empty matrix.";
			system("pause");
			return 0;
		}
		int permetations = 0;
		double* swap;
		int find_nonzero;
		double store_val;
		for (int i = 0; i <X.row; i++) {  //starting from the left top
			find_nonzero = i;
			while (X.root[find_nonzero][i] == 0) { //looking for the first nonzero el from the bottom of the matrix
				find_nonzero++;
				if (find_nonzero >X.row-1) //if none found then det==0
					return 0;
			}
			if (find_nonzero != i) {
				swap = X.root[find_nonzero];
				X.root[find_nonzero] = X.root[i];
				X.root[i] = swap;
				permetations++;
			}
			D *= X.root[i][i];
			for (int make_z = i+1; make_z < X.row; make_z++) {
				store_val = X.root[make_z][i];
				if (store_val == 0)
					continue;
				X.Minus(X.root[make_z], X.Mult(X.root[i],store_val/X.root[i][i],X.row), X.row);
				X.Mult(X.root[i], store_val, X.row);
			}
		}
		if (permetations % 2 != 0)
			D = -D;
		return D;		
	}

	friend double det(matrix X) {
		return X.det();
	}

	matrix el_Mult(const matrix& X) {
		matrix O;
		if (row != X.row || col != X.col) {
			cout << "Error multiplying corresponding elements when matrixes are different in size.";
			system("pause");
			return O;
		}
		if (root == 0 || X.root == 0||row==0||col==0)
			return O;

		double** temp = new double* [X.row];

		for (int i = 0; i < X.row; i++) {
			temp[i] = new double[X.col];
			for (int k = 0; k < X.col; k++) {
				temp[i][k] = root[i][k] * X.root[i][k];
			}
		}
		O.Init(X.row, X.col, temp);

		for (int i = 0; i < row; i++)
			delete[] temp[i];
		delete[] temp;

		return O;
	}

	matrix doSigma() {
		matrix O;
		if (root == 0||row==0||col==0) {
			cout << "Can't process an empty matrix.";
			system("pause");
			return O;
		}

		double** temp = new double* [row];

		for (int i = 0; i < row; i++) {
			temp[i] = new double[col];
			for (int k = 0; k < col; k++) {
				temp[i][k] = Sigma(root[i][k]);
			}
		}
		O.Init(row, col, temp);

		for (int i = 0; i < row; i++)
			delete[] temp[i];
		delete[] temp;

		return O;
	}

	matrix doAbs() {
		matrix O;
		if (root == 0 || row == 0 || col == 0) {
			cout << "Can't process an empty matrix.";
			system("pause");
			return O;
		}

		double** temp = new double* [row];

		for (int i = 0; i < row; i++) {
			temp[i] = new double[col];
			for (int k = 0; k < col; k++) {
				temp[i][k] = abs(root[i][k]);
			}
		}
		O.Init(row, col, temp);

		for (int i = 0; i < row; i++)
			delete[] temp[i];
		delete[] temp;

		return O;
	}

	matrix makeBool(){
		matrix O;
		if (root == 0 || row == 0 || col == 0) {
			cout << "Can't process an empty matrix.";
			system("pause");
			return O;
		}

		double** temp = new double* [row];

		for (int i = 0; i < row; i++) {
			temp[i] = new double[col];
			for (int k = 0; k < col; k++) {
				temp[i][k] = (bool)root[i][k];
			}
		}
		O.Init(row, col, temp);

		for (int i = 0; i < row; i++)
			delete[] temp[i];
		delete[] temp;

		return O;

	}

	//CONVERSION OPERATOR

	operator double** () {
		double** temp = new double* [row];
		for (int i = 0; i < row; i++) {
			temp[i] = new double[col];
			for (int k = 0; k < col; k++) {
				temp[i][k] = root[i][k];
			}
		}
		return temp;
	}

	//STREAM OPERATORS

	friend ostream& operator << (ostream& out,  matrix X) {
		int max = 0;
		int sym;
		for (int i = 0; i < X.row; i++) {
			for (int k = 0; k < X.col; k++) {
				sym = X.number_of_symbols(X.root[i][k]);
				if (sym > max) {
					max = sym;
				}
			}
		}
		max += 2;
		for (int i = 0; i < X.row; i++) {
			for (int k = 0; k < X.col; k++) {
				
				cout << setprecision(5) << X.root[i][k];
				sym = X.number_of_symbols(X.root[i][k]);
				for (int space = 0; space < max - sym; space++)
					cout << " ";
			}
			cout << "\n";
		}
		cout << "\n";


		return out;
	}


	friend istream& operator >> (istream& in, matrix& X) {
		if (X.root != 0) {
			X.delete_root();
		}
		cout << "Please, enter the matrix dimentions: \n Rows: ";
		cin >> X.row;
		if (X.row < 0) {
			cout << "Invalid row count, setting the abs val\n";
			X.row = abs(X.row);
		}

		cout << "\n Cols: ";
		cin >> X.col;
		if (X.col < 0) {
			cout << "Invalid col count, setting the abs val\n";
			X.col = abs(X.col);
		}
		if (X.row == 0 || X.col == 0) {
			X.root = 0;
			return in;
		}

		cout << "\nStart inputting the matrix:\n";
		double** temp = new double* [X.row];
		for (int i = 0; i < X.row; i++) {
			temp[i] = new double[X.col];
			for (int k = 0; k < X.col; k++) {
				cin >> temp[i][k];
			}
		}


		X.Init(X.row,X.col,temp);

		for (int i = 0; i < X.row; i++)
			delete[] temp[i];
		delete[] temp;

		return in;
	}

	//DECONSTRUCTOR

	void delete_root() {
		 if (root != 0) {
			 for (int i = 0; i < row; i++)
				 delete[] root[i];
			 delete root;
		 }
	}

	~matrix() {
		if (root != 0) {
			for (int i = 0; i < row;i++)
				delete[] root[i];
			delete[] root;
		}
	}

	/************ OPTIMISATION FUNCS ************/

	double Sigma(double x) {
		return 1 / (1 + pow(2.7182818284590452353602874713526624977572470936999595749, -x));
	}

	double* Minus(double* a, double* b, int N) {

		for (int i = 0; i < N;i++) {
			a[i] -= b[i];
		}

		return a;
	}
	double* Mult(double* a, double b, int N) {
		for (int i = 0; i < N; i++) {
			a[i] *= b;
		}

		return a;
	}

	int number_of_symbols(double x){
		 double t = (int)abs(x), a = abs(x) - t;
		int count1 = 1, count2=0;
		while (t > 9) {
			t /= 10;
			count1++;
		}
		if (x == (int)x) {
			if (x == 0)
				return 1;
			if (x < 0)
				return count1 + 1;
			else return count1;
		}
		else {
			if (x < 0)
				return count1 + 3;
			else return count1 + 4;
		}

	}

	 

};






#endif // Matrix
#pragma once
