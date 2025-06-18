// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include "Card.h"
#include "Pack.h"
#include "Player.h"

using namespace std;

class HumanPlayer;
class SimplePlayer;

class Game {
public:
    Game() {
        hand = 0;
        winning_points = 0;
        dealer = 0;
        order_up_group = 0;
        leader = 0;
        trick_take[0] = 0;
        trick_take[1] = 0;
        points[0] = 0;
        points[1] = 0;
        shuffle = false;
    }
    
    ~Game() {
        for (int i = 0; i < int(players.size()); ++i) {
          delete players[i];
        }
    }
    
    bool setup(int argc, char* argv[]) {
        int point = atoi(argv[3]);
        // check for errors
        bool error = false;
        if (argc != 12 || (point < 0 || point > 100) ||
            (strcmp(argv[2], "shuffle") != 0 &&
             strcmp(argv[2], "noshuffle") != 0)) {
            error = true;
        }
        else {
            for (int i = 0; i < 4; i++) {
                if ((strcmp(argv[2 * i + 5], "Simple") != 0 &&
                     strcmp(argv[2 * i + 5], "Human") != 0)) {
                    error = true;
                }
            }
        }
        if (error) {
            cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
                 << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
                 << "NAME4 TYPE4" << endl;
            return false;
        }
        
        winning_points = point;
        
        ifstream fin(argv[1]);
        if(fin.is_open()) {
            pack = Pack(fin);
        }
        if (strcmp(argv[2], "shuffle") == 0) {
            shuffle = true;
        }
        for (int i = 0; i < 4; i++) {
            players.push_back(Player_factory(argv[2 * i + 4], argv[2 * i + 5]));
        }
        return true;
    }
    
    void start() {
        cout << "Hand " << hand << endl;
        cout << players[dealer]->get_name() << " deals" << endl;
        pack.reset();
        if (shuffle) {
            pack.shuffle();
        }
    }
    
    void deal() {
        int deal_batch = 3;
        for (int i = 0; (unsigned) i < players.size(); i++) {
            for (int j = 0; j < deal_batch; j++) {
                players[(dealer + i + 1) % 4]->add_card(pack.deal_one());
            }
            if (deal_batch == 3) {
                deal_batch = 2;
            }
            else if (deal_batch == 2) {
                deal_batch = 3;
            }
        }
        
        deal_batch = 2;
        for (int i = 0; (unsigned) i < players.size(); i++) {
            for (int j = 0; j < deal_batch; j++) {
                players[(dealer + i + 1) % 4]->add_card(pack.deal_one());
            }
            if (deal_batch == 2) {
                deal_batch = 3;
            }
            else if (deal_batch == 3) {
                deal_batch = 2;
            }
        }
    }
    
    void making_trump() {
        // print out the upcard
        const Card upcard = pack.deal_one();
        cout << upcard << " turned up" << endl;
        bool trump_made;
        string order_up_suit;
        // round 1
        
        for (int round = 1; round <= 2; round++) {
            for (int i = 0; (unsigned) i < players.size(); i++) {
                int p = (dealer + i + 1) % 4;
                // all players
                trump_made = players[p]->make_trump(upcard,
                                            (i == 3), round, order_up_suit);
                if (trump_made && round == 1) {
                    order_up_group = p % 2;
                    cout << players[p]->get_name()<< " orders up "
                    << order_up_suit << endl;
                    cout << endl;
                    players[dealer]->add_and_discard(upcard);
                    trump_suit = order_up_suit;
                    round = 3;
                    break;
                }
                else if (trump_made && round == 2){
                    order_up_group = p % 2;
                    cout << players[p]->get_name()<< " orders up "
                    << order_up_suit << endl;
                    cout << endl;
                    trump_suit = order_up_suit;
                    break;
                }
                else {
                    cout << players[p]->get_name() << " passes" << endl;
                }
            }
        }
    }
    
    void trick_taking() {
        trick_take[0] = 0;
        trick_take[1] = 0;
        leader = (dealer + 1) % 4;
        // trick
        for (int i = 0; i < 5; i++) {
            // all players
            trick_cards[leader] = players[leader]->lead_card(trump_suit);
            cout << trick_cards[leader] << " led by "
            << players[leader]->get_name() << endl;
            // player
            for (int j = 1; (unsigned) j < players.size(); j++) {
                trick_cards[(leader + j) % 4] = players[(leader + j) % 4]->
                play_card(trick_cards[leader], trump_suit);
                cout << trick_cards[(leader + j) % 4] << " played by "
                << players[(leader + j) % 4]->get_name() << endl;
            }
            int player_won = 0;
            for (int k = 1; (unsigned) k < players.size(); k++) {
                if (Card_less(trick_cards[player_won], trick_cards[k],
                              trick_cards[leader], trump_suit)) {
                    player_won = k;
                }
            }
            // update info for the winner
            leader = player_won;
            cout << players[leader]->get_name() << " takes the trick" << endl;
            cout << endl;
            
            trick_take[leader % 2]++;
        }
    }
    
    bool scoring() {
        int i = 0;
        if (trick_take[0] < trick_take[1]) {
            i = 1;
        }
        else {
            i = 0;
        }
        cout << players[i + 0]->get_name() << " and "
        << players[i + 2]->get_name() << " win the hand" << endl;
        // to see if they are the order up group
        if (i == order_up_group) {
            if (trick_take[i] == 5) {
                points[i] += 2;
                cout << "march!" << endl;
            }
            else {
                points[i] += 1;
            }
        }
        else {
            points[i] += 2;
            cout << "euchred!" << endl;
        }
        // print the score
        cout << players[0]->get_name() << " and " << players[2]->get_name()
        << " have " << points[0] << " points" << endl;
        cout << players[1]->get_name() << " and " << players[3]->get_name()
        << " have " << points[1] << " points" << endl;
        cout << endl;
        // check if the game ends
        if (points[i] >= winning_points) {
            cout << players[i + 0]->get_name() << " and "
            << players[i + 2]->get_name() << " win!" << endl;
            return true;
        }
        // update new hand and dealer
        hand++;
        dealer = (dealer + 1) % 4;
        
        return false;
    }
    
    void run() {
        while(1) {
            start();
            deal();
            making_trump();
            trick_taking();
            if (scoring()) {
                break;
            }
        }
    }
    

private:
    vector<Player*> players;
    Pack pack;
    int hand;
    int winning_points;
    int dealer;
    string trump_suit;
    int order_up_group;
    int leader;
    Card trick_cards[4];
    int trick_take[2];
    int points[2];
    bool shuffle;
};

int main(int argc, char* argv[]) {
    Game game;
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;
    if (!game.setup(argc, argv)) {
        return -1;
    }
    game.run();
}
