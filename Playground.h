#ifndef PlayGround
#define PlayGround




#include <SFML/Graphics.hpp>
#include "Draw_Sh.h"
#include "Dependencies/Matrix.h"
#include <string>
#include <Windows.h>

using namespace sf;




class Playground
{
private:
	int tile_count; //the number of tiles placed along one side of the playground
	matrix Tiles;
	matrix Movement_Backup;
	matrix Change; //Contains information about the movement process
	bool game_over;
	bool reached_2048;
	bool ai_turned_on;
	bool skip_animation;



	sf::Vector2u size;
	sf::Color color;
	sf::Color Text_Color = setColor_vector(Text_Color, 10, 10, 10, 175);
	sf::Font universal_font;
public:
	Playground() {
		tile_count = 0;
		size = sf::Vector2u(0, 0);
		game_over = 0;
		skip_animation = 0;
	}
	void Init() {
		tile_count = 0;
		size = sf::Vector2u(0, 0);
		game_over = 0;
		ai_turned_on = 0;
		skip_animation = 0;

		if (!universal_font.loadFromFile("Fonts/clearsans-1.00/TTF/ClearSans-Bold.ttf"))
			std::cout << "Error loading font!\n";
	}

	//N-set tile count Size-playground Size when displayed
	Playground(int N, int Size) {
		Init(N, Size);
	}
	//N-set tile count Size-playground Size when displayed
	void Init(int N, int Size) {
		Tiles.Init(N, N);
		Movement_Backup = Tiles;
		Change.Init(N, N);
		game_over = 0;
		reached_2048 = 0;
		ai_turned_on = 0;
		skip_animation = 0;

		tile_count = N;
		size = sf::Vector2u(Size, Size);
		if (!universal_font.loadFromFile("Fonts/clearsans-1.00/TTF/ClearSans-Bold.ttf"))
			std::cout << "Error loading font!\n";

	}

	//N-set tile count Size-playground Size when displayed
	Playground(int N, sf::Vector2u Size) {
		Init(N, Size);
	}
	//N-set tile count Size-playground Size when displayed
	void Init(int N, sf::Vector2u Size) {
		Tiles.Init(N, N);
		Movement_Backup = Tiles;
		Change.Init(N, N);
		game_over = 0;
		reached_2048 = 0;
		ai_turned_on = 0;
		skip_animation = 0;

		tile_count = N;
		size =  Size;
		if (!universal_font.loadFromFile("Fonts/clearsans-1.00/TTF/ClearSans-Bold.ttf"))
			std::cout << "Error loading font!\n";

	}

	void setColor(sf::Color c) {
		color = c;
	}
	void setGameOver(bool g_o) {
		game_over = g_o;
	}
	void setAIstate(bool a_s) {
		ai_turned_on = a_s;
	}
	void changeAIstate() {
		ai_turned_on = !ai_turned_on;
	}
	void setSkip_animation(bool s_a) {
		skip_animation = s_a;
	}

	sf::Color getColor() {
		return color;
	}
	int getTile_count() {
		return tile_count;
	}
	sf::Vector2u getSize() {
		return size;
	}
	matrix getPground() {
		return Tiles;
	}
	bool isGameOver() {
		return game_over;
	}
	bool isWin() {
		return reached_2048;
	}
	bool isAIon() {
		return ai_turned_on;
	}
	bool isSkipping() {
		return skip_animation;
	}

	//Set a random-power tile at the random spare position, return the position
	sf::Vector2i Set_new_tile(int max_power) {
		int first = rand() % (tile_count * tile_count), count = 0;
		int done_key = 0;
		for (int i = 0; i < tile_count; i++) {
			for (int k = 0; k < tile_count; k++) {
				if (count == first && Tiles[i][k] == 0) {
					Tiles.Write(i, k, pow(2, rand() % max_power + 1));
					return sf::Vector2i(i, k);
				}
				else if (Tiles[i][k] == 0) {
					count++;
				}
				if (count != 0 && i == tile_count - 1 && k == tile_count - 1) {
					i = -1; k = -1; break;
				}
			}
		}

		return sf::Vector2i(-1, -1);

	}


