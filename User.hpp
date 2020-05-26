#pragma once

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include "UserState.hpp"

using namespace std;
using namespace sf;

class User
{
public:
  User();
  User(const User&) = delete;
  User(User&&) = delete;
  User& operator=(const User&) = delete;
  User& operator=(User&&) = delete;
  virtual ~User();
private:
  Uint32 _id;
  TcpSocket *_socket;
  UserState _state; 
  Uint32 _x;
  Uint32 _y;
  Uint32 _opponentID;
  bool _tictac;
  Int32 **_grid;
  friend ofstream &operator<<(ofstream&, const User&);
  friend ifstream &operator>>(ifstream&, User&);
  friend class Server;
};