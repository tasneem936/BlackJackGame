#include <stdio.h>
#include "CardList.h"
#include "GameState.h"
#define MAX_STR_MAIN 10
#define INIT_CASH 1000

int main() {
    char choice[MAX_STR];
    CardList *deck = malloc(sizeof(CardList));
    Game *game = malloc(sizeof(Game));
    int last_pot = 0, last_cash = INIT_CASH;
    while(1) {
        init_list(deck);
        fill_list(deck);
        init_state(game,last_pot,last_cash);
        betting_state(game);
        initial_state(game);
        blackjack_state(game);
        printf("Do you want to bit again? \n");
        scanf(" %s", choice);
        if (strcmp(choice, "yes") == 0){
            last_cash = game->cash;
            last_pot = game-> pot;
            continue;
        }
        if(strcmp(choice, "no") == 0){
            break;
        }
    }
    return 0;
}