	//Set a 1 or 2 power of "2" tile at the random spare position, return the position. The probability is 1:9 (1st pow is more likely) 
	sf::Vector2i Set_new_tile() {
		int first = rand() % (tile_count * tile_count), count = 0, define_power=rand()%100;
		int done_key = 0;
		for (int i = 0; i < tile_count; i++) {
			for (int k = 0; k < tile_count; k++) {
				if (count == first && Tiles[i][k] == 0) {
					if(define_power<90)
						Tiles.Write(i, k, pow(2, 1));
					else
						Tiles.Write(i, k, pow(2, 2));
					return sf::Vector2i(i, k);
				}
				else if (Tiles[i][k] == 0) {
					count++;
				}
				if (count != 0 && i == tile_count - 1 && k == tile_count - 1) {
					i = -1; k = -1; break;
				}
			}
		}

		return sf::Vector2i(-1, -1);

	}

	//Reset tiles data
	void Reset_Playground() {
		Tiles.Init(tile_count, tile_count);
		Movement_Backup.Init(tile_count, tile_count);
		Change.Init(tile_count, tile_count);
		game_over = 0;
		reached_2048 = 0;
	}

	//matrix transformation with the given movement:
	//from the right and counter-clockwise (1-right,2-top,3-left,4-bottom)
	void Movement( sf::RenderWindow& window, int movement_type) {
		if (game_over||reached_2048)
			return;

		matrix store_Tiles = Tiles;
		
		int store_free_space;
		bool change_key = 0;
		switch (movement_type){
		case 1: {
			//RIGHT
			//checking top to bottom, right to left
			for (int i = 0; i < tile_count; i++) {
				for (int k = tile_count - 2; k >= 0; k--) {
					store_free_space = -1;
					if (Tiles[i][k] != 0) {
						for (int to_place = k + 1; to_place < tile_count; to_place++) {
							if (Tiles[i][k] == Tiles[i][to_place] || Tiles[i][to_place] == 0) {
								store_free_space = to_place;
							}
							else break;
						}
						if (store_free_space != -1) {
							change_key = 1;
							if(Tiles[i][store_free_space]==0)
								Tiles.Write(i, store_free_space, (Tiles[i][k] + Tiles[i][store_free_space]));
							else Tiles.Write(i, store_free_space, -(Tiles[i][k] + Tiles[i][store_free_space]));
							
								Change.Write(i, k, abs(store_free_space - k));
						
							Tiles.Write(i, k, 0);
						}

					}
				}
			}

			break;
		}
		case 2: {
			//UP
			//checking top to bottom, left to right
			for (int k = 0; k < tile_count; k++) {
				for (int i = 1; i<tile_count; i++) {
					store_free_space = -1;
					if (Tiles[i][k] != 0) {
						for (int to_place = i-1; to_place >=0; to_place--) {
							if (Tiles[i][k] == Tiles[to_place][k] || Tiles[to_place][k] == 0) {
								store_free_space = to_place;
							}
							else break;
						}
						if (store_free_space != -1) {
							change_key = 1;
							if(Tiles[store_free_space][k]==0)
								Tiles.Write(store_free_space, k, (Tiles[i][k] + Tiles[store_free_space][k]));
							else Tiles.Write(store_free_space, k, -(Tiles[i][k] + Tiles[store_free_space][k]));
							
								Change.Write(i, k, abs(i - store_free_space));

							Tiles.Write(i, k, 0);
						}

					}
				}
			}

			break;
		}
		case 3: {
			//LEFT
			//checking top to bottom, left to right
			for (int i = 0; i < tile_count; i++) {
				for (int k = 1; k <tile_count; k++) {
					store_free_space = -1;
					if (Tiles[i][k] != 0) {
						for (int to_place = k-1; to_place >=0; to_place--) {
							if (Tiles[i][k] == Tiles[i][to_place] || Tiles[i][to_place] == 0) {
								store_free_space = to_place;
							}
							else break;
						}
						if (store_free_space != -1) {
							change_key = 1;
							if(Tiles[i][store_free_space]==0)
								Tiles.Write(i, store_free_space, (Tiles[i][k] + Tiles[i][store_free_space]));
							else Tiles.Write(i, store_free_space, -(Tiles[i][k] + Tiles[i][store_free_space]));
							
								Change.Write(i, k, abs(k - store_free_space));

							Tiles.Write(i, k, 0);
						}

					}
				}
			}

			break;
		}
		case 4: {
			//DOWN
			//checking bottom to top, left to right
			for (int k = 0; k < tile_count; k++) {
				for (int i = tile_count - 2; i >= 0; i--) {
					store_free_space = -1;
					if (Tiles[i][k] != 0) {
						for (int to_place = i + 1; to_place < tile_count; to_place++) {
							if (Tiles[i][k] == Tiles[to_place][k] || Tiles[to_place][k] == 0) {
								store_free_space = to_place;
							}
							else break;
						}
						if (store_free_space != -1) {
							change_key = 1;
							if(Tiles[store_free_space][k]==0)
								Tiles.Write(store_free_space, k, (Tiles[i][k] + Tiles[store_free_space][k]));
							else Tiles.Write(store_free_space, k, -(Tiles[i][k] + Tiles[store_free_space][k]));
							
								Change.Write(i, k, abs(store_free_space - i));

							Tiles.Write(i, k, 0);
						}

					}
				}
			}

			break;
		}
		default:
			break;
		}
		Tiles = Tiles.doAbs();
		
		//Rendering the shift animation
		

		//Setting the new tile
		sf::Vector2i New_tile(-1,-1);
		if (change_key) {
			Movement_Backup = store_Tiles;
			New_tile = Set_new_tile();
		}
		int move_interruption = 0;

		if (New_tile.x > -1 && New_tile.y > -1 ) {		
			move_interruption = Movement_animation(window, movement_type, New_tile);
		}
		
		
		
		game_over = !Check_all_moves();
		
		Change.Init(tile_count, tile_count);
		
		if (game_over) {
			Clear_Pground(window);
			Draw_Pground(window);
			window.display();
			Game_over_animation(window);
		}

		if (Tiles.getMax_el() >= 2048) {
			reached_2048 = 1;
			Clear_Pground(window);
			Draw_Pground(window);
			window.display();
			Win_animation(window);
		}

		if (move_interruption != 0 && !game_over ) {   
			Movement(window, move_interruption);
		}

		

	}

