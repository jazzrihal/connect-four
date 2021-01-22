//
//  Game.hpp
//  ConnectFour
//
//  Created by Jazz Rihal on 22/01/2021.
//

#ifndef Game_hpp
#define Game_hpp

class Game {
public:
    Game() {};
    virtual ~Game() {};
    virtual void Play() = 0;
    virtual void Quit() = 0;
    virtual void Reset() = 0;
};

#endif /* Game_hpp */
