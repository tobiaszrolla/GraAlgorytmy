#ifndef PLANSZA_H_
#define PLANSZA_H_
#include <vector>
#include "PionLog.h"
class Plansza
{
    private:
    //stałe odnośne planszy
        const int hight_wide{600};
        const int  fild{75};
        const int pion_nr{12};
    //kolekcja logicznych reprezentacji pionów gracza
        std::vector<PionLog> piony_gracz;
    //kolekcja logicznych reprezentacji pionów bota
        std::vector<PionLog> piony_bot;

    public:
    //inicjuje plansze z piąkami i ich logiką
        Plansza();
    //Getter
        std::vector<std::pair<int, int>> getPionyBot();
        std::vector<std::pair<int, int>> getPionyGracz();
    //Move
        bool moveLeftPlayer(int index);
};
#endif /*PLANSZA_H_*/