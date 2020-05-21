// PROJECT IDENTIFIER: 9504853406CBAC39EE89AA3AD238AA12CA198043
//  game.cpp
//  p2
//
//  Created by Connor Turco on 5/19/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#include "game.h"
#include <deque>
#include <queue>
#include "P2random.h"
#include <iostream>

using namespace std;

void Game::add_named_zombie(std::string &name, int distance, int speed, unsigned int health, unsigned int round) {
    Zombie zombie(name, distance, speed, health, round);
    
    all_zombies.push_back(zombie);
    if(round == 1) {
        Zombie *ptr = &all_zombies.back();
        zombie_pq.push(ptr);
    }

    
}
void Game::add_random_zombie(unsigned int round) {
    string name = P2random::getNextZombieName();
    unsigned int distance = P2random::getNextZombieDistance();
    unsigned int speed = P2random::getNextZombieSpeed();
    unsigned int health = P2random::getNextZombieHealth();
    
    Zombie zombie(name, distance, speed, health, round);
    all_zombies.push_back(zombie);
    if(round == 1) {
        Zombie *ptr = &all_zombies.back();
        zombie_pq.push(ptr);
    }

}
void Game::add_iterator(unsigned int round) {
    std::deque<Zombie>::iterator it = --all_zombies.end();
    std::pair<unsigned int, std::deque<Zombie>::iterator> holder (round, it);
    round_starts.push_back(holder);
    
}
//Could be wrong
void Game::up_to_round(std::deque<Zombie>::iterator &end) {
    for(auto it = round_starts.begin(); it != round_starts.end(); ++it) {
        
        if(it->first > round) {
            end = it->second;
            return;
        }
        //if it reaches end, use entire vector of zombies
        if(it == --round_starts.end()) {
            end = all_zombies.end();
            return;
        }

    }
}
bool Game::it_one_round(std::deque<Zombie>::iterator &start,
                    std::deque<Zombie>::iterator &end, unsigned int round) {
    for(auto it2 = round_starts.begin(); it2 != round_starts.end(); ++it2) {
        if(it2->first == round) {
            start = it2->second;
            end = (++it2)->second;
            return true;
        }
        if(it2->first > round) {
            return false;
        }
    }
    return false;
}
void Game::print_zombie(const Zombie &zombie_in) const {
    cout << zombie_in.get_name() << " (distance: " << zombie_in.get_distance()
    << ", speed: " << zombie_in.get_speed() << ", health: " << zombie_in.get_health()
    << ")\n";
}
bool Game::do_round() {
    if(verbose) {
        cout << "Round: " << round << "\n";
    } // verbose
    
    //refill bow
    fighter.reload();

    //if round is 1 do nothing, zombies in correct position
    if(round > 1) {
        deque<Zombie>::iterator end;
        up_to_round(end);
        //moves every zombie alive
        for(auto it = all_zombies.begin(); it != end; ++it) {
            if(it->get_health() != 0) {
                it->move();
                if(verbose) {
                    cout << "Moved: ";
                    print_zombie(*it);
                }//verbose
                //Zombie gets you
                if(it->get_distance() == 0) {
                    ate_you = &(*it);
                    fighter.set_alive(false);
                }
            }
        }
    }
    
    if(fighter.get_alive() == false) {
        return false;
    }
    //Zombie creation
    deque<Zombie>::iterator start;
    deque<Zombie>::iterator end;
    if(it_one_round(start, end, round)) {
        for(start; start != end; ++start) {
            if(verbose) {
                cout << "Created: ";
                print_zombie(*start);
            }
            //Push to pq
            if(round > 1) {
                Zombie *ptr = &(*start);
                zombie_pq.push(ptr);
            }
            
        }
    }
    Zombie* zom2 = zombie_pq.top();
    if(zom2->get_distance() == 0) {
        fighter.set_alive(false);
        return false;
    }
    
    
    //Step 6
    while(fighter.get_alive() && fighter.get_arrows() != 0) {
        Zombie* zom = zombie_pq.top();
        zom->attacked();
        fighter.shoot();
        
        //Kill zombie
        if(!zom->alive()) {
            if(verbose) {
                cout << "Destroyed: ";
                print_zombie(*zom);
            }
            zombie_pq.pop();
        }

    }
    if(zombie_pq.empty() && !zombies_left()) {
        return false;
    }
    ++round;
    return true;
}
//Does not check if dead
bool ZombieLess::operator()(const Zombie* lhs, const Zombie* rhs) const {
    int lhs_eta = lhs->get_distance()/lhs->get_speed();
    int rhs_eta = rhs->get_distance()/rhs->get_speed();
    
    //Tie in ETA
    if(lhs_eta == rhs_eta) {
        //Tie in health, use name
        unsigned int lhs_health = lhs->get_health();
        unsigned int rhs_health = rhs->get_health();
        if(lhs_health == rhs_health) {
            return lhs->get_name() > rhs->get_name();
        }
        return lhs_health > rhs_health;
    }
        return lhs_eta > rhs_eta;
}
bool Game::zombies_left() const {
    auto it = --round_starts.end();
    if(it->first == round) {
        return false;
    }
    return true;
}