	bool Check_all_moves() {
		matrix Temp(Tiles);

		int store_free_space;
		bool change_key = 0;

		//RIGHT
		//checking top to bottom, right to left
		for (int i = 0; i < tile_count; i++) {
			for (int k = tile_count - 2; k >= 0; k--) {
				store_free_space = -1;
				if (Temp[i][k] != 0) {
					for (int to_place = k + 1; to_place < tile_count; to_place++) {
						if (Temp[i][k] == Temp[i][to_place] || Temp[i][to_place] == 0) {
							store_free_space = to_place;
						}
						else break;
					}
					if (store_free_space != -1) {
						change_key = 1;
						if (Temp[i][store_free_space] == 0)
							Temp.Write(i, store_free_space, (Temp[i][k] + Temp[i][store_free_space]));
						else Temp.Write(i, store_free_space, -(Temp[i][k] + Temp[i][store_free_space]));

						//if (Tiles[i][store_free_space] == Tiles[i][k]) 
						Change.Write(i, k, abs(store_free_space - k));
						//else Change.Write(i, k, abs(store_free_space - k) + 0.5);

						Temp.Write(i, k, 0);
					}

				}
			}
		}


		Temp = Tiles;

		//UP
		//checking top to bottom, left to right
		for (int k = 0; k < tile_count; k++) {
			for (int i = 1; i < tile_count; i++) {
				store_free_space = -1;
				if (Temp[i][k] != 0) {
					for (int to_place = i - 1; to_place >= 0; to_place--) {
						if (Temp[i][k] == Temp[to_place][k] || Temp[to_place][k] == 0) {
							store_free_space = to_place;
						}
						else break;
					}
					if (store_free_space != -1) {
						change_key = 1;
						if (Temp[store_free_space][k] == 0)
							Temp.Write(store_free_space, k, (Temp[i][k] + Temp[store_free_space][k]));
						else Temp.Write(store_free_space, k, -(Temp[i][k] + Temp[store_free_space][k]));

						//if (Tiles[store_free_space][k] == Tiles[i][k])
						Change.Write(i, k, abs(i - store_free_space));
						//else Change.Write(i, k, abs(i - store_free_space) + 0.5);

						Temp.Write(i, k, 0);
					}

				}
			}
		}

		Temp = Tiles;

		//LEFT
		//checking top to bottom, left to right
		for (int i = 0; i < tile_count; i++) {
			for (int k = 1; k < tile_count; k++) {
				store_free_space = -1;
				if (Temp[i][k] != 0) {
					for (int to_place = k - 1; to_place >= 0; to_place--) {
						if (Temp[i][k] == Temp[i][to_place] || Temp[i][to_place] == 0) {
							store_free_space = to_place;
						}
						else break;
					}
					if (store_free_space != -1) {
						change_key = 1;
						if (Temp[i][store_free_space] == 0)
							Temp.Write(i, store_free_space, (Temp[i][k] + Temp[i][store_free_space]));
						else Temp.Write(i, store_free_space, -(Temp[i][k] + Temp[i][store_free_space]));

						//if (Tiles[i][store_free_space] == Tiles[i][k])
						Change.Write(i, k, abs(k - store_free_space));
						//else Change.Write(i, k, abs(k - store_free_space)+0.5);

						Temp.Write(i, k, 0);
					}

				}
			}
		}

		Temp = Tiles;

		//DOWN
		//checking bottom to top, left to right
		for (int k = 0; k < tile_count; k++) {
			for (int i = tile_count - 2; i >= 0; i--) {
				store_free_space = -1;
				if (Temp[i][k] != 0) {
					for (int to_place = i + 1; to_place < tile_count; to_place++) {
						if (Temp[i][k] == Temp[to_place][k] || Temp[to_place][k] == 0) {
							store_free_space = to_place;
						}
						else break;
					}
					if (store_free_space != -1) {
						change_key = 1;
						if (Temp[store_free_space][k] == 0)
							Temp.Write(store_free_space, k, (Temp[i][k] + Temp[store_free_space][k]));
						else Temp.Write(store_free_space, k, -(Temp[i][k] + Temp[store_free_space][k]));

						//if (Tiles[store_free_space][k] == Tiles[i][k])
						Change.Write(i, k, abs(store_free_space - i));
						//else Change.Write(i, k, abs(store_free_space - i) + 0.5);

						Temp.Write(i, k, 0);
					}

				}
			}
		}

		return change_key;

	}

