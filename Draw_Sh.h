#pragma once
#include <SFML/Graphics.hpp>

class Smooth_rect {
private:
	sf::Vector2f size;
	double radius;
	sf::Vector2f Position;
	sf::Color color;
public:
	Smooth_rect() {
		radius = 0;
	}
	Smooth_rect(sf::Vector2f Size, double R, sf::Vector2f Pos) {
		size = Size;
		radius = R;
		Position = Pos;
		color = sf::Color::White;
	}
	void Init(sf::Vector2f Size, double R, sf::Vector2f Pos) {
		size = Size;
		radius = R;
		Position = Pos;
		color = sf::Color::White;
	}

	Smooth_rect(sf::Vector2f Size, double R) {
		size = Size;
		radius = R;
		Position = sf::Vector2f(0,0);
		color = sf::Color::White;

	}
	void Init(sf::Vector2f Size, double R) {
		size = Size;
		radius = R;
		Position = sf::Vector2f(0,0);
		color = sf::Color::White;
	}

	sf::Vector2f getSize() {
		return size;
	}
	sf::Vector2f getPosition() {
		return Position;
	}

	void setColor(sf::Color c) {
		color = c;
	}
	void setPosition(sf::Vector2f pos) {
		Position = pos;
	}
	void setSize(sf::Vector2f siz) {
		size = siz;
	}

	void Draw(sf::RenderWindow& window) {
		sf::RectangleShape vertical_rect(sf::Vector2f(size.x, size.y - 2 * radius));
		vertical_rect.setOrigin(vertical_rect.getSize() / 2.f);
		vertical_rect.setPosition(Position);
		vertical_rect.setFillColor(color);
		window.draw(vertical_rect);

		sf::RectangleShape horizontal_rect(sf::Vector2f(size.x - 2 * radius, size.y));
		horizontal_rect.setOrigin(horizontal_rect.getSize() / 2.f);
		horizontal_rect.setPosition(Position);
		horizontal_rect.setFillColor(color);
		window.draw(horizontal_rect);

		sf::CircleShape circle(radius);
		circle.setOrigin(sf::Vector2f(radius, radius));
		circle.setFillColor(color);
		///
		sf::Vector2f help(size/2.f);
		///
		circle.setPosition(Position - help + circle.getOrigin());
		window.draw(circle);

		circle.setPosition(Position - help  + sf::Vector2f(size.x-radius,radius ));
		window.draw(circle);
		
		circle.setPosition(Position - help + sf::Vector2f(radius, size.y -  radius));
		window.draw(circle);
		
		circle.setPosition(Position + help - circle.getOrigin() );
		window.draw(circle);

	}
};

sf::Color setColor_vector(sf::Color& color, unsigned a, unsigned b, unsigned c, unsigned d);
sf::Color setColor_vector(sf::Color& color, unsigned a, unsigned b, unsigned c);
sf::Color setColor_vector(unsigned a, unsigned b, unsigned c, unsigned d);
