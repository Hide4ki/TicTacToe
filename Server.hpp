#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "Exception.hpp"
#include "User.hpp"
#include "MessageType.hpp"
#include "ExPacket.hpp"

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
  bool isRegistered(string&);
  User *Registration(string&, Uint32);
  void ConnectUser();
  void Proccessing();
  User *Login(string&, Uint32);
  void SafeConnect(User*, TcpSocket*);

public:
  static Server* Instance();

private:
  static Server* _instance;  
  TcpListener _listener;
  SocketSelector _selector;
  vector<User*> _users;
  Uint32 _protoId;
};