	//Draw tile with parameters
	void Draw_Tile(sf::RenderWindow& window, int tile_value, sf::Vector2f position, double Scale, int transparency) {
		
		double side = (getSize().x / (1.1 * tile_count + 0.1)), space = side * 0.1;
		sf::Vector2f vert(0, space + side), horz(space + side, 0), i_shift(space + side / (double)2, space + side / (double)2);

		//Applying desired size
		Smooth_rect Spare_tile(sf::Vector2f(side*Scale, side*Scale), 10);

		//Loading font
		sf::Text display_value;
		
		display_value.setFont(universal_font);
		display_value.setStyle(sf::Text::Regular);

	
		//Setting the value-specific color and transparency
		sf::Color color = Determine_Color(tile_value);
		color.a = transparency;
		Spare_tile.setColor(color);

		//Setting the given position
		Spare_tile.setPosition((sf::Vector2f)(window.getSize() / (unsigned)2) - (sf::Vector2f)(getSize() / (unsigned)2) + i_shift + vert * (float)position.x + horz * (float)position.y);
		///
		Spare_tile.Draw(window);

		//setting color
		color = Text_Color;
		color.a = transparency/255.0*175;
		display_value.setFillColor(color);
		if (tile_value > 4)
			display_value.setFillColor(sf::Color(249, 246, 242, 255));

		//setting character size
		display_value.setCharacterSize(side / (double)2);
		if (tile_value > 99)
			display_value.setCharacterSize(side / (double)3);
		if (tile_value > 999)
			display_value.setCharacterSize(side / (double)4);
		if (tile_value > 9999)
			display_value.setCharacterSize(side / (double)5);
		if (tile_value > 99999)
			display_value.setCharacterSize(side / (double)6);

		//setting the proper string and position
		display_value.setString(std::to_string((int)tile_value));
		sf::FloatRect bounds = display_value.getGlobalBounds();
		display_value.setOrigin(bounds.width / 2 + bounds.left, bounds.height / 2 + bounds.top);
		display_value.setScale(sf::Vector2f(Scale, Scale));
		display_value.setPosition((sf::Vector2f)(window.getSize() / (unsigned)2) - (sf::Vector2f)(getSize() / (unsigned)2) + i_shift + vert * (float)position.x + horz * (float)position.y);
		///
		window.draw(display_value);
	}
		


