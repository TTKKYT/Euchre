// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_player_insertion) {
  // Create a Human player
  Player * human = Player_factory("Ray", "Human");

  // Print the player using the stream insertion operator
  ostringstream oss1;
  oss1 << * human;

  // Verify that the output is the player's name
  ASSERT_EQUAL(oss1.str(), "Ray");

  // Create a Simple player
  Player * wendy = Player_factory("Wendy", "Simple");

  // Print the player using the stream insertion operator
  ostringstream oss2;
  oss2 << *wendy;
  ASSERT_EQUAL(oss2.str(), "Wendy");

  // Clean up players that were created using Player_factory()
  delete human;
  delete wendy;
}

TEST(test_simple_player_make_trump_1) {
    // Wendy's hand - two face trump cards
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

    // Wendy makes tump
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = wendy->make_trump(
    nine_spades,    // Upcard
    true,           // Wendy is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
    );

    // Verify Wendy's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);

    delete wendy;
}

TEST(test_simple_player_make_trump_2) {
    // Tim's hand - one face trump cards
    Player * tim = Player_factory("Tim", "Simple");
    tim->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    tim->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    tim->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    tim->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    tim->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

    // Tim makes tump
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = tim->make_trump(
    nine_spades,    // Upcard
    false,           // Tim is not the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
    );

    // Verify Tim's order up and trump suit
    ASSERT_FALSE(orderup);

    delete tim;
}

TEST(test_simple_player_make_trump_3) {
    // round 2
    // Wendy's hand - zero face trump cards
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

    // Wendy makes tump
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = wendy->make_trump(
    nine_spades,    // Upcard
    false,           // Wendy is also the dealer
    2,              // Second round
    trump           // Suit ordered up (if any)
    );

    // Verify Wendy's order up and trump suit
    ASSERT_FALSE(orderup);

    delete wendy;
}

TEST(test_simple_player_make_trump_4) {
    // round 2
    // Tim's hand - one face trump cards
    Player * tim = Player_factory("Tim", "Simple");
    tim->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    tim->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    tim->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    tim->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    tim->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

    // Tim makes tump
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = tim->make_trump(
    nine_spades,    // Upcard
    false,           // Tim is also the dealer
    2,              // Second round
    trump           // Suit ordered up (if any)
    );

    // Verify Tim's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

    delete tim;
}

TEST(test_simple_player_make_trump_5) {
    // round 2
    // Wendy's hand - zero face trump cards
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

    // Wendy makes tump
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = wendy->make_trump(
    nine_spades,    // Upcard
    true,           // Wendy is also the dealer
    2,              // Second round
    trump           // Suit ordered up (if any)
    );

    // Verify Wendy's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

    delete wendy;
}

TEST(test_simple_player_make_trump_6) {
    // round 2
    // Tim's hand - one face trump cards
    Player * tim = Player_factory("Tim", "Simple");
    tim->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    tim->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    tim->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    tim->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    tim->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

    // Tim makes tump
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = tim->make_trump(
    nine_spades,    // Upcard
    true,           // Tim is also the dealer
    2,              // Second round
    trump           // Suit ordered up (if any)
    );

    // Verify Tim's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

    delete tim;
}

TEST(test_simple_player_make_trump_7) {
    // Wendy's hand - one face trump cards
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));

    // Wendy makes tump
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = wendy->make_trump(
    nine_spades,    // Upcard
    true,           // Wendy is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
    );

    // Verify Wendy's order up and trump suit
    ASSERT_FALSE(orderup);

    delete wendy;
}

TEST(test_simple_player_make_trump_8) {
    // Wendy's hand - two face trump cards
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));

    // Wendy makes tump
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = wendy->make_trump(
    nine_spades,    // Upcard
    true,           // Wendy is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
    );

    // Verify Wendy's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);

    delete wendy;
}

TEST(test_simple_player_make_trump_9) {
    // Wendy's hand - two face trump cards
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));

    // Wendy makes tump
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = wendy->make_trump(
    nine_spades,    // Upcard
    true,           // Wendy is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
    );

    // Verify Wendy's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);

    delete wendy;
}

