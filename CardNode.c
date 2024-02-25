//
// Created by 97254 on 21/02/2024.
//

#include "CardNode.h"

uint8_t get_face_value(CardNode *card){
    uint8_t value = get_rank(card);
    uint8_t ten = 10;
    if(value > ten){
        value = ten;
    }
    return value;
}
/*----------------------------------------------------------------------//
 this function coded the data to be in one uint8_t variable that includes
 rank and suit
//----------------------------------------------------------------------*/
uint8_t decode_data(uint8_t rank, uint8_t suit){
    uint8_t digits_needed = (uint8_t)FIRST_4_BITS;
    uint8_t left_suit = suit & digits_needed;      // XXXX-SSSS
    uint8_t right_rank = rank & digits_needed;    //XXXX-RRRR
    uint8_t result = right_rank << MOVE_4_BYTES; // RRRR-0000
    result = result | left_suit;
    return result;                              // RRRR-SSSS
}
CardNode* create_node(uint8_t rank, uint8_t suit){
    uint8_t data = decode_data(rank,suit); // here data is based on rank and suit
    uint8_t one = 0b00000001;
    CardNode *new_node = malloc(sizeof(CardNode));
    new_node->data = data;
    new_node->next = NULL;
    if(rank == one){
        new_node->is_ace = true;
    }
    else{
        new_node->is_ace = false;
    }
    return new_node;
}
uint8_t get_rank(CardNode* card){
    uint8_t result = card->data;
    result = result >> MOVE_4_BYTES;
    return result;
}
uint8_t get_suit(CardNode* card){
    uint8_t result = card->data;
    result = result & FIRST_4_BITS;
    return result;
}
/*----------------------------------------------------------------------//
 Aux function - to help with the print style
//----------------------------------------------------------------------*/
enum Suits get_suit_str(CardNode* card){
    uint8_t result = card->data;
    result = result & FIRST_4_BITS;
    switch (result) {
        case 1:
           return Hearts;
        case 2:
            return Clubs;
        case 4:
            return Diamonds;
        case 8:
            return Spades;
    }
}
//----------------------------------------------------------------------//
/* this function handle the printing style of the cards of given list */
//----------------------------------------------------------------------//
void draw_card(CardNode* card){
    uint8_t rank = get_rank(card);
    uint8_t suit = get_suit(card);
    char str1[MAX_STR], str2[MAX_STR];
    if(rank > 10){
        switch (rank) {
            case Jack:
                memcpy(str1, "Jack", sizeof(str1));
                break;
            case Queen:
                memcpy(str1, "Queen", sizeof(str1));
                break;
            case King:
                memcpy(str1, "King", sizeof(str1));
                break;
        }
    }
    else{
        itoa(rank, str1, 10);
    }
    switch (get_suit_str(card)) {
        case Hearts:
            memcpy(str2, "Hearts", sizeof(str2));
            break;
        case Clubs:
            memcpy(str2, "Clubs", sizeof(str2));
            break;
        case Diamonds:
            memcpy(str2, "Diamonds", sizeof(str2));
            break;
        case Spades:
            memcpy(str2, "Spades", sizeof(str2));
            break;
    }

    printf("%s of %s ",str1,str2);
}