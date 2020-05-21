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
class ZombieActivityLess {
public:
    bool operator()(const Zombie* lhs, const Zombie* rhs) const;
};
class ZombieActivityMore {
public:
    bool operator()(const Zombie* lhs, const Zombie* rhs) const;
};

class Game {
public:
    Game() {
        round = 1;
        ate_you = nullptr;
        verbose = false;
        statistics = false;
        statistic_num = 0;
        median = false;
        num_alive_zombies = 0;
        victory = false;
    }
    unsigned int get_round() const {
        return round;
    }
    void set_victory_to_win() {
        victory = true;
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
        zombie_order.reserve(statistics_num_in);
    }
    Zombie* get_top_pq() {
        return zombie_pq.top();
    }
    void set_human(unsigned int quiver_capacity) {
        fighter.set_quiver_capacity(quiver_capacity);
    }
    bool do_round(int next_gen);
    void add_named_zombie(std::string &name, int distance, int speed, unsigned int health, unsigned int round);
    void add_random_zombie(unsigned int round);
    void add_iterator(unsigned int round);
    void print_all_stats();
    void handle_live_zombies();
    void print_victory_loss();
    bool zombies_left() const;
    void create_zombies();
private:
    circular zombie_order;
    Median running_median;
    Human fighter;
    std::deque<Zombie> all_zombies;
    std::priority_queue<Zombie*, std::vector<Zombie*>, ZombieLess> zombie_pq;
    std::vector<Zombie*> order_killed;
    Zombie *ate_you;
    bool verbose;
    bool median;
    bool statistics;
    bool victory;
    unsigned int statistic_num;
    unsigned int round;
    unsigned int num_alive_zombies;
    
    
    void print_zombie(const Zombie &zombie_in) const;
    void print_median();
    void print_activity();
    
    
};


#endif /* game_hpp */
