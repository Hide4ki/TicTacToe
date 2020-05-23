#pragma once

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
  UserState state; 
  TcpSocket *socket;
  string password;
  string login;
};