TEST(test_simple_player_make_trump_10) {
    // round 2
    // Wendy's hand - zero face trump cards
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

    // Wendy makes tump
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = wendy->make_trump(
    nine_spades,    // Upcard
    false,           // Wendy is also the dealer
    2,              // Second round
    trump           // Suit ordered up (if any)
    );

    // Verify Wendy's order up and trump suit
    ASSERT_FALSE(orderup);

    delete wendy;
}

TEST(test_simple_player_make_trump_11) {
    // Wendy's hand - one face trump cards
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));

    // Wendy makes tump
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = wendy->make_trump(
    nine_spades,    // Upcard
    false,           // Wendy is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
    );

    // Verify Wendy's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

    delete wendy;
}

TEST(test_simple_player_make_trump_12) {
    // Wendy's hand - one face trump cards
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));

    // Wendy makes tump
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = wendy->make_trump(
    nine_spades,    // Upcard
    false,           // Wendy is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
    );

    // Verify Wendy's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

    delete wendy;
}

TEST(test_simple_player_make_trump_13) {
    // Wendy's hand - one face trump cards
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));

    // Wendy makes tump
    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    string trump;
    bool orderup = wendy->make_trump(
    queen_diamonds,    // Upcard
    true,           // Wendy is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
    );

    // Verify Wendy's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

    delete wendy;
}

TEST(test_simple_player_make_trump_14) {
    // Wendy's hand - one face trump cards
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));

    // Wendy makes tump
    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    string trump;
    bool orderup = wendy->make_trump(
    queen_diamonds,    // Upcard
    true,           // Wendy is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
    );

    // Verify Wendy's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

    delete wendy;
}

TEST(test_simple_player_make_trump_15) {
    // Wendy's hand - one face trump cards
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));

    // Wendy makes tump
    Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
    string trump;
    bool orderup = wendy->make_trump(
    ten_spades,    // Upcard
    true,           // Wendy is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
    );

    // Verify Wendy's order up and trump suit
    ASSERT_FALSE(orderup);

    delete wendy;
}

TEST(test_simple_player_lead_card_1) {
    // have nontrump cards
    // Wendy's hand
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

    // Wendy adds a card to his hand and discards one card
    wendy->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
    );

    // Wendy leads
    Card card_led = wendy->lead_card(Card::SUIT_HEARTS);
    Card card_led2 = wendy->lead_card(Card::SUIT_HEARTS);

    // Verify the card Wendy selected to lead
    Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card king_diamonds(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led, ace_diamonds); //check led card
    ASSERT_EQUAL(card_led2, king_diamonds);

    delete wendy;
}

TEST(test_simple_player_lead_card_2) {
    // all trump cards
    // Tim's hand
    Player * tim = Player_factory("Tim", "Simple");
    tim->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    tim->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    tim->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    tim->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    tim->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

    // Tim leads
    Card card_led = tim->lead_card(Card::SUIT_HEARTS);

    // Verify the card Tim selected to lead
    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(card_led, ace_hearts); //check led card

    delete tim;
}

TEST(test_simple_player_lead_card_3) {
    // have left bower
    // Wendy's hand
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));


    // Wendy leads
    Card card_led = wendy->lead_card(Card::SUIT_HEARTS);
    Card card_led2 = wendy->lead_card(Card::SUIT_HEARTS);

    // Verify the card Wendy selected to lead
    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, jack_spades); //check led card
    Card jack_diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led2, jack_diamonds);
    
    delete wendy;
}

TEST(test_simple_player_lead_card_4) {
    // Wendy's hand
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));

    // Wendy adds a card to her hand and discards one card
    wendy->add_and_discard(
    Card(Card::RANK_JACK, Card::SUIT_CLUBS) // upcard
    );

    // Wendy leads
    Card card_led = wendy->lead_card(Card::SUIT_CLUBS);

    // Verify the card Wendy selected to lead
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(card_led, jack_clubs); //check led card

    delete wendy;
}

TEST(test_simple_player_lead_card_5) {
    // Wendy's hand
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));

    // Wendy adds a card to her hand and discards one card
    wendy->add_and_discard(
    Card(Card::RANK_TEN, Card::SUIT_CLUBS) // upcard
    );

    // Wendy leads
    Card card_led = wendy->lead_card(Card::SUIT_CLUBS);

    // Verify the card Wendy selected to lead
    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, jack_spades); //check led card

    delete wendy;
}