	//Shrinked code
	//Draw the playgound in the static position
	void Draw_Pground(sf::RenderWindow& window) {
		//draw the Frame first
		Draw_Frame(window);


		for (int i = 0; i < tile_count; i++) {
			for (int k = 0; k < tile_count; k++) {
				if (Tiles[i][k] != 0) {
					Draw_Tile(window, Tiles[i][k], sf::Vector2f(i,k), 1, 255);					
				}
			}
		}
	}



	//Draw the background frame
	void Draw_Frame(sf::RenderWindow& window) {
		sf::Color color_variations = color;
		

		Smooth_rect Frame((sf::Vector2f)getSize(), (double)10, (sf::Vector2f)(window.getSize() / (unsigned)2));
		Frame.setColor(color_variations);
		Frame.Draw(window);

		color_variations.r *= 1.15;
		color_variations.g *= 1.15;
		color_variations.b *= 1.15;

		double side = (getSize().x / (1.1 * tile_count + 0.1)), space = side * 0.1;
		Smooth_rect Spare_tile(sf::Vector2f(side, side), 10);
		Spare_tile.setColor(color_variations);

		sf::Vector2f horz(0, space + side), vert(space + side, 0), i_shift(space + side / (double)2, space + side / (double)2);

		for (int i = 0; i < tile_count; i++) {
			for (int k = 0; k < tile_count; k++) {
				Spare_tile.setPosition((sf::Vector2f)(window.getSize() / (unsigned)2) - Frame.getSize() / (float)2 + i_shift + vert * (float)i + horz * (float)k);
				Spare_tile.Draw(window);
			}
		}
	}

	//Determine the color of the tile based on its value
	sf::Color Determine_Color(int a) {
		sf::Color c=sf::Color::White;
		switch (a) {
		case 2:
			setColor_vector(c, 238, 228, 218);
			break;
		case 4: 
			setColor_vector(c, 237, 224, 200);
			break;
		case 8:
			setColor_vector(c, 242, 177, 121);
			break;
		case 16:
			setColor_vector(c, 245, 149, 99);
			break;
		case 32:
			setColor_vector(c, 246, 124, 95);
			break;
		case 64:
			setColor_vector(c, 246, 94, 59);
			break;
		case 128: 
			setColor_vector(c, 237, 207, 114);
			break;
		case 256: 
			setColor_vector(c, 237, 204, 97);
			break;
		case 512: 
			setColor_vector(c, 237, 200, 80);
			break;
		case 1024:
			setColor_vector(c, 237, 197, 63);
			break;
		case 2048:
			setColor_vector(c, 237, 194, 46);
			break;
		case 4096:
			setColor_vector(c, 62, 57, 51);
			break;
		}

		if (a > 4096) {
			setColor_vector(c, 30, 28, 23);
		}
		return c;
	}

	


	//ANIMATION


