#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Gameplay.h"
#include <time.h>





int main()
{
    srand(time(NULL));

    int window_size;
    window_size = min(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

    sf::RenderWindow window(sf::VideoMode(window_size, window_size), "2048!");
    window.setVerticalSyncEnabled(true);

    Gameplay game(4, sf::Vector2u((window.getSize()/(unsigned)2).x, (window.getSize() / (unsigned)2).x));
  
    game.Game(window);

    return 0;
}