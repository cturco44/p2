// PROJECT IDENTIFIER: 9504853406CBAC39EE89AA3AD238AA12CA198043
//  game.hpp
//  p2
//
//  Created by Connor Turco on 5/19/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include "players.h"
#include <queue>
#include <string>

class ZombieLess {
public:
    bool operator()(const Zombie* lhs, const Zombie* rhs) const;
};

class Game {
public:
    Game() {
        round = 1;
        ate_you = nullptr;
    }
    void set_verbose(bool verbose_in) {
        verbose = verbose_in;
    }
    void set_median(bool median_in) {
        median = median_in;
    }
    void set_statistics(bool statistics_in, unsigned int statistics_num_in) {
        statistics = statistics_in;
        statistic_num = statistics_num_in;
    }
    Zombie* get_top_pq() {
        return zombie_pq.top();
    }
    void set_human(unsigned int quiver_capacity) {
        fighter.set_quiver_capacity(quiver_capacity);
    }
    bool do_round();
    void add_named_zombie(std::string &name, int distance, int speed, unsigned int health, unsigned int round);
    void add_random_zombie(unsigned int round);
    void add_iterator(unsigned int round);
    
private:
    Human fighter;
    std::deque<Zombie> all_zombies;
    std::priority_queue<Zombie*, std::vector<Zombie*>, ZombieLess> zombie_pq;
    std::vector<std::pair<unsigned int, std::deque<Zombie>::iterator> > round_starts;
    std::vector<Zombie*> order_killed;
    Zombie *ate_you;
    bool verbose;
    bool median;
    bool statistics;
    unsigned int statistic_num;
    unsigned int round;
    
    
    bool it_one_round(std::deque<Zombie>::iterator &start, std::deque<Zombie>::iterator &end, unsigned int round);
    void up_to_round(std::deque<Zombie>::iterator &end);
    void print_zombie(const Zombie &zombie_in) const;
    bool zombies_left() const;
    
};


#endif /* game_hpp */
