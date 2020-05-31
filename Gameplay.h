#ifndef GamePlay
#define GamePlay


#include <SFML/Graphics.hpp>
#include "Playground.h"
#include "Button.h"
using namespace sf;

class Gameplay
{
private:
	
	Playground playground;
	Button undo_buton, new_game_button, ai_button, tip_button;
    bool ai_turned_on;
public:

	Gameplay() {
      
	}
	Gameplay(int N, sf::Vector2u Size) {
        float window_size;
        window_size = min(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

		playground.Init(N, Size);
		playground.setColor(sf::Color(187, 173, 160, 255));
		
        undo_buton.Init(sf::Vector2f(230,70)/float(2000)*window_size,10 / float(2000) * window_size,sf::Vector2f(1375, 435) / float(2000) * window_size,sf::Color(143, 122, 102,255), "Undo", sf::Color(255,253,230, 255),1 , 1);
        new_game_button.Init(sf::Vector2f(230, 70) / float(2000) * window_size, 10 / float(2000) * window_size, sf::Vector2f(1375, 235) / float(2000) * window_size, sf::Color(103, 88, 73, 255), "New Game", sf::Color(255, 253, 230, 255), 1, 1);
		ai_button.Init(sf::Vector2f(350, 90) / float(2000) * window_size, 10 / float(2000) * window_size, sf::Vector2f(200, 80) / float(2000) * window_size, sf::Color(60, 60, 60, 255), "Give AI a try", sf::Color(255, 253, 230, 255), 1, 1);
        tip_button.Init(sf::Vector2f(350, 75) / float(2000) * window_size, 10 / float(2000) * window_size, sf::Vector2f(200, 180) / float(2000) * window_size, sf::Color(60, 60, 60, 255), "AI tips", sf::Color(255, 253, 230, 255), 1, 1);
        ai_turned_on = 0;
    }


    void Draw_Static_Entities(sf::RenderWindow& window) {
        Draw_Background(window);
        undo_buton.Draw(window);
        new_game_button.Draw(window);
        ai_button.Draw(window);
        tip_button.Draw(window);
    }

    void Game(sf::RenderWindow& window) {
        if (window.isOpen()) {
            Draw_Static_Entities(window);

            Start_scene(window);
            New_game(window);
        }
        sf::Vector2f Mouse_Pressed;

        int ai_executive = 1;

        while (window.isOpen())
        {
            
            window.clear();
            Draw_Static_Entities(window);

            playground.Draw_Pground(window);

            //Game Over event
            if (playground.isGameOver()) {
               Game_over_scene(window);
            }

            if (playground.isWin()) {
                Win_scene(window);
            }

            window.display();
            if (ai_turned_on) {
                playground.Movement(window, ai_executive);
                ai_executive++;
                if (ai_executive > 4)
                    ai_executive = 1;
                playground.Movement(window, ai_executive);
                ai_executive++;
                if (ai_executive > 4)
                    ai_executive = 1;
                playground.Movement(window, ai_executive);
                ai_executive++;
                if (ai_executive > 4)
                    ai_executive = 1;
                playground.Movement(window, ai_executive);
                ai_executive++;
                if (ai_executive > 4)
                    ai_executive = 1;
            }
            sf::Event event;
            while (window.pollEvent(event))
            {
                
                if (event.type == sf::Event::MouseButtonPressed) {

                    Mouse_Pressed = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

                    if (undo_buton.getBounds().contains(Mouse_Pressed) && undo_buton.isActive()) {
                        playground.Reset_Move(window);
                    }
                    if (new_game_button.getBounds().contains(Mouse_Pressed) && new_game_button.isActive()) {
                        New_game(window);
                    }
                    if (ai_button.getBounds().contains(Mouse_Pressed) && ai_button.isActive()) {
                        ai_turned_on = !ai_turned_on;
                    }
                }

               

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == 72|| event.key.code == 3) {
                        playground.Movement(window, 1);
                    }
                    if (event.key.code == 73|| event.key.code == 22) {
                        playground.Movement(window, 2);
                    }
                    if (event.key.code == 71||event.key.code == 0) {
                        playground.Movement(window, 3);
                    }
                    if (event.key.code == 74|| event.key.code == 18) {
                        playground.Movement(window, 4);
                    }


                    if (event.key.code == 36) {
                        window.close();
                    }
                }
                if (event.type == sf::Event::Closed)
                    window.close();
            }
        }
    }


	void Start_scene(sf::RenderWindow& window) {
        int frame = 0, max_frame = 70;
       
        sf::RectangleShape white_screen((sf::Vector2f)window.getSize());
        white_screen.setFillColor(sf::Color::White);
        
        //Loading font
        sf::Text display_text;
        sf::Font font;
        if (!font.loadFromFile("Fonts/clearsans-1.00/TTF/ClearSans-Bold.ttf"))
            std::cout << "Error loading font!\n";
        display_text.setString("2048!");

        display_text.setFont(font);
        display_text.setStyle(sf::Text::Regular);


        display_text.setCharacterSize(250 / float(2000) * window.getSize().x);

        sf::FloatRect bounds = display_text.getGlobalBounds();

        display_text.setOrigin(bounds.width / 2 + bounds.left, bounds.height / 2 + bounds.top);

        display_text.setPosition((sf::Vector2f)window.getSize()/(float)2);
        ///
        window.draw(display_text);


        while (frame < max_frame) {
            sf::Event event;
            while (window.pollEvent(event))
            {

                if (event.type == sf::Event::MouseButtonPressed||event.type==sf::Event::KeyPressed) {
                    frame = max_frame;
                    break;
                }

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == 36) {
                        window.close();
                    }
                }

                if (event.type == sf::Event::Closed)
                    window.close();

            }

            window.draw(white_screen);
            if (frame < max_frame * 0.6) {
                display_text.setFillColor(sf::Color(143, 122, 102, frame / (max_frame * 0.6) * 255));
            }
            else {
                display_text.setFillColor(sf::Color(143, 122, 102, 255));
            }
            window.draw(display_text);

            window.display();
            frame++;
        }


        frame = 0;
        
        while (frame < max_frame*0.45) {

            Draw_Static_Entities(window);
            playground.Draw_Pground(window);

            white_screen.setFillColor(sf::Color(255,255,255,255-255*frame/(max_frame*0.45)));
            window.draw(white_screen);
            display_text.setFillColor(sf::Color(143, 122, 102, 255 - 255 * frame / (max_frame * 0.45)));
            window.draw(display_text);


            window.display();
            frame++;
        }
    }



    void New_game(sf::RenderWindow& window) {
        playground.Reset_Playground();
        sf::Vector2i a=playground.Set_new_tile();
        sf::Vector2i b = playground.Set_new_tile();

        int frame = 0, max_frame=12;

        while (frame < max_frame) {
            Draw_Static_Entities(window);

            playground.Clear_Pground(window);
            playground.Draw_Frame(window);
            playground.New_tile_animation(window, a, frame, max_frame);
            playground.New_tile_animation(window, b, frame, max_frame);

            window.display();
            frame++;
        }
    }



    void Game_over_scene(sf::RenderWindow& window) {
        sf::RectangleShape faded_pground((sf::Vector2f)playground.getSize());
        faded_pground.setOrigin(faded_pground.getSize() / (float)2);
        faded_pground.setPosition((sf::Vector2f)window.getSize() / float(2));
        faded_pground.setFillColor(sf::Color(240, 240, 240, 150));

        //Loading font
        sf::Text display_text_1, display_text_2;
        sf::Font font;
        if (!font.loadFromFile("Fonts/clearsans-1.00/TTF/ClearSans-Bold.ttf"))
            std::cout << "Error loading font!\n";
        display_text_1.setString("Game over!");
        display_text_2.setString("To continue, press Undo or New Game");


        display_text_1.setFont(font);
        display_text_2.setFont(font);

        display_text_1.setStyle(sf::Text::Regular);
        display_text_2.setStyle(sf::Text::Regular);


        display_text_1.setCharacterSize(100/float(2000)*window.getSize().x);
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
        window.draw(faded_pground);
        window.draw(display_text_1);
        window.draw(display_text_2);

    }

    void Win_scene(sf::RenderWindow& window) {
        sf::RectangleShape faded_pground((sf::Vector2f)playground.getSize());
        faded_pground.setOrigin(faded_pground.getSize() / (float)2);
        faded_pground.setPosition((sf::Vector2f)window.getSize() / float(2));
        faded_pground.setFillColor(sf::Color(240, 240, 240, 150));

        //Loading font
        sf::Text display_text_1, display_text_2;
        sf::Font font;
        if (!font.loadFromFile("Fonts/clearsans-1.00/TTF/ClearSans-Bold.ttf"))
            std::cout << "Error loading font!\n";
        display_text_1.setString("Congratulations!");
        display_text_2.setString("To continue, press Undo or New Game");


        display_text_1.setFont(font);
        display_text_2.setFont(font);

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
        window.draw(faded_pground);
        window.draw(display_text_1);
        window.draw(display_text_2);

    }

    void Draw_Background(sf::RenderWindow& window) {
        sf::RectangleShape ambient((sf::Vector2f)window.getSize());
        ambient.setFillColor(sf::Color(250, 248, 239, 255));
        window.draw(ambient);
    }

};


#endif // !GamePlay

#pragma once