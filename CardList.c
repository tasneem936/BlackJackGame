//
// Created by 97254 on 21/02/2024.
//

#include "CardList.h"

void fill_list(CardList* list){
    uint8_t rank,suit;
    for(Ranks r = Ace; r <= King; r++){
        rank = (uint8_t)r;
        for (size_t s = 0; s < Number_OF_SUITS; s++) {

            switch (s) {
                case Hearts:
                    suit = 1;
                    break;
                case Clubs:
                    suit = 2;
                    break;
                case Diamonds:
                    suit = 4;
                    break;
                case Spades:
                    suit = 8;
                    break;
            }
            CardNode* card = create_node(rank,suit);
            card->next = list->head;
            list->head = card;
            list->len++;
        }
    }
}
void init_list(CardList* list){
    list->head = NULL;
    list->len = 0;
}
void push_to_list(CardList *list,CardNode *card){
    card->next = list->head;
    list->head = card;
    list->len++;
}
CardNode* pop_list(CardList *list){
    if(list->head == NULL){
        return NULL;
    }
    CardNode *first_card = list->head;
    list->head = list->head->next;
    first_card->next = NULL;
    list->len--;
    return first_card;
}
void clear_list(CardList *list){
    if(list->head == NULL){
        return ;
    }
    CardNode *current = list->head;
    CardNode *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->len = 0;
}
CardNode* remove_at_list(CardList *list,size_t index){
    CardNode *node = NULL, *prev = NULL;
    CardNode *curr = list->head;

    while (curr!=NULL && index > 0){
        index--;
        prev = curr;
        curr = curr->next;
    }
    if(curr == NULL){
        return NULL;
    }

    if(prev == NULL){
        list->head = curr->next;
    }
    else{
        prev->next = curr->next;
    }

    node = curr;
    node->next = NULL;
    list->len--;
    return node;
}
/*----------------------------------------------------------------------//
 this function draw card and then print the cards in the given hand(in list)
 it has flag to help with the style of the print:
 flag = 1 means that this is the player hand
 flag = 0 means it is the dealer hand + hide the last card
 flag = 2 means it is the dealer hand + show all cards
//----------------------------------------------------------------------*/
void draw_list(CardList* list,int flag){
    if(!list){
        return;
    }

    if(flag){ // 0 or 2 means dealer
        printf("dealer: ");
    }
    else{
        printf("player: ");
    }

    size_t len = list->len;
    CardNode *curr = list->head;
    while (curr != NULL && len > 0){
        draw_card(curr);
        len > 1 ? printf(", "): printf("");
        curr = curr->next;
        len--;

        if(flag == 1 && len == 1){ // this will be printed only if it's dealer list
            printf("??????");
            break;
        }
    }
    printf("\n");
}
/*----------------------------------------------------------------------//
 this function calculate the value of the cards in the given hand
 it also handles the Ace issue, it counts how many Aces there is in the list
 and try to check if it will be better to use bonus value or not
//----------------------------------------------------------------------*/
int get_list_value(CardList *list){
    if(!list){
        return 0;
    }
    int value = 0,count = 0;
    size_t len = list->len;
    CardNode *curr = list->head;

    while (curr != NULL && len > 0) {
        value+=(int)get_face_value(curr);
        if(curr->is_ace == true){
            count++;
        }
        curr = curr->next;
        len--;
    }
    //------------------------
    //------ Handle ace  ------
    while(count >= 1){
        if(value >= 21 || value + BONUS_ACE > 21){
            break;
        }
        else {
            if(value + BONUS_ACE <= 21 ){
                value+=BONUS_ACE;
            }
        }
        count--;
    }
    //------------------------

    return value;
}