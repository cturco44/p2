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
    
private:
    unsigned int arrows;
    unsigned int quiver_capacity;
    bool alive;
};

class Zombie {
public:
    Zombie(std::string &name_in, int distance_in, int speed_in, unsigned int health_in)
    : name(name_in), distance(distance_in), speed(speed_in), health(health_in) {}

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
    
private:
    std::string name;
    int distance;
    int speed;
    unsigned int health;
    unsigned int round_created;
    
};

#endif /* players_hpp */
