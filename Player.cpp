// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <string>
#include <vector>
#include <algorithm>
#include "Card.h"
#include "Player.h"


class SimplePlayer : public Player {
  public:
    // constructor
    SimplePlayer(std::string _name) {
        name = _name;
    }
    
    //EFFECTS returns player's name
    const std::string & get_name() const {
        return name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) {
        hand.push_back(c);
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                            int round, std::string &order_up_suit) const {
        // recording how many trump face cards the player has
        int count = 0;
        if (round == 1) {
            for (size_t i = 0; i < hand.size(); i++) {
                if (hand[i].is_trump(upcard.get_suit()) && hand[i].is_face()) {
                    count++;
                }
            }
            // the player will order up
            if (count >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
        }
        else if (round == 2) {
            // if the player is the dealer, the player is forced to order up
            if (is_dealer) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            for (size_t i = 0; i < hand.size(); i++) {
                if (hand[i].is_trump(Suit_next(upcard.get_suit())) &&
                    hand[i].is_face()) {
                    count++;
                }
                if (count >= 1) {
                    order_up_suit = Suit_next(upcard.get_suit());
                    return true;
                }
            }
        }
        return false;
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) {
        // add the one card in the hand
        hand.push_back(upcard);
        Card min_card = hand[0];
        int index = 0;;
        for (int i = 0; (unsigned) i < hand.size(); i++) {
            if (Card_less(hand[i], min_card, upcard.get_suit())) {
                min_card = hand[i];
                index = i;
            }
        }
        // removes the smallest weight of card from the hand
        hand.erase(hand.begin() + index);
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(const std::string &trump) {
        // both are two of spades
        Card trump_card;
        Card nontrump_card;
        int trump_index = 0;
        int nontrump_index = 0;
        
        for (int i = 0; (unsigned) i < hand.size(); i++) {
            if (hand[i].is_trump(trump)) {
                // it means all of the cards are trump
                if (Card_less(trump_card, hand[i], trump)) {
                    trump_card = hand[i];
                    trump_index = i;
                }
            }
            else {
                if (nontrump_card < hand[i]) {
                    nontrump_card = hand[i];
                    nontrump_index = i;
                }
            }
        }
        // lead trump or nontrump
        if (nontrump_card.get_suit() == Card::SUIT_SPADES &&
            nontrump_card.get_rank() == Card::RANK_TWO) {
            hand.erase(hand.begin() + trump_index);
            return trump_card;
        }
        else {
            hand.erase(hand.begin() + nontrump_index);
            return nontrump_card;
        }
    }
    

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump) {
        Card max_card;
        Card min_card = hand[0];
        int min_index = 0;
        int max_index = 0;
        
        for (int i = 0; (unsigned) i < hand.size(); i++) {
            // player can follow suit: play the highest card that follows suit
            if (hand[i].get_suit(trump) == led_card.get_suit(trump)) {
                if (Card_less(max_card, hand[i], trump)
                    || max_card.get_rank() == Card::RANK_TWO) {
                    max_card = hand[i];
                    max_index = i;
                }
            }
            else if (hand[i].get_suit(trump) != led_card.get_suit(trump)) {
                if (Card_less(hand[i], min_card, trump)) {
                    min_card = hand[i];
                    min_index = i;
                }
            }
        }
        // see to return card or min_card
        if (max_card.get_rank() == Card::RANK_TWO) {
            hand.erase(hand.begin() + min_index);
            return min_card;
        }
        else {
            hand.erase(hand.begin() + max_index);
            return max_card;
        }
    }

    // Maximum number of cards in a player's hand
    static const int MAX_HAND_SIZE = 5;

    // Needed to avoid some compiler errors
    ~SimplePlayer() {}
    
  private:
    std::string name;
    std::vector<Card> hand;
};

class HumanPlayer : public Player {
  public:
    // constructor
    HumanPlayer(std::string _name) {
        name = _name;
    }
    
    // Add: effect is to return hand
    const std::vector<Card> & get_hand() const {
        return hand;
    }
    
    //EFFECTS returns player's name
    const std::string & get_name() const {
        return name;
    }
    
    // Print functions
    void human_print_hand() const {
        const std::vector<Card>& hand = get_hand();
        for (int i = 0; (unsigned) i < hand.size(); i++) {
            std::cout << "Human player " << get_name() << "'s hand: "
            << "[" << i << "] " << hand[i] << std::endl;
        }
    }
    
    void making_trump_print() const {
        std::cout << "Human player " << get_name()
        << ", please enter a suit, or \"pass\":" << std::endl;
    }
    
    void trick_taking_print() const {
        std::cout << "Human player " << get_name()
        << ", please select a card:" << std::endl;
    }
    
    void add_discard_print() const {
        std::cout << "Discard upcard: [-1]" << std::endl;
        std::cout << "Human player " << get_name()
        << ", please select a card to discard:" << std::endl;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) {
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, std::string &order_up_suit) const {
        human_print_hand();
        making_trump_print();
        std::string suit;
        std::cin >> suit;
        if (suit == "pass") {
            return false;
        }
        else {
            order_up_suit = suit;
            return true;
        }
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) {
        human_print_hand();
        add_discard_print();
        int index;
        std::cin >> index;
        if (index != -1) {
            // removes the card
            hand.erase(hand.begin() + index);
            // adds one card
            hand.push_back(upcard);
        }
        std::sort(hand.begin(), hand.end());
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(const std::string &trump) {
        human_print_hand();
        trick_taking_print();
        int index;
        std::cin >> index;
        
        Card result = hand[index];
        hand.erase(hand.begin() + index);
       
        return result;
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump) {
        return lead_card(trump);
    }

    // Maximum number of cards in a player's hand
    static const int MAX_HAND_SIZE = 5;

    // Needed to avoid some compiler errors
    ~HumanPlayer() {}
    
private:
  std::string name;
  std::vector<Card> hand;
};



//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {
    // We need to check the value of strategy and return
    // the corresponding player type.
    if (strategy == "Simple") {
      // The "new" keyword dynamically allocates an object.
      return new SimplePlayer(name);
    }
    // when the strategy is human
    if (strategy == "Human") {
        return new HumanPlayer(name);
    }
    
    // Invalid strategy if we get here
    return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}

