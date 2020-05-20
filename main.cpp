// PROJECT IDENTIFIER: 9504853406CBAC39EE89AA3AD238AA12CA198043
//  main.cpp
//  p2
//
//  Created by Connor Turco on 5/19/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#include <iostream>
#include <getopt.h>
#include "xcode_redirect.hpp"
#include "game.h"

using namespace std;

void read_args(int argc, char* argv[], Game &main_game) {
    int gotopt;
    int option_index = 0;
    option long_opts[] = {
        { "verbose",    no_argument,       nullptr, 'v' },
        { "statistics", required_argument, nullptr, 's' },
        { "median"    , no_argument,       nullptr, 'm' },
        { "help"      , no_argument,       nullptr, 'h' },
        {nullptr, 0, nullptr, '\0' },
        
    };
    while((gotopt = getopt_long(argc, argv, "vs:m:h", long_opts, &option_index)) != -1) {
        switch(gotopt) {
            case 'v': {
                main_game.set_verbose(true);
                break;
            }
            case 's': {
                main_game.set_statistics(true, atoi(optarg));
                break;
            }
            case 'm': {
                main_game.set_median(true);
                break;
            }
            case 'h': {
                cout << "Helpful message\n";
                break;
            }
            default: {
                cout << "Flag not recognized\n";
                exit(0);
                break;
            }
        }
    } //while
}

int main(int argc, char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    
    Game main_game;
    read_args(argc, argv, main_game);
    
    
    
    
    
    
    return 0;
}
