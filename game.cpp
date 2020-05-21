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
#include "players.h"

using namespace std;

void Game::print_victory_loss() {
    if(victory) {
        cout << "VICTORY IN ROUND " << round << "! "
        << ate_you->get_name() << "was the last zombie.\n";
    }
    else {
        cout << "DEFEAT IN ROUND " << round << "! " << ate_you->get_name()
        << " ate your brains!\n";
    }
}
void Game::handle_live_zombies() {
    num_alive_zombies = (int)zombie_pq.size();
    while(!zombie_pq.empty()) {
        zombie_pq.top()->set_killed(round);
        zombie_pq.pop();
    }
}
void Game::print_all_stats() {
    cout << "Zombies still active: " << num_alive_zombies << "\n";
    zombie_order.print();
    print_activity();
}

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
            if(end == round_starts.end()->second) {
                end = all_zombies.end();
            }
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
        int changed = false;
        for(auto it = all_zombies.begin(); it != end; ++it) {
            if(it->get_health() != 0) {
                it->move();
                if(verbose) {
                    cout << "Moved: ";
                    print_zombie(*it);
                }//verbose
                //Zombie gets you
                if(it->get_distance() == 0) {
                    if(changed == false) {
                        changed = true;
                        ate_you = &(*it);
                        fighter.set_alive(false);
                    }

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
        for(; start != end; ++start) {
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
                zom->set_killed(round);
                ate_you = zom;
                if(statistics) {
                    zombie_order.push(zom);
                }
                if(median) {
                    running_median.push(zom->get_lifespan(round));
                }
                
            }
            zombie_pq.pop();
        }

    }
    if(median) {
        print_median();
    }
    if(zombie_pq.empty() && !zombies_left()) {
        victory = true;
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
bool ZombieActivityLess::operator()(const Zombie* lhs, const Zombie* rhs) const {
    int lhs_lifespan = lhs->get_lifespan();
    int rhs_lifespan = rhs->get_lifespan();
    if(lhs_lifespan == rhs_lifespan) {
        return lhs->get_name() > rhs->get_name();
    }
    
    return lhs_lifespan < rhs_lifespan;
}
bool ZombieActivityMore::operator()(const Zombie* lhs, const Zombie* rhs) const {
    int lhs_lifespan = lhs->get_lifespan();
    int rhs_lifespan = rhs->get_lifespan();
    if(lhs_lifespan == rhs_lifespan) {
        return lhs->get_name() > rhs->get_name();
    }
    
    return lhs_lifespan > rhs_lifespan;
    
}
bool Game::zombies_left() const {
    auto it = --round_starts.end();
    if(it->first == round) {
        return false;
    }
    return true;
}
void Game::print_median() {
    cout << "At the end of round " << round << ", the median zombie lifetime is "
    << running_median.get_median() << "\n";
}
void Game::print_activity() {
    
    priority_queue<Zombie*, vector<Zombie*>, ZombieActivityLess> most_active;
    priority_queue<Zombie*, vector<Zombie*>, ZombieActivityMore> least_active;
    
    deque<Zombie>::iterator end;
    up_to_round(end);
    for(auto it = all_zombies.begin(); it != end; ++it) {
        Zombie* ptr = &(*it);
        most_active.push(ptr);
        least_active.push(ptr);
    }
    
    cout << "Most active zombies:\n";
    for(unsigned int i = 0; i < statistic_num; ++i) {
        if(most_active.empty()) {
            break;
        }
        Zombie *ptr = most_active.top();
        cout << ptr->get_name() << " " << ptr->get_lifespan() << "\n";
        most_active.pop();
    }
    
    cout << "Least active zombies:\n";
    for(unsigned int i = 0; i < statistic_num; ++i) {
        
        if(least_active.empty()) {
            break;
        }
        Zombie *ptr = least_active.top();
        cout << ptr->get_name() << " " << ptr->get_lifespan() << "\n";
        least_active.pop();
    }
}