	matrix Merged_tiles(int movement_type) {
	matrix M(tile_count, tile_count);
	switch (movement_type) {
	case 1:

		for (int i = 0; i < tile_count; i++) {
			for (int k = tile_count-2; k >=0; k--) {
				//if no change happened -- skip
				if (Change[i][k] == 0)
					continue;
				//for each element after current (if its destination is the same and its value is != 0)
				for (int pair = k + 1; pair <tile_count; pair++) {
					if (k + Change[i][k] == Change[i][pair] + pair && Movement_Backup[i][pair] != 0) {
						M.Write(i, pair + Change[i][pair], 1);
					}
				}
			}
		}

		break;

	case 2:

		for (int k = 0; k < tile_count; k++) {
			for (int i = 1; i < tile_count; i++) {
				//if no change happened -- skip
				if (Change[i][k] == 0)
					continue;

				//for each element after current (if its destination is the same and its value is != 0)
				for (int pair = i -1; pair >=0; pair--) {
					if (i - Change[i][k] == pair - Change[pair][k] && Movement_Backup[pair][k] != 0) {
						M.Write(pair - Change[pair][k], k, 1);
					}
				}
			}
		}

		break;


	case 3:

		for (int i = 0; i < tile_count; i++) {
			for (int k = 1; k <tile_count; k++) {
				//if no change happened -- skip
				if (Change[i][k] == 0)
					continue;

				//for each element after current (if its destination is the same and its value is != 0)
				for (int pair = k - 1; pair >=0; pair--) {
					if (k - Change[i][k] == pair - Change[i][pair] && Movement_Backup[i][pair] != 0) {
						M.Write(i, pair - Change[i][pair], 1);
					}
				}
			}
		}

		break;
	case 4:

		for (int k = 0; k < tile_count; k++) {
			for (int i = tile_count-2; i >=0; i--) {
				//if no change happened -- skip
				if (Change[i][k] == 0)
					continue;
				
				//for each element after current (if its destination is the same and its value is != 0)
				for (int pair = i + 1; pair <tile_count; pair++) {
					if (i + Change[i][k] == Change[pair][k] + pair && Movement_Backup[pair][k] != 0) {
						M.Write(pair + Change[pair][k], k, 1);
					}
				}
			}
		}

		break;
	}
	//cout << M;
	return M;
}

	

	//Core Animation

	

