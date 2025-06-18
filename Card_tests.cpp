// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_card_suit_and_rank) {
    // test function Card::Card()
    Card two_spades = Card();
    ASSERT_EQUAL(two_spades.get_rank(), Card::RANK_TWO);
    ASSERT_EQUAL(two_spades.get_suit(), Card::SUIT_SPADES);
    
    // test function get_rank and get_suit
    // test left bower
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(jack_hearts.get_rank(), Card::RANK_JACK);
    ASSERT_EQUAL(jack_hearts.get_suit(), Card::SUIT_HEARTS);
    ASSERT_EQUAL(jack_hearts.get_suit(Card::SUIT_DIAMONDS), Card::SUIT_DIAMONDS);
    
    // test right bower
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(jack_clubs.get_rank(), Card::RANK_JACK);
    ASSERT_EQUAL(jack_clubs.get_suit(), Card::SUIT_CLUBS);
    ASSERT_EQUAL(jack_clubs.get_suit(Card::SUIT_CLUBS), Card::SUIT_CLUBS);
}

TEST(test_card_type) {
    // nothing - not face
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(nine_diamonds.is_face());
    ASSERT_FALSE(nine_diamonds.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(nine_diamonds.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(nine_diamonds.is_trump(Card::SUIT_CLUBS));
    ASSERT_FALSE(nine_diamonds.is_trump(Card::SUIT_HEARTS));
    ASSERT_TRUE(nine_diamonds.is_trump(Card::SUIT_DIAMONDS));

    
    // face - queen (not a trump)
    Card queen_clubs = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_TRUE(queen_clubs.is_face());
    ASSERT_FALSE(queen_clubs.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(queen_clubs.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(queen_clubs.is_trump(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(queen_clubs.is_trump(Card::SUIT_SPADES));
    
    
    // face - king (a trump)
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_TRUE(king_hearts.is_face());
    ASSERT_FALSE(king_hearts.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(king_hearts.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(king_hearts.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(king_hearts.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_TRUE(king_hearts.is_trump(Card::SUIT_HEARTS));
    
    
    // face - special condition: ace
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_TRUE(ace_spades.is_face());
    ASSERT_FALSE(ace_spades.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(ace_spades.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(ace_spades.is_right_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(ace_spades.is_left_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(ace_spades.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(ace_spades.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(ace_spades.is_right_bower(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(ace_spades.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(ace_spades.is_trump(Card::SUIT_CLUBS));
    ASSERT_FALSE(ace_spades.is_trump(Card::SUIT_HEARTS));
    ASSERT_TRUE(ace_spades.is_trump(Card::SUIT_SPADES));
    
    // bower - jack
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(ace_spades.is_face());
    ASSERT_TRUE(jack_clubs.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(jack_clubs.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(jack_clubs.is_right_bower(Card::SUIT_SPADES));
    ASSERT_TRUE(jack_clubs.is_left_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(jack_clubs.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(jack_clubs.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(jack_clubs.is_right_bower(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(jack_clubs.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_TRUE(jack_clubs.is_trump(Card::SUIT_CLUBS));
    ASSERT_FALSE(jack_clubs.is_trump(Card::SUIT_HEARTS));
    ASSERT_TRUE(jack_clubs.is_trump(Card::SUIT_SPADES));
}

TEST(test_card_comparison) {
    // normal case
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(nine_diamonds < jack_spades);
    ASSERT_TRUE(nine_diamonds <= jack_spades);
    ASSERT_FALSE(nine_diamonds > jack_spades);
    ASSERT_FALSE(nine_diamonds >= jack_spades);
    ASSERT_FALSE(nine_diamonds == jack_spades);
    ASSERT_TRUE(nine_diamonds != jack_spades);
    
    // same rank - king
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_TRUE(king_spades < king_hearts);
    ASSERT_TRUE(king_spades <= king_hearts);
    ASSERT_FALSE(king_spades > king_hearts);
    ASSERT_FALSE(king_spades >= king_hearts);
    ASSERT_FALSE(king_spades == king_hearts);
    ASSERT_TRUE(king_spades != king_hearts);
    
    // same suit - clubs
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card ace_clubs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_TRUE(ten_clubs < ace_clubs);
    ASSERT_TRUE(ten_clubs <= ace_clubs);
    ASSERT_FALSE(ten_clubs > ace_clubs);
    ASSERT_FALSE(ten_clubs >= ace_clubs);
    ASSERT_FALSE(ten_clubs == ace_clubs);
    ASSERT_TRUE(ten_clubs != ace_clubs);
}

TEST(test_suit_next) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES), Card::SUIT_CLUBS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);
}

TEST(test_card_less_no_led) {
    // both cards are trump - no jack
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card nine_clubs = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_FALSE(Card_less(ten_clubs, nine_clubs, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(nine_clubs, ten_clubs, Card::SUIT_CLUBS));
    
    // both cards are trump - jack and ace
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_FALSE(Card_less(jack_hearts, ace_hearts, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(ace_hearts, jack_hearts, Card::SUIT_HEARTS));
    
    // both cards are trump - jack and ten
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_FALSE(Card_less(jack_hearts, ten_hearts, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(ten_hearts, jack_hearts, Card::SUIT_HEARTS));
    
    // jack - left vs. right bower
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(jack_spades, jack_clubs, Card::SUIT_SPADES));
                            
    // left bower and normal 1
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    ASSERT_FALSE(Card_less(jack_diamonds, king_spades, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(king_spades, jack_diamonds, Card::SUIT_HEARTS));
                            
    // left bower and normal 2
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_FALSE(Card_less(jack_diamonds, ten_spades, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(ten_spades, jack_diamonds, Card::SUIT_HEARTS));
    
    // right bower and normal 1 and 2
    ASSERT_FALSE(Card_less(jack_diamonds, ten_spades, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(ten_spades, jack_diamonds, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(jack_diamonds, king_spades, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(king_spades, jack_diamonds, Card::SUIT_DIAMONDS));
                           
    // one trump and one normal (equal rank)
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card queen_hearts = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_FALSE(Card_less(queen_diamonds, queen_hearts, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(queen_hearts, queen_diamonds, Card::SUIT_DIAMONDS));
                            
    // one trump and one normal (rank: trump > normal)
    Card queen_clubs = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(Card_less(queen_clubs, ten_diamonds, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(ten_diamonds, queen_clubs, Card::SUIT_CLUBS));
    
    // one trump and one normal (rank: trump < normal)
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(Card_less(nine_spades, ace_diamonds, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_diamonds, nine_spades, Card::SUIT_SPADES));

    // both normal
    ASSERT_TRUE(Card_less(nine_spades, ace_diamonds, Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(ace_diamonds, nine_spades, Card::SUIT_CLUBS));
}
                            
TEST(test_card_less_led_1) {
    // one led and one trump (rank: led > trump)
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(Card_less(ten_spades, queen_diamonds,
                           queen_diamonds, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(queen_diamonds, ten_spades,
                          queen_diamonds, Card::SUIT_SPADES));
    
    // one led and one trump (rank: led = trump)
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(Card_less(king_spades, king_diamonds,
                           king_diamonds, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(king_diamonds, king_spades,
                          king_diamonds, Card::SUIT_SPADES));
    
    // one led and one trump (rank: led < trump)
    ASSERT_TRUE(Card_less(ten_spades, queen_diamonds,
                           ten_spades, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(queen_diamonds, ten_spades,
                          ten_spades, Card::SUIT_DIAMONDS));
    
    // one led and one normal (rank: led > normal)
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(nine_spades, king_hearts,
                           king_hearts, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(king_hearts, nine_spades,
                          king_hearts, Card::SUIT_DIAMONDS));
        
    // one led and one normal (rank: led = normal)
    ASSERT_TRUE(Card_less(king_spades, king_diamonds,
                           king_diamonds, Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(king_diamonds, king_spades,
                          king_diamonds, Card::SUIT_HEARTS));
    
    // one led and one normal (rank: led < normal)
    ASSERT_FALSE(Card_less(nine_spades, king_hearts,
                          nine_spades, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(king_hearts, nine_spades,
                           nine_spades, Card::SUIT_DIAMONDS));
    }
        
TEST(test_card_less_led_2) {
    // one led and one left bower (rank: led > left bower)
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(Card_less(jack_spades, queen_diamonds,
                           queen_diamonds, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(queen_diamonds, jack_spades,
                          queen_diamonds, Card::SUIT_CLUBS));
        
    // one led and one left bower (rank: led = left bower)
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(Card_less(jack_spades, jack_diamonds,
                           jack_diamonds, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(jack_diamonds, jack_spades,
                          jack_diamonds, Card::SUIT_CLUBS));
        
    // one led and one left bower (rank: led < left bower)
    Card ten_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(Card_less(jack_spades, ten_diamonds,
                           ten_diamonds, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(ten_diamonds, jack_spades,
                          ten_diamonds, Card::SUIT_CLUBS));
    
    // one led and one right bower (rank: led > right bower)
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    ASSERT_FALSE(Card_less(jack_hearts, queen_spades,
                           queen_spades, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(queen_spades, jack_hearts,
                          queen_spades, Card::SUIT_HEARTS));
        
    // one led and one right bower (rank: led = right bower)
    ASSERT_FALSE(Card_less(jack_hearts, jack_spades,
                           jack_spades, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(jack_spades, jack_hearts,
                          jack_spades, Card::SUIT_HEARTS));
    
    // one led and one right bower (rank: led < right bower)
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_FALSE(Card_less(jack_hearts, ten_spades,
                           ten_spades, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(ten_spades, jack_hearts,
                          ten_spades, Card::SUIT_HEARTS));
        
    // led is left bower and right bower
    ASSERT_FALSE(Card_less(jack_hearts, jack_diamonds,
                           jack_diamonds, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(jack_diamonds, jack_hearts,
                          jack_diamonds, Card::SUIT_HEARTS));
    
    // led is right bower and left bower
    ASSERT_FALSE(Card_less(jack_hearts, jack_diamonds,
                          jack_hearts, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(jack_diamonds, jack_hearts,
                           jack_hearts, Card::SUIT_HEARTS));
    }


TEST_MAIN()
