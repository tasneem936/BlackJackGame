//
// Created by 97254 on 22/02/2024.
//

#include "GameState.h"

void init_state(Game *game,int pot,int cash)
{
    game->deck = malloc(sizeof(CardList));
    game->dealerHand = malloc(sizeof(CardList));
    game->playerHand = malloc(sizeof(CardList));

    fill_list(game->deck);
    init_list(game->playerHand);
    init_list(game->dealerHand);

    game->pot = pot;
    game->cash = cash;
}
void betting_state(Game* game){
    int pot = game->pot;
    int cash = game->cash;
    
    printf("Pot is : %d \nCash is : %d\n",pot,cash);

    if(pot == 0 && cash < MIN_OF_CASH ){
        printf("Game Over!\n");
        exit(0);
    }

    printf("How much money you will add to the pot ?\n");
    int to_add;
    while(1){

        scanf(" %d", &to_add);

        if(to_add < 0 || to_add%10 != 0){
            printf("Try again! enter a number that is a multiple of 10 and greater than 0: \n");
            continue;
        }
        else if(to_add > cash) {
            printf("You are out of cash! enter smaller number:\n");
            continue;
        }
        else if (to_add == 0 && game->pot > 0){
            break;
        }
        else{
            break;
        }
    }
    game->pot+=to_add;
    game->cash-=to_add;

}
/*
 * this function is the first phase of the game, its mission to
 * draw two cards for both : player and dealer. and then to print the list
 **/
void initial_state(Game *game){
    srand(time(NULL));
    int index, cardsNum;
    printf("*** START **** \n");

    // generate two card and add them to the player list
    index = rand() % CARDS_NUM;
    CardNode *firstCard = remove_at_list(game->deck,index);

    cardsNum = game->deck->len;
    index = rand() % cardsNum;
    CardNode *secCard = remove_at_list(game->deck,index);
    push_to_list(game->playerHand,firstCard);
    push_to_list(game->playerHand,secCard);

    // generate two card and add them to the dealer list
    cardsNum = game->deck->len;
    index = rand() % cardsNum;
    CardNode *thirdCard = remove_at_list(game->deck,index);

    cardsNum = game->deck->len;
    index = rand() % cardsNum;
    CardNode *forthCard = remove_at_list(game->deck,index);
    push_to_list(game->dealerHand,thirdCard);
    push_to_list(game->dealerHand,forthCard);

    // show the hands of the dealer and the player
    draw_list(game->playerHand,0);
    draw_list(game->dealerHand,1);
}
void blackjack_state(Game *game){
    int dealerValue, playerValue;
    playerValue = get_list_value(game->playerHand);
    if(playerValue == 21){
        player_wins(game);
        reset_cards(game);
    }
    else{
        hit_or_stand_state(game,playerValue);
    }
}
void hit_or_stand_state(Game* game,int score){
    char choice[MAX_STR];
    int index,cardsNum;

    while( score < 21 )
    {
            printf("Do you want to hit or stand? \n");
            scanf(" %s", choice);

            if (strcmp(choice, "hit") == 0)
            {
                cardsNum = game->deck->len;
                index = rand() % cardsNum;
                CardNode *new_card = remove_at_list(game->deck, index);
                push_to_list(game->playerHand, new_card);
                draw_list(game->playerHand, 0);
                score = get_list_value(game->playerHand);
            }
            else if (strcmp(choice, "stand") == 0)
            {
                dealer_draw_state(game,score);
                break;
                // dealer draw
            }
            else
            {
                printf("Invalid choice. try again! \n");
            }
    }

    if(score > 21){ //print that player bust
        player_bust(game);
        reset_cards(game);
    }
    if(score == 21){
        player_wins(game);
        reset_cards(game);
    }

}
void dealer_draw_state(Game *game,int playerValue){
    int dealerValue = get_list_value(game->dealerHand);
    if (playerValue < dealerValue && dealerValue <= 21 && dealerValue > 17)
    {
        draw_list(game->dealerHand, 2);
        dealer_wins(game);
        //print you lose & pot = 0
    }
    else
    {
        int index,cardsNum;
        while( playerValue > dealerValue || dealerValue < 17  )
        {
            cardsNum = game->deck->len;
            index = rand() % cardsNum;
            CardNode *new_card = remove_at_list(game->deck, index);
            push_to_list(game->dealerHand, new_card);
            draw_list(game->dealerHand, 2);
            dealerValue = get_list_value(game->dealerHand);
        }

        if(dealerValue >= 17 && dealerValue <= 21){
            if(dealerValue > playerValue){
                dealer_wins(game);
            }
            else if (dealerValue == playerValue){
                printf("Tie!**\n");
                // pot will keep the same
            }
            else{
                player_wins(game);

            }
        }
        if(dealerValue > 21)
        {
            dealer_bust(game);
        }

    }
    reset_cards(game);
}
void reset_cards(Game *game){
    printf("Pay attention -> Current pot: %d -- Current cash: %d\n",game->pot,game->cash);
    clear_list(game->dealerHand);
    clear_list(game->playerHand);
    clear_list(game->deck);
    init_list(game->deck);
    fill_list(game->deck);

    if(game->cash < MIN_OF_CASH){
        printf("Game over ! \n");
        exit(0);
    }
}
void dealer_wins(Game *game){
    printf("Dealer wins!!! \n");
    game->pot = 0;

}
void player_bust(Game * game){
    printf("You Bust!!\n");
    game->pot = 0;
}
void player_wins(Game *game){
    printf("Black Jack!!! \n");
    int pot = game->pot;
    game->cash += (pot*2.5);
    game->pot = 0;
}
void dealer_bust(Game *game){
    printf("Dealer Bust :|\n");
    int pot = game->pot;
    pot*=2;
    game->cash+=pot;
    game->pot = 0;
}