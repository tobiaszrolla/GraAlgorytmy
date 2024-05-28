#ifndef WARCABY_H_
#define WARCABY_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "plansza.hpp"
#include "Judge.hpp"
#include "Bot.hpp"
//Główna klasa gry
class Warcaby
{
private:
    /* data */
    //zmienne okna
    const int hight_wide{600};
    const int  fild{75};
    const int pion_nr{12};
    sf::RenderWindow* window;
    sf::VideoMode videmod;
    sf::Vector2i mouse_pos;
    sf::Sprite szachownica_sprite;
    //event zamykania
    sf::Event ev;
    //Czarne pionki
    std::vector<sf::CircleShape> piony_bot;
    std::vector<sf::CircleShape> piony_gracz;
    Plansza plansza;
    Judge judge;
    Bot bot;
    //ZMienne menu wyboru
    int selected_index = -1;
    bool pion_selected = false;
    bool bot_turn = false;
    // Zmiena zawierająca rozztrzygnięcie sędziego
    int judge_choice;
    /*metody prywatne*/
    void variableInit();
    void windowInit();
    //obsługuje wjeścia klawiszy
    void pollEvents();
    void pollPionGracz(int index);
    //tworzenie pionków render
    sf::CircleShape initPion(int x, int y,sf::Color color);
    void initPionColection(std::vector<std::pair<int,int>> bot_pos, std::vector<std::pair<int,int>> gracz_pos);
    //myszka klasa 
    void updateMousePosition();
public:
    //konstruktor destruktor
    Warcaby(/* args */);
    ~Warcaby();
    //zmienia stan gry
    void update();
    //renderuje nowom plansze
    void render();
    //prawda gdy okno jest otwarte
    const bool running() const;
    // pozwala ustawić teksturę szachownicy;
    void SpriteSzachText(sf::Texture& obraz);
};


#endif /*WARCABY_H_*/