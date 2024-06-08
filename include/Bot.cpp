#include "Bot.hpp"
#include <iostream>

int Bot::Search(std::unique_ptr<Node> &ptr, int depth, double alpha, double betha)
{
    /*
        Wywołania rekursywne dla bot i gracz karzdy wybiera najlepszą opcje

    */
    if (depth == 0 || judge.judging(ptr->curent) != 0) {
        return ptr->value;
    }
    if(ptr->is_bot_turn)
    {
        //double minEval = 1000;
        for(int i = 0; i<ptr->posiblitis.size(); i++)
        {
            double eval = Search(ptr->posiblitis[i], depth - 1, alpha, betha);
            //minEval = std::min(minEval, eval);
            betha = std::min(betha, eval);
            if (betha <= alpha) {
                break; 
            }
        }
        /*ptr->value = minEval;
        return minEval;*/
        ptr->value = betha;
        return betha;
    }
    else
    {
        //double maxEval = -1000;
        for(int i = 0; i<ptr->posiblitis.size(); i++)
        {
            //double maxEval;
            double eval = Search(ptr->posiblitis[i], depth - 1, alpha, betha);
            //maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (betha <= alpha) {
                break; 
            }
        }
        /*ptr->value = maxEval;
        return maxEval;*/
        ptr->value = alpha;
        return alpha;
    }
    
}

