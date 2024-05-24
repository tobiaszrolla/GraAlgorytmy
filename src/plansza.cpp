#include "/home/tobiasz/GraAlgorytmy/include/plansza.hpp"
#include <iostream>

Plansza::Plansza()
{
    int x = 0;
    int y = 0;
    bool lock = false;
    for(int i = 0; i < pion_nr; i++)
    {
        piony_bot.push_back(PionLog(x,y,lock));
        x = x + 2*fild;
        if((i + 1) % 4 == 0)
        {
            y = y + fild;
            if((i + 1)%8 != 0)
            {
                x = fild;
            }
            else
            {
                lock = true;
                x = 0;
            }
        }
    }
    x = 0;
    y = hight_wide - 3*fild;
    lock = false;
    for(int i = 0; i < pion_nr; i++)
    {
        piony_gracz.push_back(PionLog(x,y,lock));
        x = x + 2*fild;
        if((i + 1) % 4 == 0)
        {
            y = y + fild;
            if((i + 1)%8 != 0)
            {
                x = fild;
            }
            else
            {
                lock = true;
                x = 0;
            }
        }
    }
}

std::vector<std::pair<int, int>> Plansza::getPionyBot()
{
    /*
        Zwraca tablice zawierające wszystkie pozycje
        x,y kolekcji bota
        Słurzy do rysowania; 
    */
     std::vector<std::pair<int, int>> result_vector;
     for(int i = 0; i< piony_bot.size(); i++)
     {
        result_vector.push_back(std::pair{piony_bot[i].get_x() , piony_bot[i].get_y()});
     }
    return result_vector;
}

std::vector<std::pair<int, int>> Plansza::getPionyGracz()
{
    /*
        Zwraca tablice zawierające wszystkie pozycje
        x,y kolekcji gracza
        Słurzy do rysowania; 
    */
     std::vector<std::pair<int, int>> result_vector;
     for(int i = 0; i< piony_gracz.size(); i++)
     {
        result_vector.push_back(std::pair{piony_gracz[i].get_x() , piony_gracz[i].get_y()});
     }
    return result_vector;
}
bool Plansza::moveLeftPlayer(int index)
{
    if(piony_gracz[index].get_lock() == false || piony_gracz[index].get_x() != 0 || piony_gracz[index].get_y() != 0)
    {
        for(int i = 0; i<piony_gracz.size(); i++)
        {
            if(piony_gracz[i].get_x() == (piony_gracz[index].get_x() - fild) && piony_gracz[i].get_y() == (piony_gracz[index].get_y() - fild))
            {
                return false;
            }
        }
        for(int i = 0; i<piony_bot.size(); i++)
        {
        if(piony_bot[i].get_x() == (piony_gracz[index].get_x() - fild) && piony_bot[i].get_y() == (piony_gracz[index].get_y() - fild))
            {
                return false;
            }
        }
        piony_gracz[index].set_pos((piony_gracz[index].get_x() - fild),(piony_gracz[index].get_y() - fild));
        return true;
    }
    return false;
}
