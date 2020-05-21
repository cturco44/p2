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
void Game::create_zombies() {
    string junk;
    unsigned int random_zombies;
    unsigned int named_zombies;
    cin >> junk >> random_zombies >> junk >> named_zombies;
    for(unsigned int i = 0; i < random_zombies; ++i) {
        add_random_zombie(round);
    }
    
    for(unsigned int i = 0; i < named_zombies; ++i) {
        string name;
        unsigned int distance;
        unsigned int speed;
        unsigned int health;
        cin >> name >> junk >> distance >> junk >> speed >> junk >> health;
        add_named_zombie(name, distance, speed, health, round);
    }
    
}
void Game::print_victory_loss() {
    if(victory) {
        cout << "VICTORY IN ROUND " << round - 1 << "! "
        << ate_you->get_name() << " was the last zombie.\n";
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
    if(statistics) {
        cout << "Zombies still active: " << num_alive_zombies << "\n";
        zombie_order.print();
        print_activity();
    }

}
bool Game::zombies_left() const {
    if(!zombie_pq.empty()) {
        return true;
    }
    else {
        return false;
    }
}
void Game::add_named_zombie(std::string &name, int distance, int speed, unsigned int health, unsigned int round) {
    Zombie zombie(name, distance, speed, health, round);
    
    all_zombies.push_back(zombie);
    
    Zombie *ptr = &all_zombies.back();
    zombie_pq.push(ptr);
    if(verbose) {
        cout << "Created: ";
        print_zombie(zombie);
    }
    

    
}
void Game::add_random_zombie(unsigned int round) {
    string name = P2random::getNextZombieName();
    unsigned int distance = P2random::getNextZombieDistance();
    unsigned int speed = P2random::getNextZombieSpeed();
    unsigned int health = P2random::getNextZombieHealth();
    
    Zombie zombie(name, distance, speed, health, round);
    all_zombies.push_back(zombie);
    
    if(verbose) {
        cout << "Created: ";
        print_zombie(zombie);
    }
    
    Zombie *ptr = &all_zombies.back();
    zombie_pq.push(ptr);
    

}
void Game::print_zombie(const Zombie &zombie_in) const {
    cout << zombie_in.get_name() << " (distance: " << zombie_in.get_distance()
    << ", speed: " << zombie_in.get_speed() << ", health: " << zombie_in.get_health()
    << ")\n";
}

//only returns false if you died, read and do round checks if you won
bool Game::do_round(int next_gen) {
    if(verbose) {
        cout << "Round: " << round << "\n";
    } // verbose
    
    //refill bow
    fighter.reload();

    //if round is 1 do nothing, zombies in correct position
    if(!zombie_pq.empty()) {
        //moves every zombie alive
        int changed = false;
        for(auto it = all_zombies.begin(); it != all_zombies.end(); ++it) {
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
    //If zombie moved and ate you GAME OVER
    if(fighter.get_alive() == false) {
        return false;
    }
    //Zombie creation
    if(next_gen == (int)round) {
        create_zombies();
        //Make sure no named zombies started at position 0 GAME OVER
        if(!zombie_pq.empty()) {
            Zombie* zom2 = zombie_pq.top();
            if(zom2->get_distance() == 0) {
                fighter.set_alive(false);
                return false;
            }
        }
    }


    
    
    //Step 6
    while(fighter.get_alive() && fighter.get_arrows() != 0 && !zombie_pq.empty()) {
        Zombie* zom = zombie_pq.top();
        zom->attacked();
        fighter.shoot();
        
        //Kill zombie
        if(!zom->alive()) {
            if(verbose) {
                cout << "Destroyed: ";
                print_zombie(*zom);
            }
            if(statistics) {
                zombie_order.push(zom);
            }
            if(median) {
                running_median.push(zom->get_lifespan(round));
            }
            zom->set_killed(round);
            ate_you = zom;
            zombie_pq.pop();
        }

    }
    if(median) {
        print_median();
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
void Game::print_median() {
    int running_med = running_median.get_median();
    if(running_med != 0) {
        cout << "At the end of round " << round << ", the median zombie lifetime is "
        << running_med << "\n";
    }

}
void Game::print_activity() {
    
    priority_queue<Zombie*, vector<Zombie*>, ZombieActivityLess> most_active;
    priority_queue<Zombie*, vector<Zombie*>, ZombieActivityMore> least_active;
    
    for(auto it = all_zombies.begin(); it != all_zombies.end(); ++it) {
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

