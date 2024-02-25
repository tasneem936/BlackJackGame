//
// Created by 97254 on 22/02/2024.
//

#ifndef UNTITLED9_GAMESTATE_H
#define UNTITLED9_GAMESTATE_H


#define CARDS_NUM 52
#define MIN_OF_CASH 10
#include "CardList.h"
#include "CardNode.h"
#include <stdlib.h>
#include <time.h>

enum GameStates{DRAW,PLAYER_WIN,DEALER_WIN };

typedef struct Game{
    CardList *deck;
    CardList *dealerHand;
    CardList *playerHand;
    int pot;
    int cash;
}Game;

void init_state(Game *game,int pot, int cash);
void betting_state(Game *game);
void initial_state(Game *game);
void blackjack_state(Game *game);
void hit_or_stand_state(Game* game,int score);
void dealer_draw_state(Game *game,int playerValue);
void reset_cards(Game *game);

/* aux function */
void dealer_wins(Game *game);
void player_bust(Game *game);
void player_wins(Game *game);
void dealer_bust(Game* game);

#endif //UNTITLED9_GAMESTATE_H
