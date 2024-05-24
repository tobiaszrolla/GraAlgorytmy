#include <iostream>
#include "/home/tobiasz/GraAlgorytmy/include/warcaby.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
int main()
{
    sf::Texture obraz;
    if (!obraz.loadFromFile("/home/tobiasz/GraAlgorytmy/szachownica600x600.png")) {
        return -1; 
    }
    Warcaby warcaby;
    warcaby.SpriteSzachText(obraz);
    while (warcaby.running())
    {
        warcaby.update();

        warcaby.render();
    }

    return 0;
}