#ifndef BOT_H_
#define BOT_H_
#include "Judge.hpp"
#include <memory>
class Bot : public Judge
{
    private:
        struct Node
        {
            Plansza curent;
            std::vector<std::unique_ptr<Node>> posiblitis;
            double value;
            bool is_bot_turn;
            double alpha;
            double betha;
            Node(): value{0}, alpha{-1000}, betha{1000}{};
        };
        const int MAX_DEPHT{4};
        std::unique_ptr<Node> startingNode;
        Judge judge;
        //metody prywatne
        int Search(std::unique_ptr<Node> &ptr, int depht, double alpha, double betha);
        void moveSimulation(std::unique_ptr<Node> &ptr, bool is_bot, int depht);
        double evaluation(Plansza plansza);
        bool botRightAttacer(Plansza &plansza, int index);
        
    public:
        Plansza makeMove(Plansza sytuacja);

};
#endif/*BOT_H_*/