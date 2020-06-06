#include "AI move.h"









matrix Decision_Tree::Set_new_tile(matrix Tiles) {
	if (type == 0)
		return Tiles;
	int first = rand() % (Tiles.getRow() * Tiles.getRow()), count = 0, define_power = rand() % 100;
	int done_key = 0;
	for (int i = 0; i < Tiles.getRow(); i++) {
		for (int k = 0; k < Tiles.getRow(); k++) {
			if (count == first && Tiles[i][k] == 0) {
				if (type == 1) {
					Tiles.Write(i, k, (rand()%99+1)/double(100));
				}
				if (type == 2||type==3||type==4) {
					if (define_power < 90)
						Tiles.Write(i, k, pow(2, 1));
					else
						Tiles.Write(i, k, pow(2, 2));
				}

				return Tiles;
			}
			else if (Tiles[i][k] == 0) {
				count++;
			}
			if (count != 0 && i == Tiles.getRow() - 1 && k == Tiles.getRow() - 1) {
				i = -1; k = -1; break;
			}
		}
	}

	return Tiles;

}






//MOVEMENTS

matrix Decision_Tree::Right(matrix Tiles, int m) {
	bool change_key = 0;
	int store_free_space;
	for (int i = 0; i < Tiles.getRow(); i++) {
		for (int k = Tiles.getRow() - 2; k >= 0; k--) {
			store_free_space = -1;
			if (Tiles[i][k] != 0) {
				for (int to_place = k + 1; to_place < Tiles.getRow(); to_place++) {
					if (Tiles[i][k] == Tiles[i][to_place] || Tiles[i][to_place] == 0) {
						store_free_space = to_place;
					}
					else break;
				}
				if (store_free_space != -1) {
					change_key = 1;
					if (Tiles[i][store_free_space] == 0)
						Tiles.Write(i, store_free_space, (Tiles[i][k] + Tiles[i][store_free_space]));
					else {
						if (type == 4)
							benefit[m] += Tiles[i][k] + Tiles[i][store_free_space];
						else if(type!=3)
							benefit[m]++;
						else 
							benefit[m]+=log(Tiles[i][k])/log(2)-1;

						Tiles.Write(i, store_free_space, -(Tiles[i][k] + Tiles[i][store_free_space])); 
					}

					Tiles.Write(i, k, 0);
				}

			}
		}
	}

	if (!change_key) {
		benefit[m] = -1;
	}
	Tiles = Tiles.doAbs();

	

	Tiles = Set_new_tile(Tiles);
	return Tiles;
}

matrix Decision_Tree::Up(matrix Tiles, int m) {
	bool change_key = 0;
	int store_free_space;
	for (int k = 0; k < Tiles.getRow(); k++) {
		for (int i = 1; i < Tiles.getRow(); i++) {
			store_free_space = -1;
			if (Tiles[i][k] != 0) {
				for (int to_place = i - 1; to_place >= 0; to_place--) {
					if (Tiles[i][k] == Tiles[to_place][k] || Tiles[to_place][k] == 0) {
						store_free_space = to_place;
					}
					else break;
				}
				if (store_free_space != -1) {
					change_key = 1;
					if (Tiles[store_free_space][k] == 0)
						Tiles.Write(store_free_space, k, (Tiles[i][k] + Tiles[store_free_space][k]));
					else {
						if (type == 4)
							benefit[m] += Tiles[i][k] + Tiles[i][store_free_space];
						else if (type != 3)
							benefit[m]++;
						else
							benefit[m] += log(Tiles[i][k]) / log(2) - 1;

						Tiles.Write(store_free_space, k, -(Tiles[i][k] + Tiles[store_free_space][k]));
					}

					Tiles.Write(i, k, 0);
				}

			}
		}
	}
	
	if (!change_key) {
		benefit[m] = -1;
	}
	Tiles = Tiles.doAbs();

	

	Tiles = Set_new_tile(Tiles);
	return Tiles;

}

matrix Decision_Tree::Left(matrix Tiles, int m) {
	bool change_key = 0;
	int store_free_space;

	for (int i = 0; i < Tiles.getRow(); i++) {
		for (int k = 1; k < Tiles.getRow(); k++) {
			store_free_space = -1;
			if (Tiles[i][k] != 0) {
				for (int to_place = k - 1; to_place >= 0; to_place--) {
					if (Tiles[i][k] == Tiles[i][to_place] || Tiles[i][to_place] == 0) {
						store_free_space = to_place;
					}
					else break;
				}
				if (store_free_space != -1) {
					change_key = 1;
					if (Tiles[i][store_free_space] == 0)
						Tiles.Write(i, store_free_space, (Tiles[i][k] + Tiles[i][store_free_space]));
					else {
						if (type == 4)
							benefit[m] += Tiles[i][k] + Tiles[i][store_free_space];
						else if (type != 3)
							benefit[m]++;
						else
							benefit[m] += log(Tiles[i][k]) / log(2) - 1;

						Tiles.Write(i, store_free_space, -(Tiles[i][k] + Tiles[i][store_free_space]));
					}
					Tiles.Write(i, k, 0);
				}

			}
		}
	}	
	

	if (!change_key) {
		benefit[m] = -1;
	}
	Tiles = Tiles.doAbs();

	

	Tiles = Set_new_tile(Tiles);
	return Tiles;

}

matrix Decision_Tree::Down(matrix Tiles, int m) {
	bool change_key = 0;
	int store_free_space;
	
	for (int k = 0; k < Tiles.getRow(); k++) {
		for (int i = Tiles.getRow() - 2; i >= 0; i--) {
			store_free_space = -1;
			if (Tiles[i][k] != 0) {
				for (int to_place = i + 1; to_place < Tiles.getRow(); to_place++) {
					if (Tiles[i][k] == Tiles[to_place][k] || Tiles[to_place][k] == 0) {
						store_free_space = to_place;
					}
					else break;
				}
				if (store_free_space != -1) {
					change_key = 1;
					if (Tiles[store_free_space][k] == 0)
						Tiles.Write(store_free_space, k, (Tiles[i][k] + Tiles[store_free_space][k]));
					else {
						if (type == 4)
							benefit[m] += Tiles[i][k] + Tiles[i][store_free_space];
						else if (type != 3)
							benefit[m]++;
						else
							benefit[m] += log(Tiles[i][k]) / log(2) - 1;

						Tiles.Write(store_free_space, k, -(Tiles[i][k] + Tiles[store_free_space][k]));
					}
					Tiles.Write(i, k, 0);
				}

			}
		}
	}
	

	if (!change_key) {
		benefit[m] = -1;
	}
	Tiles = Tiles.doAbs();

	
	Tiles = Set_new_tile(Tiles);
	return Tiles;

}

