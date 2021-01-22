//
//  main.cpp
//  ConnectFour
//
//  Created by Jazz Rihal on 07/11/2020.
//

#include "ConnectFour.hpp"

using namespace std;

int main() {
    Game *game = new ConnectFour();

    game->Play();
    
    delete game;
    return 0;
}
