#include "/home/tobiasz/GraAlgorytmy/include/warcaby.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
void Warcaby::variableInit()
{
    //inicjalizacja zmiennej window na nullptr
    this->window = nullptr;
    //klasa biblioteki potzebna dla okna
    sf::VideoMode videomode;
    //event zamykania
    sf::Event closeing;
}
void Warcaby::windowInit()
{
    this->videmod.height = hight_wide;
    this->videmod.width = hight_wide;
    //inicjalizacja window na jej rozmiar Tital bar i close pozwalają na zamknięcie
    this->window = new sf::RenderWindow(sf::VideoMode(hight_wide, hight_wide), "Warcaby", sf::Style::Titlebar | sf::Style::Close);
    this->window->setVerticalSyncEnabled(false);
}
void Warcaby::pollEvents()
{
    while(window->pollEvent(ev))
    {
        /*
            Sprawdza czy nie zamknięto okna
            Sprawdza czy klknięto na pole zajęte przez gracza
        */
        switch(ev.type)
        {
            //jeśli zamykamy okno to je zamykamy
            case sf::Event::Closed :
                window->close();
                break;
            case sf::Event::MouseButtonPressed :
                if(!pion_selected)
                {
                    this -> updateMousePosition();
                    std::cout<<mouse_pos.x<<" "<<mouse_pos.y<<std::endl;
                    for(int i = 0; i < piony_gracz.size(); i++)
                    {
                       // określa zakres pola pionka porównuje z mous_pos
                       if(piony_gracz[i].getGlobalBounds().contains(sf::Vector2f(mouse_pos)))
                       {
                           selected_index = i;
                           pion_selected = true;
                           break;
                       }
                    }   
                }
                else
                {
                    this -> updateMousePosition();
                    std::cout<<mouse_pos.x<<" "<<mouse_pos.y<<std::endl;
                    pollPionGracz(selected_index);
                    selected_index = -1;
                    pion_selected = false;
                    break;
                }
            default:
                break;
        }
    }
}
void Warcaby::pollPionGracz(int index)
{
    /*
        Metoda pomagająca przy poll Event
        Określa ruch po wciśnięciu pionka
        Przyjmuje index klikniętego

        index rozpoznaje sprawdzany pionek
        mov_res sprawdza czy doszło do przesunięcia
    */
   //bool move_result = false;
   if(ev.type == sf::Event::MouseButtonPressed)
   {
    bool move_result = false;
    if(piony_gracz[index].getPosition().x >= mouse_pos.x &&
       piony_gracz[index].getPosition().y >= mouse_pos.y &&  
       (piony_gracz[index].getPosition().x - fild) <= mouse_pos.x &&
       (piony_gracz[index].getPosition().y - fild) <= mouse_pos.y)
       {
        move_result = plansza.moveLeftPlayer(index);
        if(move_result)
        {
            std::cout<<piony_gracz[index].getPosition().x<<std::endl;
            piony_gracz[index].setPosition(piony_gracz[index].getPosition().x - fild,piony_gracz[index].getPosition().y - fild);
            std::cout<<piony_gracz[index].getPosition().x<<std::endl;
        }
       }
    if((piony_gracz[index].getPosition().x + 2 *fild)>= mouse_pos.x &&
       piony_gracz[index].getPosition().y >= mouse_pos.y &&  
       (piony_gracz[index].getPosition().x + fild) <= mouse_pos.x &&
       (piony_gracz[index].getPosition().y - fild) <= mouse_pos.y)
       {
        move_result = plansza.moveRightPlayer(index);
        if(move_result)
        {
            std::cout<<piony_gracz[index].getPosition().x<<std::endl;
            piony_gracz[index].setPosition(piony_gracz[index].getPosition().x + fild,piony_gracz[index].getPosition().y - fild);
            std::cout<<piony_gracz[index].getPosition().x<<std::endl;
        }
       }
    if(piony_gracz[index].getPosition().x  - fild >= mouse_pos.x &&
       piony_gracz[index].getPosition().y  - fild >= mouse_pos.y &&  
       (piony_gracz[index].getPosition().x - 2*fild) <= mouse_pos.x &&
       (piony_gracz[index].getPosition().y - 2*fild) <= mouse_pos.y)
       {
        std::pair<bool,int> move_result = plansza.attactLeftPlayer(index);
        if(move_result.first)
        {
            std::cout<<piony_gracz[index].getPosition().x<<std::endl;
            piony_gracz[index].setPosition(piony_gracz[index].getPosition().x - 2 * fild ,piony_gracz[index].getPosition().y - 2*fild);
            piony_bot.erase(piony_bot.begin() + move_result.second);
            std::cout<<piony_gracz[index].getPosition().x<<std::endl;
        }
        }
    if(piony_gracz[index].getPosition().x  + 3*fild >= mouse_pos.x &&
       piony_gracz[index].getPosition().y  - fild >= mouse_pos.y &&  
       (piony_gracz[index].getPosition().x + 2*fild) <= mouse_pos.x &&
       (piony_gracz[index].getPosition().y - 2*fild) <= mouse_pos.y)
       {
        std::pair<bool,int> move_result = plansza.attactRightPlayer(index);
        if(move_result.first)
        {
            std::cout<<piony_gracz[index].getPosition().x<<std::endl;
            piony_gracz[index].setPosition(piony_gracz[index].getPosition().x + 2 * fild ,piony_gracz[index].getPosition().y - 2*fild);
            piony_bot.erase(piony_bot.begin() + move_result.second);
            std::cout<<piony_gracz[index].getPosition().x<<std::endl;
        }
        }
        checkGameStatus();
        bot_turn = true;
    }

};
sf::CircleShape Warcaby::initPion(int x, int y,sf::Color color)
{
    /*
        Metoda odpowiedzialna za zwracanie kolejnych pionków
        (Graficznych) bota działa z initBotColection
    */
    sf::CircleShape pion; 
    pion.setPosition(x,y);
    double radius = hight_wide/16;
    pion.setRadius(radius);
    pion.setFillColor(color);
    return pion;
};

