#ifndef JUDGE_H_
#define JUDGE_H_
#include "plansza.hpp"
#include "PionLog.h"
/*
    Klasa sędziująca zawodom
*/
class Judge : public Plansza
{
    protected:
        int isBlockedBotPion(const Plansza &plansza, int index);
        int isBlockedGraczPion(const Plansza &plansza, int index);
    private:
        
    public:
        Judge(){};
        ~Judge(){};
        int judging(Plansza plansza);
};

#endif /*JUDGE_H_*/