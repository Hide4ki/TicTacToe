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
  User(string&, Uint32);
  User(const User&) = delete;
  User(User&&) = delete;
  User& operator=(const User&) = delete;
  User& operator=(User&&) = delete;
  virtual ~User();
  bool CheckLogin(string&) const;
  bool CheckPass(Uint32) const;
private:
  Uint32 _id;
  TcpSocket *_socket;
  UserState _state; 
  Uint32 _cntWon;
  Uint32 _cntLost;
  Uint32 _cntGame;
  Uint32 _password;//TODO add md5 hash
  string _login;
  friend ofstream &operator<<(ofstream&, const User*);
  friend ifstream &operator>>(ifstream&, User*);
  friend class Server;
};