void Warcaby::initPionColection(std::vector<std::pair<int,int>> bot_pos, std::vector<std::pair<int,int>> gracz_pos)
{
    /*
        Metoda ustawia koeljne pionki bota na planszy
        w odpowiednich miejscach wstawia do wektora;
    */
    piony_bot.clear();
    piony_gracz.clear();
    for(int i = 0; i < bot_pos.size(); i++)
    {
        piony_bot.push_back(initPion(bot_pos[i].first,bot_pos[i].second, sf::Color::Red));
    }
    for(int i = 0; i < gracz_pos.size(); i++)
    {
        piony_gracz.push_back(initPion(gracz_pos[i].first,gracz_pos[i].second, sf::Color::White));
    }
}
void Warcaby::updateMousePosition()
{
    /*
        Wczytuje pozycję myszy względem okna
    */
    this->mouse_pos = sf::Mouse::getPosition(*this->window);
    }
/*Metody publiczne*/
Warcaby::Warcaby()
{
    this->variableInit();
    this->windowInit();
    this->initPionColection(this->plansza.getPionyBot(),this->plansza.getPionyGracz());
}
Warcaby::~Warcaby()
{
    /*
        usuwamy alokowane dynamiczne window
    */
    delete window;
}
//sprawdza stan gry
void Warcaby::checkGameStatus()
{
    judge_choice = judge.judging(plansza);
    if(judge_choice != 0)
    {
        if(judge_choice == -1000)
        {
            std::cout<<"Bot"<<std::endl;
        }
        else if(judge_choice == -1000)
        {
            std::cout<<"Gracz"<<std::endl;
        }
        else
        {
            std::cout<<"Remis"<<std::endl;
        }
        this->render();
        sf::sleep(sf::milliseconds(1000));
        plansza = Plansza();
        this->initPionColection(this->plansza.getPionyBot(),this->plansza.getPionyGracz());
    }
}
//zmienia stan okna
void Warcaby::render()
{
    this->window->clear(sf::Color::Black);
    this->window->draw(szachownica_sprite);
    for(int i = 0; i < piony_bot.size(); i++)
    {
        this->window->draw(this->piony_bot[i]);
    }
    for(int i = 0; i < piony_gracz.size(); i++)
    {
        this->window->draw(this->piony_gracz[i]);
    }
    this->window->display();
}
//zmienia stan gry
/*void Warcaby::update()
{
    checkGameStatus();
    this->pollEvents();
    if(bot_turn)
    {
        checkGameStatus();
        this->render();
        sf::sleep(sf::milliseconds(500));
        bot_turn = false;
        piony_bot.clear();
        piony_gracz.clear();
        plansza = bot.makeMove(plansza);
        initPionColection(plansza.getPionyBot(), plansza.getPionyGracz());
        judge_choice = judge.judging(plansza);
        bool move_result;
        int i = 0;
        checkGameStatus();
        this->render();
    }
}*/
void Warcaby::update() {
    checkGameStatus(); // Najpierw sprawdź stan gry

    if (bot_turn) {
        // Sprawdź stan gry przed ruchem bota
        sf::sleep(sf::milliseconds(500));
        checkGameStatus();
        bot_turn = false;
        piony_bot.clear();
        piony_gracz.clear();
        plansza = bot.makeMove(plansza);
        initPionColection(plansza.getPionyBot(), plansza.getPionyGracz());
        judge_choice = judge.judging(plansza);
        bool move_result;
        int i = 0;
        checkGameStatus();
    } 
    else {
        this->pollEvents();
    }

    // Renderuj zawsze po sprawdzeniu stanu gry
    this->render();
}
/*Gettery*/
const bool Warcaby::running() const
{
    return this->window->isOpen();
}
/*Setery w sumie*/
void Warcaby::SpriteSzachText(sf::Texture& obraz)
{
    /*
        Ustawia texturę sprita
        urzywa referencji ponieważ inaczej zniszczono by obraz po zakończeniu
    */
    this->szachownica_sprite.setTexture(obraz);
}
