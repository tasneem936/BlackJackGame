//
// Created by 97254 on 21/02/2024.
//

#ifndef UNTITLED9_CARDLIST_H
#define UNTITLED9_CARDLIST_H


#include <stdbool.h>
#include "CardNode.h"
#define BONUS_ACE 10


typedef struct list{
    CardNode *head;
    int len;
}CardList;
void init_list(CardList* list); // empty list
void fill_list(CardList* list); // list filled with 52 card
void push_to_list(CardList *list,CardNode* card);
CardNode* pop_list(CardList *list);
CardNode* remove_at_list(CardList *list,size_t index);
void clear_list(CardList *head);
void draw_list(CardList *list,int flag);
int get_list_value(CardList *list);

#endif //UNTITLED9_CARDLIST_H
