#ifndef AI_move
#define AI_move

#include "Dependencies/Matrix.h"



//depth tree of possible movements not taking into account the appearing tiles
//taking the number of merged tiles as benefit
class Decision_Tree {
private:
	Decision_Tree* possible;
	int* benefit;
	int type;
public:

	Decision_Tree() {
		possible = 0;
		benefit = 0;
		type = 0;
	}
	//first fill out the next movements
	Decision_Tree(const matrix& t, int depth, int typ) {
		Init(t, depth, typ);
	}
	void Init(const matrix& t, int depth, int typ) {
		deconstruct(this);
		type = typ;
		possible = new Decision_Tree[4];
		benefit = new int[4]{ 0 };
		matrix temp;

		temp = Right(t, 0);
		if (benefit[0] >= 0)
			possible[0].Init(temp, 1, depth, typ);

		temp = Up(t, 1);
		if (benefit[1] >= 0)
			possible[1].Init(temp, 1, depth, typ);

		temp = Left(t, 2);
		if (benefit[2] >= 0)
			possible[2].Init(temp, 1, depth, typ);

		temp = Down(t, 3);
		if (benefit[3] >= 0)
			possible[3].Init(temp, 1, depth, typ);

	}

	void Init(const matrix& t, int current, int end, int typ) {
		deconstruct(this);
		if (current > end)
			return;
		type = typ;
		possible = new Decision_Tree[4];
		benefit = new int[4]{ 0 };

		matrix temp;

		temp = Right(t, 0);
		if (benefit[0] >= 0)
			possible[0].Init(temp, current + 1, end, typ);

		temp = Up(t, 1);
		if (benefit[1] >= 0)
			possible[1].Init(temp, current + 1, end, typ);

		temp = Left(t, 2);
		if (benefit[2] >= 0)
			possible[2].Init(temp, current + 1, end, typ);

		temp = Down(t, 3);
		if (benefit[3] >= 0)
			possible[3].Init(temp, current + 1, end, typ);
		
	}

	int Calculate() {
		// if the branch is uninitialized then it should return 0
		//This means we should return already at this point
		if (possible == 0)
			return 0;
		for (int i = 0; i < 4; i++) {
			if (benefit[i] < 0)
				continue;
			benefit[i] += possible[i].Calculate();
		}
		return getMaxBenefit();
	}

	//used to instantly calculate and output then best movement based on the object data
	int getMovement() {
		Calculate();
		int max = 0;
		int ret = 0;
		for (int i = 0; i < 4; i++) {
			if (benefit[i] > max) {
				max = benefit[i];
				ret = i;
			}
		}
		if (max == 0)
			ret = rand() % 4;
		return ret + 1;
	}

	//used to output then best movement based on the max element of the array
	int getMovement(int* X) {
		int max = 0;
		int ret = 0;
		for (int i = 0; i < 4; i++) {
			if (X[i] > max) {
				max = X[i];
				ret = i;
			}
		}
		if (max == 0)
			ret = rand() % 4;
		return ret + 1;
	}

	//used to output then best movement based on the max element of the array and the matrix of the playground
	int getMovement(const matrix& t, int* X) {
		int max = 0;
		int add_check[4]{ 0 };
		int ret;
		//finding max el to compare with
		for (int i = 0; i < 4; i++) {
			if (X[i] > max) {
				max = X[i];
				ret = i;
			}
		}
		//if max == 0 we can already return
		if (max == 0)
			return rand() % 4 + 1;

		//then the comparing cycle after which we get the movements that should be reviewed
		for (int i = 0; i < 4; i++) {
			if (X[ret] - X[i] < 2) {
				add_check[i] = 1;
			}
		}


		Decision_Tree temp(t, 1, 4);
		temp.Calculate();
		X = temp.getBenefit();
		max = 0;
		//finding max el  the 
		for (int i = 0; i < 4; i++) {
			if (add_check[i] == 0)
				continue;
			if (X[i] > max) {
				max = X[i];
				ret = i;
			}
		}

		return ret + 1;
	}


	int getMaxBenefit() {
		int max = 0;
		for (int i = 0; i < 4; i++) {
			if (benefit[i] > max) {
				max = benefit[i];
			}
		}
		return max;
	}

	int* getBenefit() {
		
		return benefit;
	}

	int Decide() {
		Calculate();
		return getMovement();
	}

	~Decision_Tree() {
		deconstruct(this);
	}
	void deconstruct(Decision_Tree* t) {

		if (t == 0)
			return;
		

		if (t->possible == 0)
			return;

		deconstruct(t->possible[0].possible);
		deconstruct(t->possible[1].possible);
		deconstruct(t->possible[2].possible);
		deconstruct(t->possible[3].possible);

		delete[] t->benefit;

		return;
	}


	//MOVEMENTS
	matrix Right(matrix Tiles, int m);
	matrix Up(matrix Tiles, int m);
	matrix Left(matrix Tiles, int m);
	matrix Down(matrix Tiles, int m);

	matrix Set_new_tile(matrix Tiles);

};



class General_Move {

};


#endif // !AI_move


#pragma once
