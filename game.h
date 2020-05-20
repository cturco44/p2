//
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
    void add_named_zombie(std::string &name, int distance, int speed, unsigned int health);
    
private:
    std::deque<Zombie> all_zombies;
    std::priority_queue<Zombie*, std::vector<Zombie*>, ZombieLess> zombie_pq;
    
    bool verbose;
    bool median;
    bool statistics;
    unsigned int statistic_num;
    unsigned int round;
    
};


#endif /* game_hpp */
