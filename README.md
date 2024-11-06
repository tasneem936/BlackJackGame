## BlackJack Game - human player vs. computer controlled dealer

This project implements a simplified version of the classic BlackJack game in C, with a few added challenges. The game is played with a single shared deck, starting each game with all possible cards (order doesn’t matter). Each player (the dealer and the human player) begins with an empty hand, which is filled by drawing cards from the deck as the game progresses. At the end of the game, the hands are returned to the deck.

# Card Representation
The game uses a standard deck of playing cards, with each card having:
- A rank: Ace, 2, 3, …, 9, 10, Jack, Queen, King.
- A suit: Hearts ♥, Clubs ♣, Diamonds ♦, and Spades ♠.

# Card Structure in Code
Each card is represented as a Card struct, which serves as both a data holder and a linked list node. The struct includes two fields:

- data: Encodes both suit and rank in an 8-bit (uint8_t) format:
> The lower 4 bits (bits 3:0) represent the suit.
> The upper 4 bits (bits 7:4) represent the rank.
- next: A pointer to the next card in the list. In this encoding:
> Suit values are not stored as a separate field but are encoded within data.
> Rank values are also encoded within data.
