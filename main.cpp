#include <SFML/Graphics.hpp>
#include "Gameplay.h"
#include <time.h>





int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(2000, 2000), "2048!");
    window.setVerticalSyncEnabled(true);

    Gameplay game(4, sf::Vector2u((window.getSize()/(unsigned)2).x, (window.getSize() / (unsigned)2).x));
  
    game.Game(window);

    return 0;
}