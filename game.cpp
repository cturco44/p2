//
//  game.cpp
//  p2
//
//  Created by Connor Turco on 5/19/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#include "game.h"
#include <deque>
#include <queue>

void Game::add_named_zombie(std::string &name, int distance, int speed, unsigned int health) {
    Zombie zombie(name, distance, speed, health);
    
    all_zombies.push_back(zombie);
    Zombie *ptr = &all_zombies.back();
    zombie_pq.push(ptr);
    
}
//Does not check if dead
bool ZombieLess::operator()(const Zombie* lhs, const Zombie* rhs) const {
    int lhs_eta = lhs->get_distance()/lhs->get_speed();
    int rhs_eta = lhs->get_distance()/lhs->get_speed();
    
    //Tie in ETA
    if(lhs_eta == rhs_eta) {
        //Tie in health, use name
        unsigned int lhs_health = lhs->get_health();
        unsigned int rhs_health = rhs->get_health();
        if(lhs_health == rhs_health) {
            return lhs->get_name() < rhs->get_name();
        }
        return lhs_health < rhs_health;
    }
        return lhs_eta < rhs_eta;
}
