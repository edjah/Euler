#include "lib/utility.h"

#define JACK 11
#define QUEEN 12
#define KING 13
#define ACE 14

typedef enum Suit {
    Clubs,
    Hearts,
    Diamond,
    Spades,
} Suit;

typedef enum Rank {
    HighCard,
    OnePair,
    TwoPairs,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush,
} Rank;

typedef struct HandResult {
    Rank rank;
    int strength;
} HandResult;

typedef struct Card {
    int value;
    int suit;
} Card;

// returns an array of 5 cards
Card* parse_hand(char** string_ptr) {
    Card* cards = calloc(5, sizeof(Card));

    for (int i = 0; i < 5; ++i) {
        char* card_repr = strsep(string_ptr, " ");
        assert(card_repr != NULL && strlen(card_repr) >= 2);

        // getting the value of the card
        switch (card_repr[0]) {
            case 'T':
                cards[i].value = 10;
                break;
            case 'J':
                cards[i].value = JACK;
                break;
            case 'Q':
                cards[i].value = QUEEN;
                break;
            case 'K':
                cards[i].value = KING;
                break;
            case 'A':
                cards[i].value = ACE;
                break;
            default:
                assert(isdigit(card_repr[0]));
                cards[i].value = card_repr[0] - '0';
                break;
        }

        // getting the suit
        switch (card_repr[1]) {
            case 'C':
                cards[i].suit = Clubs;
                break;
            case 'H':
                cards[i].suit = Hearts;
                break;
            case 'D':
                cards[i].suit = Diamond;
                break;
            case 'S':
                cards[i].suit = Spades;
                break;
            default:
                fprintf(stderr, "Unexpected suit \"%c\"\n", card_repr[1]);
                abort();
        }
    }

    // sorting the cards in ascending order
    INSERTION_SORT(cards, 5, /*sort_key=*/.value);

    return cards;
};

HandResult test_of_a_kind(Card* cards, int num, Rank rank) {
    for (int start_idx = 5 - num; start_idx >= 0; --start_idx) {
        bool success = true;
        int value = cards[start_idx].value;
        for (int i = start_idx; i < start_idx + num; ++i) {
            if (cards[i].value != value) {
                success = false;
            }
        }

        if (success) {
            return (HandResult) {.rank = rank, .strength = value};
        }
    }
    return (HandResult) {.rank = -1, .strength = -1};
}


HandResult hand_result(Card* cards) {
    bool success;
    int start_value = cards[0].value;
    int suit = cards[0].suit;

    // test royal flush
    success = true;
    for (int i = 0; i < 5; ++i) {
        if (cards[i].suit != suit || cards[i].value != 10 + i) {
            success = false;
        }
    }
    if (success) {
        return (HandResult) {.rank = RoyalFlush, .strength = 420};
    }

    // test straight flush
    success = true;
    for (int i = 0; i < 5; ++i) {
        if (cards[i].suit != suit || cards[i].value != start_value + i) {
            success = false;
        }
    }
    if (success) {
        return (HandResult) {.rank = StraightFlush, .strength = start_value};
    }

    // test four of a kind
    HandResult four_of_a_kind_test = test_of_a_kind(cards, 4, FourOfAKind);
    if (four_of_a_kind_test.rank != -1) {
        return four_of_a_kind_test;
    }

    // test full house
    if (cards[0].value == cards[1].value && cards[1].value == cards[2].value &&
        cards[3].value == cards[4].value) {
        return (HandResult) {.rank = FullHouse, .strength = cards[0].value};
    }
    if (cards[2].value == cards[3].value && cards[3].value == cards[4].value &&
        cards[0].value == cards[1].value) {
        return (HandResult) {.rank = FullHouse, .strength = cards[2].value};
    }

    // test flush
    success = true;
    for (int i = 0; i < 5; ++i) {
        if (cards[i].suit != suit) {
            success = false;
        }
    }
    if (success) {
        return (HandResult) {.rank = Flush, .strength = cards[4].value};
    }

    // test straight
    success = true;
    for (int i = 0; i < 5; ++i) {
        if (cards[i].value != start_value + i) {
            success = false;
        }
    }
    if (success) {
        return (HandResult) {.rank = Straight, .strength = cards[4].value};
    }

    // test three of a kind
    HandResult three_of_a_kind_test = test_of_a_kind(cards, 3, ThreeOfAKind);
    if (three_of_a_kind_test.rank != -1) {
        return three_of_a_kind_test;
    }

    // test two pairs
    for (int i = 0; i < 4; ++i) {
        if (cards[i].value == cards[i + 1].value) {
            for (int j = i + 2; j < 4; ++j) {
                if (cards[j].value == cards[j + 1].value) {
                    return (HandResult) {.rank = TwoPairs, .strength = cards[j].value};
                }
            }
        }
    }

    // test one pair
    HandResult one_pair_test = test_of_a_kind(cards, 2, OnePair);
    if (one_pair_test.rank != -1) {
        return one_pair_test;
    }

    // default to high card
    return (HandResult) {.rank = HighCard, .strength = cards[4].value};
}

bool first_has_high_card(Card* hand1, Card* hand2) {
    for (int i = 4; i >= 0; --i) {
        if (hand1[i].value != hand2[i].value) {
            return hand1[i].value > hand2[i].value;
        }
    }
    fprintf(stderr, "There is no clear winner!\n");
    abort();
}

int main(void) {
    start_time();

    FILE* fp = fopen("files/p054_poker.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open: files/p054_poker.txt\n");
        return 1;
    }

    int player1_wins = 0;
    char line_buf[128];
    char* s;
    while ((s = fgets(line_buf, sizeof(line_buf), fp)) != NULL) {
        Card* hand1 = parse_hand(&s);
        Card* hand2 = parse_hand(&s);
        HandResult r1 = hand_result(hand1);
        HandResult r2 = hand_result(hand2);

        if (r1.rank > r2.rank) {
            player1_wins += 1;
        } else if (r1.rank == r2.rank) {
            if (r1.strength > r2.strength) {
                player1_wins += 1;
            } else if (r1.strength == r2.strength) {
                player1_wins += first_has_high_card(hand1, hand2);
            }
        }
    }

    fclose(fp);
    printf("Solution: %d\n", player1_wins);
    end_time();
}
