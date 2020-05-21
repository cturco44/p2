// PROJECT IDENTIFIER: 9504853406CBAC39EE89AA3AD238AA12CA198043
//  players.hpp
//  p2
//
//  Created by Connor Turco on 5/19/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#ifndef players_hpp
#define players_hpp

#include <stdio.h>
#include <string>
#include <deque>
#include <vector>
#include <queue>

class Human {
public:
    Human() : arrows(0), quiver_capacity(0), alive(true) {}
    unsigned int get_arrows() {
        return arrows;
    }
    unsigned int get_quiver_capacity() {
        return quiver_capacity;
    }
    bool get_alive() {
        return alive;
    }
    void set_arrows(unsigned int arrows_in) {
        arrows = arrows_in;
    }
    void set_quiver_capacity(unsigned int quiver_in) {
        quiver_capacity = quiver_in;
    }
    void set_alive(bool alive_in) {
        alive = alive_in;
    }
    void reload() {
        arrows = quiver_capacity;
    }
    //if out return false
    bool shoot() {
        if(arrows > 0) {
            --arrows;
        }
        if(arrows == 0) {
            return false;
        }
        return true;
    }
    
private:
    unsigned int arrows;
    unsigned int quiver_capacity;
    bool alive;
};

class Zombie {
public:
    Zombie(std::string &name_in, int distance_in, int speed_in, unsigned int health_in, unsigned int round)
    : name(name_in), distance(distance_in), speed(speed_in), health(health_in),
    round_created(round) {
        killed = 0;
    }
    
    unsigned int get_lifespan(unsigned int current_round) const {
        return current_round - round_created + 1;
    }
    int get_lifespan() const {
          return killed - round_created + 1;
    }

    void set_name(std::string name_in) {
        name = name_in;
    }
    void set_distance(int distance_in) {
        distance = distance_in;
    }
    void set_speed(int speed_in) {
        speed = speed_in;
    }
    void set_health(unsigned int health_in) {
        health = health_in;
    }
    void set_round_created(unsigned int round_in) {
        round_created = round_in;
    }
    int get_distance() const {
        return distance;
    }
    int get_speed() const {
        return speed;
    }
    unsigned int get_health() const {
        return health;
    }
    const std::string& get_name() const {
        return name;
    }
    void move() {
        distance = std::max(0, distance - speed);
    }

    //if dead returns false
    bool attacked() {
        if(health > 0) {
            --health;
        }
        if(health == 0) {
            return false;
        }
        return true;
    }
    bool alive() const {
        if(health == 0) {
            return false;
        }
        return true;
    }
    unsigned int get_killed() const {
        return killed;
    }
    void set_killed(unsigned int round_killed) {
        killed = round_killed;
    }
private:
    std::string name;
    int distance;
    int speed;
    unsigned int health;
    unsigned int round_created;
    unsigned int killed;
    
};
class circular {
public:
    void push(Zombie* z);
    void reserve(unsigned int n);
    void print();
private:
    std::vector<Zombie*>::iterator it;
    std::vector<Zombie*> firstn;
    std::vector<Zombie*> lastn;
    
    
};
class Median {
public:
    void push(unsigned int data);
    unsigned int get_median();
private:
    std::priority_queue<unsigned int, std::vector<unsigned int>, std::less<unsigned int> > max_heap;
    std::priority_queue<unsigned int, std::vector<unsigned int>, std::greater<unsigned int> > min_heap;
};


#endif /* players_hpp */