TEST(test_simple_player_lead_card_6) {
    // all trump cards - jack
    // Tim's hand
    Player * tim = Player_factory("Tim", "Simple");
    tim->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    tim->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    tim->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    tim->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    tim->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

    // Tim leads
    Card card_led = tim->lead_card(Card::SUIT_HEARTS);

    // Verify the card Tim selected to lead
    Card ace_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(card_led, ace_hearts); //check led card

    delete tim;
}

TEST(test_simple_player_lead_card_7) {
    // all trump cards - jack (left bower)
    // Tim's hand
    Player * tim = Player_factory("Tim", "Simple");
    tim->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    tim->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    tim->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    tim->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    tim->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

    // Tim leads
    Card card_led = tim->lead_card(Card::SUIT_HEARTS);

    // Verify the card Tim selected to lead
    Card ace_hearts(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led, ace_hearts); //check led card

    delete tim;
}

TEST(test_simple_player_play_card_1) {
    // Wendy's hand
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

    // Wendy plays a card
    Card ten_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card card_played = wendy->play_card(
    ten_clubs,  // Ten of Clubs is led
    "Hearts"        // Trump suit
    );

    // Verify the card Wendy played
    ASSERT_EQUAL(card_played, Card(Card::RANK_KING, Card::SUIT_CLUBS));
    delete wendy;
}

TEST(test_simple_player_play_card_2) {
    // Wendy's hand
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

    // Wendy plays a card
    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    Card card_played = wendy->play_card(
    jack_spades,  // Jack of Spades is led
    "Spades"        // Trump suit
    );

    // Verify the card Wendy played
    ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_SPADES));
    delete wendy;
}

TEST(test_simple_player_play_card_3) {
    // Wendy's hand
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

    // Wendy plays a card
    Card ten_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card card_played = wendy->play_card(
    ten_clubs,  // Ten of Clubs is led
    "Spades"        // Trump suit
    );

    // Verify the card Wendy played
    ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    delete wendy;
}

TEST(test_simple_player_play_card_4) {
    // Wendy's hand
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

    // Wendy plays a card
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card card_played = wendy->play_card(
    jack_clubs,  // Jack of Clubs is led
    "Clubs"        // Trump suit
    );

    // Verify the card Wendy played
    ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_SPADES));
    delete wendy;
}

TEST(test_simple_player_play_card_5) {
    // Wendy's hand
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

    // Wendy plays a card
    Card king_spades(Card::RANK_KING, Card::SUIT_SPADES);
    Card card_played = wendy->play_card(
    king_spades,  // King of Spades is led
    "Hearts"        // Trump suit
    );
    Card card_played2 = wendy->play_card(
    king_spades,  // King of Spades is led
    "Hearts"        // Trump suit
    );

    // Verify the card Wendy played
    ASSERT_EQUAL(card_played, Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(card_played2, Card(Card::RANK_KING, Card::SUIT_HEARTS));
    delete wendy;
}

TEST(test_simple_player_play_card_6) {
    // Wendy's hand
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

    // Wendy plays a card
    Card queen_clubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card card_played = wendy->play_card(
    queen_clubs,  // Queen of Clubs is led
    "Hearts"        // Trump suit
    );

    // Verify the card Wendy played
    ASSERT_EQUAL(card_played, Card(Card::RANK_KING, Card::SUIT_SPADES));
    delete wendy;
}

TEST(test_simple_player_play_card_7) {
    // Wendy's hand
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

    // Wendy plays a card
    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card card_played = wendy->play_card(
    queen_hearts,  // Queen of Hearts is led
    "Hearts"        // Trump suit
    );

    // Verify the card Wendy played
    ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    delete wendy;
}

TEST(test_simple_player_play_card_8) {
    // Wendy's hand
    Player * wendy = Player_factory("Wendy", "Simple");
    wendy->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    wendy->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    
    // Wendy adds a card to her hand and discards one card
    wendy->add_and_discard(
    Card(Card::RANK_JACK, Card::SUIT_HEARTS) // upcard
    );

    // Wendy plays a card
    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card card_played = wendy->play_card(
    queen_diamonds,  // Queen of Diamonds is led
    "Spades"        // Trump suit
    );

    // Verify the card Wendy played
    ASSERT_EQUAL(card_played, Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    delete wendy;
}



TEST_MAIN()