void Bot::moveSimulation(std::unique_ptr<Node> &ptr, bool is_bot, int depht)
{
    /*
        Sprawdza wszystkie możliwe opcje dla
        Danego Noda; 
    */
    Plansza plansza_judge = ptr->curent;
    int verditc = 0;
    verditc = judge.judging(plansza_judge);
    /*
        Jeżeli jest koniec głeębokość lub gra skończona;
    */
    if(depht == 0 || verditc != 0)
    {
        if(verditc == 0)
        {
            Plansza eval_plansza = ptr->curent;
            ptr->value = evaluation(eval_plansza);
        }
        else if(verditc == 500)
        {
            ptr->value  = 0;
        }
        else
        {
            ptr->value = verditc;
        }
        return;
    }
    bool res = false;
    if(is_bot == true)
    {
        for(int i = 0; i < ptr->curent.getPionyBot().size(); i++)
        {
            Plansza plansza_attac_left = ptr->curent;
            res = plansza_attac_left.attactLeftBot(i).first;
            if(res)
            {
                std::unique_ptr<Node> new_node =std::make_unique<Node>();
                new_node->curent = plansza_attac_left;
                new_node->is_bot_turn = false;
                new_node->value = 0;
                moveSimulation(new_node, new_node->is_bot_turn,depht - 1);
                ptr->posiblitis.push_back(std::move(new_node));
            }
            Plansza plansza_attac_right = ptr->curent;
            res = plansza_attac_right.attactRightBot(i).first;
            if(res)
            {
                std::unique_ptr<Node> new_node =std::make_unique<Node>();
                new_node->curent = plansza_attac_right;
                new_node->is_bot_turn = false;
                new_node->value = 0;
                moveSimulation(new_node, new_node->is_bot_turn,depht - 1);
                ptr->posiblitis.push_back(std::move(new_node));
            }
            Plansza plansza_mov_left = ptr->curent;
            res = plansza_mov_left.moveLeftBot(i);
            if(res)
            {
                std::unique_ptr<Node> new_node =std::make_unique<Node>();
                new_node->curent = plansza_mov_left;
                new_node->is_bot_turn = false;
                new_node->value = 0;
                moveSimulation(new_node, new_node->is_bot_turn,depht - 1);
                ptr->posiblitis.push_back(std::move(new_node));
                

            }
            Plansza plansza_mov_right = ptr->curent;
            res = plansza_mov_right.moveRightBot(i);
            if(res)
            {
                std::unique_ptr<Node> new_node =std::make_unique<Node>();
                new_node->curent = plansza_mov_right;
                new_node->is_bot_turn = false;
                new_node->value = 0;
                moveSimulation(new_node, new_node->is_bot_turn,depht - 1);
                ptr->posiblitis.push_back(std::move(new_node));

            }
        }
        
    }
    else
    {
        for(int i = 0; i < ptr->curent.getPionyGracz().size(); i++)
        {
            Plansza plansza_attac_left = ptr->curent;
            res = plansza_attac_left.attactLeftPlayer(i).first;
            if(res)
            {
                std::unique_ptr<Node> new_node =std::make_unique<Node>();
                new_node->curent = plansza_attac_left;
                new_node->is_bot_turn = true;
                new_node->value = 0;
                moveSimulation(new_node, new_node->is_bot_turn,depht - 1);
                ptr->posiblitis.push_back(std::move(new_node));
            }
            Plansza plansza_attac_right = ptr->curent;
            res = plansza_attac_right.attactRightPlayer(i).first;
            if(res)
            {
                std::unique_ptr<Node> new_node =std::make_unique<Node>();
                new_node->curent = plansza_attac_right;
                new_node->is_bot_turn = true;
                new_node->value = 0;
                moveSimulation(new_node, new_node->is_bot_turn,depht - 1);
                ptr->posiblitis.push_back(std::move(new_node));
            }
            Plansza plansza_mov_left = ptr->curent;
            res = plansza_mov_left.moveLeftPlayer(i);
            if(res)
            {
                std::unique_ptr<Node> new_node =std::make_unique<Node>();
                new_node->curent = plansza_mov_left;
                new_node->is_bot_turn = true;
                new_node->value = 0;
                moveSimulation(new_node, new_node->is_bot_turn,depht - 1);
                ptr->posiblitis.push_back(std::move(new_node));

            }
            Plansza plansza_mov_right = ptr->curent;
            res = plansza_mov_right.moveRightPlayer(i);
            if(res)
            {
                std::unique_ptr<Node> new_node =std::make_unique<Node>();
                new_node->curent = plansza_mov_right;
                new_node->is_bot_turn = true;
                new_node->value = 0;
                moveSimulation(new_node, new_node->is_bot_turn,depht - 1);
                ptr->posiblitis.push_back(std::move(new_node));

            }
        }
    }
}
double Bot::evaluation(Plansza plansza)
{
    /*int bot_value = 0;
    int blocval = 0;
    for(int i = 0;  i < plansza.getPionyBot().size(); i++)
    {
        //blocval = isBlockedBotPion(plansza, i);
        bot_value = bot_value + (-1/(blocval + 1));    
    };

    int gracz_value = 0;
    for(int i = 0;  i < plansza.getPionyGracz().size(); i++)
    {
        //blocval = isBlockedGraczPion(plansza, i);

        gracz_value = gracz_value + (1/(blocval + 1));
    };
    return(gracz_value + bot_value);*/
    double gr_nr = plansza.getPionyGracz().size();
    double bot_nr = plansza.getPionyBot().size();
    double wynik = gr_nr - bot_nr;
    return(wynik);
}
bool Bot::botRightAttacer(Plansza &plansza, int index)
{
    bool attac_result = false;
    attac_result = plansza.attactRightBot(index).first;
    return(attac_result);
};
Plansza Bot::makeMove(Plansza sytuacja)
{
    startingNode = std::make_unique<Node>();
    startingNode->curent = sytuacja;
    startingNode->is_bot_turn = true;
    startingNode->value = 0;
    moveSimulation(startingNode, true, MAX_DEPHT);
    double bestValue = 1000;
    int bestIndex = 0;

    Search(startingNode, MAX_DEPHT, -1000, 1000);
    for(int i = 0; i < startingNode->posiblitis.size(); i++)
    {
        if(startingNode->posiblitis[i]->value < bestValue)
        {
            bestValue = startingNode->posiblitis[i]->value;
            bestIndex = i;
        }
    }
    return Plansza(startingNode->posiblitis[bestIndex]->curent);
}
