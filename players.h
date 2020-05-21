//
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
    round_created(round) {}

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
    bool alive() {
        if(health == 0) {
            return false;
        }
        return true;
    }
    
    
private:
    std::string name;
    int distance;
    int speed;
    unsigned int health;
    unsigned int round_created;
    
};

#endif /* players_hpp */