	int Movement_animation(sf::RenderWindow& window, int movement_type, sf::Vector2i new_tile_index) {
		if (skip_animation) {
			Draw_Pground(window);
			window.display();
			return 0;
		}
		int shift_st = 0, shift_ed = 6, merge_st = 5, merge_ed = 12, new_tile_st = 8, new_tile_ed = 11, end=11;
		int frame = 0;
		matrix Merged = Merged_tiles(movement_type);
		sf::Event event;
		while (frame <= end) {
			if (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::MouseButtonPressed) {
					ai_turned_on = 0;
				}
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == 72 || event.key.code == 3) {
						return 1;
					}
					if (event.key.code == 73 || event.key.code == 22) {
						return 2;
					}
					if (event.key.code == 71 || event.key.code == 0) {
						return 3;
					}
					if (event.key.code == 74 || event.key.code == 18) {
						return 4;
					}

					if (event.key.code == 36) {
						window.close();
					}
				}
			}
			Clear_Pground(window);
			Draw_Frame(window);
			if (frame >= shift_st ) {
				Shift_animation(window, movement_type, frame-shift_st, shift_ed-shift_st);
			}
			if (frame >= merge_st ) {
				Merge_tile_animation(window, Merged, frame-merge_st, merge_ed-merge_st);
			}
			if (frame >= new_tile_st && frame <= new_tile_ed) {
				New_tile_animation(window, new_tile_index, frame-new_tile_st, new_tile_ed-new_tile_st);
			}
			
			window.display();
			frame++;
			
		}

		return 0;
	}

	void Shift_animation(sf::RenderWindow& window,int movement_type, int frame, int max_frame) {
		
		//set frame confinement
		if (frame > max_frame) {
			frame = max_frame;
		}

		//direction - unit shift vector that is added to the position with every frame
		sf::Vector2f direction;
		switch (movement_type) {
		case 1: direction = sf::Vector2f(0, 1);
			break;
		case 2: direction = sf::Vector2f(-1, 0);
			break;
		case 3: direction = sf::Vector2f(0, -1);
			break;
		case 4: direction = sf::Vector2f(1, 0);
			break;
		}

		for (int i = 0; i < tile_count; i++) {
			for (int k = 0; k < tile_count; k++) {
				if (Movement_Backup[i][k] != 0) {
					Draw_Tile(
						window,
						Movement_Backup[i][k],
						sf::Vector2f(i, k) + direction * float(Change[i][k]) * float(frame) / float(max_frame),
						1,
						255
					);
				}
			}
		}
	}

	void New_tile_animation(sf::RenderWindow& window, sf::Vector2i index, int frame, int max_frame) {
			
		Draw_Tile(
			window,
			Tiles[index.x][index.y],
			sf::Vector2f(index.x, index.y),
			frame/double(max_frame),
			255*frame/double(max_frame)
		);
		
	}


	void Merge_tile_animation(sf::RenderWindow& window, matrix Merged, int frame, int max_frame) {
		//set frame confinement
		if (frame > max_frame) {
			frame = max_frame;
		}

		if (frame < 0.6 * max_frame) {
			for (int i = 0; i < tile_count; i++) {
				for (int k = 0; k < tile_count; k++) {
					if (Merged[i][k] != 0)
						Draw_Tile(
							window,
							Tiles[i][k],
							sf::Vector2f(i, k),
							frame / double(max_frame),
							255 * frame / double(max_frame)
						);
				}
			}
		}
		else if(frame<=0.8*max_frame) {
			for (int i = 0; i < tile_count; i++) {
				for (int k = 0; k < tile_count; k++) {
					if (Merged[i][k] != 0)
						Draw_Tile(window,
							Tiles[i][k],
							sf::Vector2f(i, k),
							1.1*frame / double(max_frame*0.8),
							255 
						);
				}
			}
		}
		else {
			for (int i = 0; i < tile_count; i++) {
				for (int k = 0; k < tile_count; k++) {
					if (Merged[i][k] != 0)
						Draw_Tile(
							window,
							Tiles[i][k],
							sf::Vector2f(i, k),
							1.1 - 0.1 *(frame-0.8*max_frame) / double(0.2*max_frame),
							255
						);
				}
			}
		}
	}


	void Reset_Move(sf::RenderWindow& window) {
		game_over = 0;
		reached_2048 = 0;
		if (Movement_Backup != matrix(tile_count, tile_count)) {
			int frame = 0, max_frame = 10;
			while (frame <= max_frame) {
				Clear_Pground(window);
				Draw_Frame(window);
				for (int i = 0; i < tile_count; i++) {
					for (int k = 0; k < tile_count; k++) {
						if (Tiles[i][k] != 0 && frame <= 0.7 * max_frame) {
							Draw_Tile(window, Tiles[i][k], sf::Vector2f(i, k), 1, 255 - 255 * (frame) / double(0.7 * max_frame));
						}
						if (Movement_Backup[i][k] != 0 && frame > 0.7 * max_frame) {
							Draw_Tile(window, Movement_Backup[i][k], sf::Vector2f(i, k), 1, 255 * (frame - 0.7 * max_frame)/ double(0.3 * max_frame));
						}
					}
				}
				window.display();
				frame++;
			}
			Tiles = Movement_Backup;
		}
	}

	
	void Game_over_animation(sf::RenderWindow& window) {

		sf::RectangleShape faded_pground((sf::Vector2f)getSize());
		faded_pground.setOrigin(faded_pground.getSize() / (float)2);
		faded_pground.setPosition((sf::Vector2f)window.getSize() / float(2));
		faded_pground.setFillColor(sf::Color(240, 240, 240, 150));

		//Loading font
		sf::Text display_text_1, display_text_2;
		
		display_text_1.setString("Game over!");
		display_text_2.setString("To continue, press Undo or New Game");


		display_text_1.setFont(universal_font);
		display_text_2.setFont(universal_font);

		display_text_1.setStyle(sf::Text::Regular);
		display_text_2.setStyle(sf::Text::Regular);


		display_text_1.setCharacterSize(100 / float(2000) * window.getSize().x);
		display_text_2.setCharacterSize(40 / float(2000) * window.getSize().x);

		display_text_1.setFillColor(sf::Color(143, 122, 102, 255));
		display_text_2.setFillColor(sf::Color(143, 122, 102, 255));


		sf::FloatRect bounds1 = display_text_1.getGlobalBounds();
		sf::FloatRect bounds2 = display_text_2.getGlobalBounds();

		display_text_1.setOrigin(bounds1.width / 2 + bounds1.left, bounds1.height / 2 + bounds1.top);
		display_text_1.setPosition((sf::Vector2f)window.getSize() / (float)2);

		display_text_2.setOrigin(bounds2.width / 2 + bounds2.left, bounds2.height / 2 + bounds2.top);
		display_text_2.setPosition((sf::Vector2f)window.getSize() / (float)2 + sf::Vector2f(0, 2.5 * bounds1.height));

		///

		int frame = 0, max_frame = 40;

		while (frame < max_frame) {
			Draw_Pground(window);
			window.display();
			frame++;
		}

		frame = 0; max_frame = 20;

		while (frame <= max_frame) {
			faded_pground.setFillColor(sf::Color(240, 240, 240, 150 * frame / float(max_frame)));
			display_text_1.setFillColor(sf::Color(143, 122, 102, 255 * frame / float(max_frame)));
			display_text_2.setFillColor(sf::Color(143, 122, 102, 255 * frame / float(max_frame)));

			Draw_Pground(window);

			window.draw(faded_pground);
			window.draw(display_text_1);
			window.draw(display_text_2);
			window.display();
			frame++;
		}
	}

	void Win_animation(sf::RenderWindow& window) {

		sf::RectangleShape faded_pground((sf::Vector2f)getSize());
		faded_pground.setOrigin(faded_pground.getSize() / (float)2);
		faded_pground.setPosition((sf::Vector2f)window.getSize() / float(2));
		faded_pground.setFillColor(sf::Color(240, 240, 240, 150));

		//Loading font
		sf::Text display_text_1, display_text_2;
		
		display_text_1.setString("Congratulations!");
		display_text_2.setString("To continue, press Undo or New Game");


		display_text_1.setFont(universal_font);
		display_text_2.setFont(universal_font);

		display_text_1.setStyle(sf::Text::Regular);
		display_text_2.setStyle(sf::Text::Regular);


		display_text_1.setCharacterSize(100 / float(2000) * window.getSize().x);
		display_text_2.setCharacterSize(40 / float(2000) * window.getSize().x);

		display_text_1.setFillColor(sf::Color(143, 122, 102, 255));
		display_text_2.setFillColor(sf::Color(143, 122, 102, 255));


		sf::FloatRect bounds1 = display_text_1.getGlobalBounds();
		sf::FloatRect bounds2 = display_text_2.getGlobalBounds();

		display_text_1.setOrigin(bounds1.width / 2 + bounds1.left, bounds1.height / 2 + bounds1.top);
		display_text_1.setPosition((sf::Vector2f)window.getSize() / (float)2);

		display_text_2.setOrigin(bounds2.width / 2 + bounds2.left, bounds2.height / 2 + bounds2.top);
		display_text_2.setPosition((sf::Vector2f)window.getSize() / (float)2 + sf::Vector2f(0, 2.5 * bounds1.height));

		///

		int frame = 0, max_frame = 40;

		while (frame < max_frame) {
			Draw_Pground(window);
			window.display();
			frame++;
		}

		frame = 0; max_frame = 20;

		while (frame <= max_frame) {
			faded_pground.setFillColor(sf::Color(240, 240, 240, 150 * frame / float(max_frame)));
			display_text_1.setFillColor(sf::Color(143, 122, 102, 255 * frame / float(max_frame)));
			display_text_2.setFillColor(sf::Color(143, 122, 102, 255 * frame / float(max_frame)));

			Draw_Pground(window);

			window.draw(faded_pground);
			window.draw(display_text_1);
			window.draw(display_text_2);
			window.display();
			frame++;
		}
	}


	void Clear_Pground(sf::RenderWindow& window) {
		Smooth_rect blank((sf::Vector2f)getSize(), (double)10, (sf::Vector2f)(window.getSize() / (unsigned)2));
		blank.setColor(sf::Color(250, 248, 239, 255));
		blank.Draw(window);
	}
};

#endif 
#pragma once