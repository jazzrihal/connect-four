//
//  ConnectFour.hpp
//  ConnectFour
//
//  Created by Jazz Rihal on 22/01/2021.
//

#ifndef ConnectFour_h
#define ConnectFour_h

#include "Game.h"
#include <iostream>
#include <string>

class ConnectFour : public Game {
  enum SlotState { BLANK, PLAYER_1, PLAYER_2 };

  int height, width;
  SlotState **board;
  SlotState current_player;
  int user_in;
  std::string status_message;
  int winner;

public:
  ConnectFour();
  ~ConnectFour();

  void Play() override;
  void Quit() override;
  void Reset() override;

private:
  // Game mechanics
  void Draw();
  void Input();
  void PlaceToken(int column);
  void SwitchPlayer();

  // Win detection
  void DetectWin();
  void AppendTokenToString(const SlotState token, std::string &lineOfTokens);
  void VerifyConnectFour(const std::string &tokens);
};

#endif /* ConnectFour_h */
