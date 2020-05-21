// PROJECT IDENTIFIER: 9504853406CBAC39EE89AA3AD238AA12CA198043
//  main.cpp
//  p2
//
//  Created by Connor Turco on 5/19/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#include <iostream>
#include <getopt.h>
#include "xcode_redirect.hpp"
#include "game.h"
#include "P2random.h"
#include <deque>

using namespace std;

void read_args(int argc, char* argv[], Game &main_game) {
    int gotopt;
    int option_index = 0;
    option long_opts[] = {
        { "verbose",    no_argument,       nullptr, 'v' },
        { "statistics", required_argument, nullptr, 's' },
        { "median"    , no_argument,       nullptr, 'm' },
        { "help"      , no_argument,       nullptr, 'h' },
        {nullptr, 0, nullptr, '\0' },
        
    };
    while((gotopt = getopt_long(argc, argv, "vs:mh", long_opts, &option_index)) != -1) {
        switch(gotopt) {
            case 'v': {
                main_game.set_verbose(true);
                break;
            }
            case 's': {
                main_game.set_statistics(true, atoi(optarg));
                break;
            }
            case 'm': {
                main_game.set_median(true);
                break;
            }
            case 'h': {
                cout << "Helpful message\n";
                break;
            }
            default: {
                cout << "Flag not recognized\n";
                exit(0);
                break;
            }
        }
    } //while
}
void read_in(Game &main_game) {
    string line;
    //get comment line
    getline(cin, line);
    //get quiver
    unsigned int quiver_capacity;
    cin >> line >> quiver_capacity;
    main_game.set_human(quiver_capacity);
    //get seed
    unsigned int seed;
    cin >> line >> seed;
    //get max rand distance
    unsigned int max_random_dist;
    cin >> line >> max_random_dist;
    //get max rand speed
    unsigned int max_random_speed;
    cin >> line >> max_random_speed;
    //get max rand health
    unsigned int max_random_health;
    cin >> line >> max_random_health;
    
    P2random::initialize(seed, max_random_dist, max_random_speed, max_random_health);
    
}
bool read_and_run_round(Game &main_game) {
    //get triple hyphen for each round
    string line;
    //more zombies need to be added
    cin >> line;
    if(line == "---") {
        string junk;
        unsigned int round;
        cin >> junk >> round;
        while(round >= main_game.get_round()) {
            //loops until need to add zombies or human dies
            if(main_game.do_round(round) == false) {
                return false;
            }
        }

    }
    //if there are no more zombies to be added but not all are killed
    else if(main_game.zombies_left()) {
        while (main_game.zombies_left()) {
            if(main_game.do_round(-5) == false) {
                return false;
            }
        }
    }
    //there are no zombies left and no more will be added
    else {
        return false;
    }

    return true;
}
int main(int argc, char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    
    Game main_game;
    read_args(argc, argv, main_game);
    read_in(main_game);
    
    while (read_and_run_round(main_game)) {
    }
    
    main_game.handle_live_zombies();
    main_game.print_victory_loss();
    main_game.print_all_stats();
    
    
    
    
     return 0;
}
