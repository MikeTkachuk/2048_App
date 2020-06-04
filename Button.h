#ifndef Button1
#define Button1

#include <SFML/Graphics.hpp>
#include "Draw_Sh.h"
#include "Dependencies/Matrix.h"
#include <string>
#include <Windows.h>



class Button
{
private:
	Smooth_rect body;
	Smooth_rect outline;
	string text;
	sf::Color text_color;
	int Char_Size;
	bool active, visible;

public:

	Button() {
		text = "";
		text_color = sf::Color::White;
	}

	Button(sf::Vector2f Size, double R, sf::Vector2f Pos, sf::Color bodycolor, int outline_width, string t, sf::Color tcolor) {
		body.Init(Size, R, Pos);
		body.setColor(bodycolor);
		outline.Init(Size + sf::Vector2f(outline_width, outline_width), R, Pos);
		outline.setColor(contrast(bodycolor));
		text = t;
		text_color = tcolor;
	}
	void Init(sf::Vector2f Size, double R, sf::Vector2f Pos, sf::Color bodycolor, int outline_width, string t, sf::Color tcolor) {
		body.Init(Size, R, Pos);
		body.setColor(bodycolor);
		text = t;
		text_color = tcolor;
	}

	Button(sf::Vector2f Size, double R, sf::Vector2f Pos, sf::Color bodycolor, int outline_width, string t, sf::Color tcolor, bool vis, bool act) {
		body.Init(Size, R, Pos);
		body.setColor(bodycolor);
		outline.Init(Size + sf::Vector2f(outline_width, outline_width), R, Pos);
		outline.setColor(contrast(bodycolor));
		text = t;
		text_color = tcolor;
		Char_Size = 40;
		visible = vis;
		active = act;
	}
	void Init(sf::Vector2f Size, double R, sf::Vector2f Pos, sf::Color bodycolor, int outline_width, string t, sf::Color tcolor, bool vis, bool act) {
		body.Init(Size, R, Pos);
		body.setColor(bodycolor);
		outline.Init(Size + sf::Vector2f(outline_width, outline_width), R, Pos);
		outline.setColor(contrast(bodycolor));
		text = t;
		text_color = tcolor;
		Char_Size = 40;
		visible = vis;
		active = act;
	}

	Button(sf::Vector2f Size, double R, sf::Vector2f Pos, sf::Color bodycolor, string t, int ch_size, sf::Color tcolor, bool vis, bool act) {
		body.Init(Size, R, Pos);
		body.setColor(bodycolor);
		text = t;
		text_color = tcolor;
		Char_Size = ch_size;
		visible = vis;
		active = act;
	}
	void Init(sf::Vector2f Size, double R, sf::Vector2f Pos, sf::Color bodycolor, string t, int ch_size, sf::Color tcolor, bool vis, bool act) {
		body.Init(Size, R, Pos);
		body.setColor(bodycolor);
		text = t;
		text_color = tcolor;
		Char_Size = ch_size;
		visible = vis;
		active = act;
	}

	sf::Vector2f getSize() {
		return body.getSize();
	}
	sf::Vector2f getPosition() {
		return body.getPosition();
	}
	sf::FloatRect getBounds() {
		sf::FloatRect B(getPosition()-getSize()/float(2), getSize());
		return B;
	}
	bool isActive() {
		return active;
	}
	bool isVisible() {
		return visible;
	}
	void setSize(sf::Vector2f s) {
		 body.setSize(s);
	}
	void setPosition(sf::Vector2f p) {
		body.setPosition(p);
	}

	void setVisibility(bool i) {
		visible = i;
	}
	void setActivity(bool i) {
		active = i;
	}


	void Press(sf::RenderWindow& window) {
		body.setColor(contrast(body.getColor()));
		outline.setColor(contrast(outline.getColor()));
		Draw(window);
	}

	void Draw(sf::RenderWindow& window) {
		if (visible) {
			outline.Draw(window);
			body.Draw(window);

			//Loading font
			sf::Text display_text;
			sf::Font font;
			if (!font.loadFromFile("Fonts/clearsans-1.00/TTF/ClearSans-Bold.ttf"))
				std::cout << "Error loading font!\n";
			display_text.setString(text);
			
			display_text.setFont(font);
			display_text.setStyle(sf::Text::Regular);

			
			display_text.setCharacterSize(body.getSize().y / 2);
			
			sf::FloatRect bounds = display_text.getGlobalBounds();
			
			display_text.setOrigin(bounds.width / 2 + bounds.left, bounds.height / 2 + bounds.top);
			display_text.setPosition(sf::Vector2f(0,0));
			
			sf::FloatRect test = display_text.getGlobalBounds();
			
			
			display_text.setPosition((sf::Vector2f)body.getPosition());
			///
			window.draw(display_text);

		}
	}

};

#endif // !Button1

#pragma once