#include "Judge.hpp"

int Judge::isBlockedBotPion(const Plansza &plansza, int index)
{
    /*
        Karzdy pion zwycajny ma 4 ruchy
        metoda zwraca wartość ilość dostępych ruchów
    */
    int wynik = 0;
    Plansza plansze[]{plansza,plansza,plansza,plansza};
    if(plansze[0].moveLeftBot(index) != false)
    {
        wynik++;
    }
    if(plansze[1].moveRightBot(index) != false)
    {
        wynik++;
    }
    if(plansze[2].attactLeftBot(index).first != false)
    {
        wynik++;
    }
    if(plansze[3].attactRightBot(index).first != false)
    {
        wynik++;
    }
    return wynik;  
}
int Judge::isBlockedGraczPion(const Plansza &plansza, int index)
{
    /*
        Karzdy pion zwycajny ma 4 ruchy
        metoda zwraca wartość ilość dostępych ruchów
    */
    int wynik = 0;
    Plansza plansze[]{plansza,plansza,plansza,plansza};
    if(plansze[0].moveLeftPlayer(index) != false)
    {
        wynik++;
    }
    if(plansze[1].moveRightPlayer(index) != false)
    {
        wynik++;
    }
    if(plansze[2].attactLeftPlayer(index).first != false)
    {
        wynik++;
    }
    if(plansze[3].attactRightPlayer(index).first != false)
    {
        wynik++;
    }
    return wynik;
    
}

int Judge::judging(Plansza plansza)
{
    /*
        Metoda sprawdzająca czy starcie jest zakończone
        1000 wygrana Gracz
        -1000 wygrana Bot
        500 remis
        0 kontynułujemy
    */
    if(plansza.getPionyBot().size() == 0)
    {
        return 1000;
    }
    else if(plansza.getPionyGracz().size() == 0)
    {
        return -1000;
    }
    int isBot = 0;
    for(int i = 0; i<plansza.getPionyBot().size(); i++)
    {
       isBot = isBlockedBotPion(plansza,i);
       if(isBot > 0)
       {
        break;
       }
    }
    int isGracz = 0;
    for(int i = 0; i<plansza.getPionyGracz().size(); i++)
    {
       isGracz = isBlockedGraczPion(plansza,i);
       if(isGracz > 0)
       {
        break;
       }
    }
    if(isBot == plansza.getPionyBot().size() && isGracz == plansza.getPionyGracz().size())
    {
        return 500;
    }
    else if(isBot == plansza.getPionyBot().size())
    {
        return 1000;
    }
    else if(isGracz == plansza.getPionyGracz().size())
    {
        return -1000;
    }

    return 0;
}
