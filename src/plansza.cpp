#include "/home/tobiasz/GraAlgorytmy/include/plansza.hpp"
#include <iostream>

Plansza::Plansza()
{
    int x = fild;
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
                x = 0;
            }
            else
            {
                lock = true;
                x = fild;
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
/*Plansza::Plansza(const Plansza &other)
    : hight_wide(other.hight_wide),
    fild(other.fild),
    pion_nr(other.pion_nr),
    piony_gracz(other.piony_gracz),
    piony_bot(other.piony_bot)
{};
Plansza& Plansza::operator=(const Plansza &other)
{
    if (this != &other) 
    {
        piony_gracz = other.piony_gracz;
        piony_bot = other.piony_bot;
    }
    return *this;
    }
*/
Plansza::Plansza(const Plansza &other)
    : hight_wide(other.hight_wide),
    fild(other.fild),
    pion_nr(other.pion_nr),
    piony_gracz(), // Tworzymy nowy pusty wektor
    piony_bot()    // Tworzymy nowy pusty wektor
{
    // Kopiowanie elementów z wektora piony_gracz
    for (const auto& pion : other.piony_gracz) {
        piony_gracz.push_back(PionLog(pion.get_x(), pion.get_y(), pion.get_lock())); // Tworzymy głęboką kopię obiektu PionLog
    }

    // Kopiowanie elementów z wektora piony_bot
    for (const auto& pion : other.piony_bot) {
        piony_bot.push_back(PionLog(pion.get_x(), pion.get_y(), pion.get_lock())); // Tworzymy głęboką kopię obiektu PionLog
    }
}

Plansza& Plansza::operator=(const Plansza &other)
{
    if (this != &other) {
        /*hight_wide = other.hight_wide;
        fild = other.fild;
        pion_nr = other.pion_nr;*/

        // Czyszczenie istniejących danych w wektorach
        piony_gracz.clear();
        piony_bot.clear();

        // Kopiowanie elementów z wektora piony_gracz
        for (const auto& pion : other.piony_gracz) {
            piony_gracz.push_back(PionLog(pion.get_x(), pion.get_y(), pion.get_lock())); // Tworzymy głęboką kopię obiektu PionLog
        }

        // Kopiowanie elementów z wektora piony_bot
        for (const auto& pion : other.piony_bot) {
            piony_bot.push_back(PionLog(pion.get_x(), pion.get_y(), pion.get_lock())); // Tworzymy głęboką kopię obiektu PionLog
        }
    }
    return *this;
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
    if(piony_gracz[index].get_x() != 0 && piony_gracz[index].get_y() != 0)
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
bool Plansza::moveRightPlayer(int index)
{
    if(piony_gracz[index].get_x() <= hight_wide - 2*fild && piony_gracz[index].get_y() != 0)
    {
        for(int i = 0; i<piony_gracz.size(); i++)
        {
            if(piony_gracz[i].get_x() == (piony_gracz[index].get_x() + fild) && piony_gracz[i].get_y() == (piony_gracz[index].get_y() - fild))
            {
                return false;
            }
        }
        for(int i = 0; i<piony_bot.size(); i++)
        {
        if(piony_bot[i].get_x() == (piony_gracz[index].get_x() + fild) && piony_bot[i].get_y() == (piony_gracz[index].get_y() - fild))
            {
                return false;
            }
        }
        piony_gracz[index].set_pos((piony_gracz[index].get_x() + fild),(piony_gracz[index].get_y() - fild));
        return true;
    }
    return false;
}
std::pair<bool,int> Plansza::attactLeftPlayer(int index)
{
    int index_oponent = -1;
    if(piony_gracz[index].get_x() <= fild || piony_gracz[index].get_y() <= fild)
    {
        return std::make_pair(false,index_oponent);
    }
    for(int i = 0; i<piony_bot.size(); i++)
    {
        if(piony_bot[i].get_x() == (piony_gracz[index].get_x() - fild) && piony_bot[i].get_y() == (piony_gracz[index].get_y() - fild))
        {
            index_oponent = i;
            break;
        }
    }
    if(index_oponent != -1)
    {
        for(int i = 0; i<piony_gracz.size(); i++)
        {
            if(piony_gracz[i].get_x() == (piony_gracz[index].get_x() -2*fild) && piony_gracz[i].get_y() == (piony_gracz[index].get_y() - 2*fild))
            {
                return std::make_pair(false,index_oponent);
            }
        }
        for(int i = 0; i<piony_bot.size(); i++)
        {
        if(piony_bot[i].get_x() == (piony_gracz[index].get_x() - 2*fild) && piony_bot[i].get_y() == (piony_gracz[index].get_y() - 2*fild))
            {
                return std::make_pair(false,index_oponent);
            }
        }
        piony_gracz[index].set_pos((piony_gracz[index].get_x() - 2*fild),(piony_gracz[index].get_y() - 2*fild));
        piony_bot.erase(piony_bot.begin() + index_oponent);
        return std::make_pair(true,index_oponent);
    }
    return std::make_pair(false,index_oponent);
}
std::pair<bool, int> Plansza::attactRightPlayer(int index)
{
    int index_oponent = -1;
    if(piony_gracz[index].get_x() >= hight_wide -3*fild || piony_gracz[index].get_y() <= fild)
    {
        return std::make_pair(false,index_oponent);
    }
    for(int i = 0; i<piony_bot.size(); i++)
    {
        if(piony_bot[i].get_x() == (piony_gracz[index].get_x() + fild) && piony_bot[i].get_y() == (piony_gracz[index].get_y() - fild))
        {
            index_oponent = i;
            break;
        }
    }
    if(index_oponent != -1)
    {
        for(int i = 0; i<piony_gracz.size(); i++)
        {
            if(piony_gracz[i].get_x() == (piony_gracz[index].get_x() +2*fild) && piony_gracz[i].get_y() == (piony_gracz[index].get_y() - 2*fild))
            {
                return std::make_pair(false,index_oponent);
            }
        }
        for(int i = 0; i<piony_bot.size(); i++)
        {
        if(piony_bot[i].get_x() == (piony_gracz[index].get_x() + 2*fild) && piony_bot[i].get_y() == (piony_gracz[index].get_y() - 2*fild))
            {
                return std::make_pair(false,index_oponent);
            }
        }
        piony_gracz[index].set_pos((piony_gracz[index].get_x() + 2*fild),(piony_gracz[index].get_y() - 2*fild));
        piony_bot.erase(piony_bot.begin() + index_oponent);
        return std::make_pair(true,index_oponent);
    }
    return std::make_pair(false,index_oponent);
}
bool Plansza::moveLeftBot(int index)
{
    if(piony_bot[index].get_x() != 0 && piony_bot[index].get_y() != hight_wide - fild)
    {
        for(int i = 0; i<piony_gracz.size(); i++)
        {
            if(piony_gracz[i].get_x() == (piony_bot[index].get_x() - fild) && piony_gracz[i].get_y() == (piony_bot[index].get_y() + fild))
            {
                return false;
            }
        }
        for(int i = 0; i<piony_bot.size(); i++)
        {
        if(piony_bot[i].get_x() == (piony_bot[index].get_x() - fild) && piony_bot[i].get_y() == (piony_bot[index].get_y() + fild))
            {
                return false;
            }
        }
        piony_bot[index].set_pos((piony_bot[index].get_x() - fild),(piony_bot[index].get_y() + fild));
        return true;
    }
    return false;
}
bool Plansza::moveRightBot(int index)
{
    if(piony_bot[index].get_x() != hight_wide - fild && piony_bot[index].get_y() != hight_wide - fild)
    {
        for(int i = 0; i<piony_gracz.size(); i++)
        {
            if(piony_gracz[i].get_x() == (piony_bot[index].get_x() + fild) && piony_gracz[i].get_y() == (piony_bot[index].get_y() + fild))
            {
                return false;
            }
        }
        for(int i = 0; i<piony_bot.size(); i++)
        {
        if(piony_bot[i].get_x() == (piony_bot[index].get_x() + fild) && piony_bot[i].get_y() == (piony_bot[index].get_y() + fild))
            {
                return false;
            }
        }
        piony_bot[index].set_pos((piony_bot[index].get_x() + fild),(piony_bot[index].get_y() + fild));
        return true;
    }
    return false;
}
std::pair<bool, int> Plansza::attactLeftBot(int index)
{
    int index_oponent = -1;
    if(piony_bot[index].get_x() <= fild || piony_bot[index].get_y() >= hight_wide - 3*fild)
    {
        return std::make_pair(false,index_oponent);
    }
    for(int i = 0; i<piony_gracz.size(); i++)
    {
        if(piony_gracz[i].get_x() == (piony_bot[index].get_x() - fild) && piony_gracz[i].get_y() == (piony_bot[index].get_y() + fild))
        {
            index_oponent = i;
            break;
        }
    }
    if(index_oponent != -1)
    {
        for(int i = 0; i<piony_bot.size(); i++)
        {
            if(piony_bot[i].get_x() == (piony_bot[index].get_x() -2*fild) && piony_bot[i].get_y() == (piony_bot[index].get_y() + 2*fild))
            {
                return std::make_pair(false,index_oponent);
            }
        }
        for(int i = 0; i<piony_gracz.size();i++)
        {
        if(piony_gracz[i].get_x() == (piony_bot[index].get_x() - 2*fild) && piony_gracz[i].get_y() == (piony_bot[index].get_y() + 2*fild))
            {
                return std::make_pair(false,index_oponent);
            }
        }
        piony_bot[index].set_pos((piony_bot[index].get_x() - 2*fild),(piony_bot[index].get_y() + 2*fild));
        piony_gracz.erase(piony_gracz.begin() + index_oponent);
        return std::make_pair(true,index_oponent);
    }
    return std::make_pair(false,index_oponent);
}
std::pair<bool, int> Plansza::attactRightBot(int index)
{
    int index_oponent = -1;
    if(piony_bot[index].get_x() >= hight_wide -3 * fild || piony_bot[index].get_y() >= hight_wide - 3*fild)
    {
        return std::make_pair(false,index_oponent);
    }
    for(int i = 0; i<piony_gracz.size(); i++)
    {
        if(piony_gracz[i].get_x() == (piony_bot[index].get_x() + fild) && piony_gracz[i].get_y() == (piony_bot[index].get_y() + fild))
        {
            index_oponent = i;
            break;
        }
    }
    if(index_oponent != -1)
    {
        for(int i = 0; i<piony_bot.size(); i++)
        {
            if(piony_bot[i].get_x() == (piony_bot[index].get_x() +2*fild) && piony_bot[i].get_y() == (piony_bot[index].get_y() + 2*fild))
            {
                return std::make_pair(false,index_oponent);
            }
        }
        for(int i = 0; i<piony_gracz.size();i++)
        {
        if(piony_gracz[i].get_x() == (piony_bot[index].get_x() + 2*fild) && piony_gracz[i].get_y() == (piony_bot[index].get_y() + 2*fild))
            {
                return std::make_pair(false,index_oponent);
            }
        }
        piony_bot[index].set_pos((piony_bot[index].get_x() + 2*fild),(piony_bot[index].get_y() + 2*fild));
        piony_gracz.erase(piony_gracz.begin() + index_oponent);
        return std::make_pair(true,index_oponent);
    }
    return std::make_pair(false,index_oponent);
}
