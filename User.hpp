#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include "UserState.hpp"

using namespace std;
using namespace sf;

class User
{
public:
  Uint32 id;
  TcpSocket *socket;
  UserState state; 
  Uint32 cntWon;
  Uint32 cntLost;
  Uint32 cntGame;
  Uint32 password;//TODO add md5 hash
  string login;
  User();
  User(TcpSocket*);
  User(const User&);
  User(User&&);
  User& operator=(const User&);
  User& operator=(User&&);
  virtual ~User();
  friend ofstream &operator<<(ofstream&, User*);
  friend ifstream &operator>>(ifstream&, User*);
};