// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;


//EFFECTS Initializes Card to the Two of Spades
Card::Card() {
    rank = Card::RANK_TWO;
    suit = Card::SUIT_SPADES;
}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in) {
    rank = rank_in;
    suit = suit_in;
}

//EFFECTS Returns the rank
std::string Card::get_rank() const {
    return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const {
    return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const {
    if (is_left_bower(trump)) {
        return trump;
    }
    else {
        return suit;
    }
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const {
    if (rank == Card::RANK_JACK || rank == Card::RANK_QUEEN
        || rank == Card::RANK_KING || rank == Card::RANK_ACE) {
        return true;
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const {
    if (rank == Card::RANK_JACK && suit == trump) {
        return true;
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const {
    if (rank == Card::RANK_JACK && suit == Suit_next(trump)) {
        return true;
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const {
    if (suit == trump || is_left_bower(trump)) {
        return true;
    }
    else {
        return false;
    }
}



// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
    int i = 0;
    int j = 0;
    while (j < NUM_RANKS && i < NUM_SUITS) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[j] &&
            rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            // lhs and rhs have the same rank: needs to compare the suit
                // two sides can't be the same suit when the rank is the same
                if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i] &&
                    rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                    return false;
                }
                // lhs has a smaller suit
                else if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                    return true;
                }
                // rhs has smaller suit
                else if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                    return false;
                }
            }
        // lhs has a smaller rank
        else if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            return true;
        }
        // rhs has a smaller rank
        else if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            return false;
        }
        i++;
        if (i > 3) {
            i = 0;
            j++;
        }
    }
    return false;
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
    if (lhs < rhs || lhs == rhs) {
        return true;
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
    return !(lhs <= rhs);
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
    return !(lhs < rhs);
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
    if ((lhs.get_rank() == rhs.get_rank()) &&
        (lhs.get_suit() == rhs.get_suit())) {
        return true;
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
    return !(lhs == rhs);
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit) {
    if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    }
    else if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    }
    else if (suit == Card::SUIT_HEARTS) {
        return Card::SUIT_DIAMONDS;
    }
    else if (suit == Card::SUIT_DIAMONDS) {
        return Card::SUIT_HEARTS;
    }
    return "";
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump) {
    // see if card a and b are equal
    if (a == b) {
        return false;
    }
    // see if either card is a right bower (highest weight)
    // card a is the right bower, while card b isn't
    else if (a.is_right_bower(trump) && !b.is_right_bower(trump)) {
        return false;
    }
    // card b is the right bower, and card a isn't
    else if (!a.is_right_bower(trump) && b.is_right_bower(trump)) {
        return true;
    }
    // see if either card is a left brower
    // card a is the left bower, while card b isn't
    else if (a.is_left_bower(trump) && !b.is_left_bower(trump)) {
        return false;
    }
    // card b is the left bower, while card a isn't
    else if (!a.is_left_bower(trump) && b.is_left_bower(trump)) {
        return true;
    }
    // see if either card is a trump
    // card a is the trump, while card b isn't
    else if (a.is_trump(trump) && !b.is_trump(trump)) {
        return false;
    }
    // card b is the trump, while card a isn't
    else if (!a.is_trump(trump) && b.is_trump(trump)) {
        return true;
    }
    // both cards are or are not a trump
    else if ((a.is_trump(trump) && b.is_trump(trump)) ||
             (!a.is_trump(trump) && !b.is_trump(trump))) {
        if (a < b) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
    // card a is a led card and a right bower
    if (a.is_right_bower(trump)) {
        return false;
    }
    // card b is a led card and a right bower
    else if (b.is_right_bower(trump)) {
        return true;
    }
    // card a is a led card and card b is a trump card --> true
   if (a.get_suit() == led_card.get_suit() && b.is_trump(trump)
       && !a.is_trump(trump)) {
        return true;
    }
    // card a is a trump card and card b is a led card --> false
    else if (a.is_trump(trump) && b.get_suit() == led_card.get_suit()
             && !b.is_trump(trump)) {
        return false;
    }
    // card a is a led card and card b is neither a led or a trump
    if (a.get_suit() == led_card.get_suit() &&
        (!b.is_trump(trump) && !(b.get_suit() == led_card.get_suit()))) {
        return false;
    }
    // card a is neither a led or a trump and card b is a led
    else if (!a.is_trump(trump) && !(a.get_suit() == led_card.get_suit()) &&
             b.get_suit() == led_card.get_suit()) {
        return true;
    }
    // both cards are neither a led or a trump
    else {
        return Card_less(a, b, trump);
    }
    return false;
}
