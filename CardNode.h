//
// Created by 97254 on 21/02/2024.
//

#ifndef UNTITLED9_CARDNODE_H
#define UNTITLED9_CARDNODE_H

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define MOVE_4_BYTES 4
#define FIRST_4_BITS 0b00001111
#define LAST_4_BITS 0b11110000
#define Number_OF_SUITS 4
#define MAX_STR 30


enum Suits {Hearts, Clubs, Diamonds, Spades};

typedef enum Rank{ Ace = 1, TWO, THREE, FOUR, FIVE,
    SIX, SEVEN, EIGHT, NINE, TEN,
    Jack, Queen, King} Ranks;

typedef struct card{
    uint8_t data;
    bool is_ace;
    struct card *next;
}CardNode;


uint8_t decode_data(uint8_t rank, uint8_t suit); // to set the values in the suitable bits
CardNode* create_node(uint8_t rank, uint8_t suit);
uint8_t get_rank(CardNode* card);
uint8_t get_suit(CardNode* card);
enum Suits get_suit_str(CardNode* card);
uint8_t get_face_value(CardNode *card);
void draw_card(CardNode* card);

#endif //UNTITLED9_CARDNODE_H
