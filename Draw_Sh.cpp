#include "Draw_Sh.h"

sf::Color setColor_vector(sf::Color& color, unsigned a, unsigned b, unsigned c, unsigned d) {
	color.r = a;
	color.g = b;
	color.b = c;
	color.a = d;
	return color;
}

sf::Color setColor_vector(sf::Color& color, unsigned a, unsigned b, unsigned c) {
	color.r = a;
	color.g = b;
	color.b = c;
	return color;
}

sf::Color setColor_vector(unsigned a, unsigned b, unsigned c, unsigned d) {
	sf::Color color(a, b, c, d);
	return color;
}

sf::Color contrast(sf::Color c) {
	sf::Color color(255 - c.r, 255 - c.g, 255 - c.b, c.a);
	return color;
}