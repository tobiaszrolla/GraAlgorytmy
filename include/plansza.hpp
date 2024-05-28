#ifndef PLANSZA_H_
#define PLANSZA_H_
#include <vector>
#include "PionLog.h"
class Plansza
{
    protected:
    //stałe odnośne planszy
        const int hight_wide{600};
        const int  fild{75};
        const int pion_nr{12};
    //sprawdza możliwość ruchu
        bool moveLeftPlayerCheck(int index);
    private:
     //kolekcja logicznych reprezentacji pionów gracza
        std::vector<PionLog> piony_gracz;
    //kolekcja logicznych reprezentacji pionów bota
        std::vector<PionLog> piony_bot;
    public:
    //inicjuje plansze z piąkami i ich logiką
        Plansza();
        ~Plansza(){};
        Plansza(const Plansza &other);
        Plansza& operator =(const Plansza &other);
    //Getter
        std::vector<std::pair<int, int>> getPionyBot();
        std::vector<std::pair<int, int>> getPionyGracz();
    //Move
        bool moveLeftPlayer(int index);
        bool moveRightPlayer(int index);
        std::pair<bool,int> attactLeftPlayer(int index);
        std::pair<bool,int> attactRightPlayer(int index);
        bool moveLeftBot(int index);
        bool moveRightBot(int index);
        std::pair<bool,int> attactLeftBot(int index);
        std::pair<bool,int> attactRightBot(int index);
    //Judgment
};

#endif /*PLANSZA_H_*/