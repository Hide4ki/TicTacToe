#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "User.hpp"

using namespace std;
using namespace sf;

class Server
{
public:
  void Work();
  void Stop();
private:
  Server();
  Server(const Server&) = delete;
  Server(Server&&) = delete;
  Server &operator=(const Server&) = delete;
  Server &operator=(Server&&) = delete;
  virtual ~Server();

public:
  static Server* Instance();
private:
  static Server* _instance;  
  TcpListener _listener;
  SocketSelector _selector;
  vector<User*> _clients;
};