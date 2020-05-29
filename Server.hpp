#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "MyException.hpp"
#include "User.hpp"
#include "MessageType.hpp"
#include "ExPacket.hpp"
#include "MatchState.hpp"

using namespace std;
using namespace sf;

class Server
{
public:
  static Server* Instance();
  void Work();
  void Stop();
  bool isWasStoped();

private:
  Server();
  Server(const Server&) = delete;
  Server(Server&&) = delete;
  Server &operator=(const Server&) = delete;
  Server &operator=(Server&&) = delete;
  virtual ~Server();
  User* Registration();
  void ConnectUser();
  void Proccessing();
  bool CheckBorder(Vector2i,Vector2i);
  MatchState GetStateMatch(Int32 **, Vector2i, Vector2i, Int32&);
  void SafeConnect(User*, TcpSocket*);
  void SetAIgrid(Int32 **, Int32, Int32);
  Vector2i GenerateAImove(Int32**, Int32**, Vector2i, Int32&, Int32&);
  void CalcValueCell(Int32 **, Vector2i, Vector2i, Int32, Int32 *);
  Int32 GetUserValue(Int32*);
  Int32 GetAIValue(Int32*);
  void Matchmaking(Packet &, User*);
  static Server* _instance;  
  TcpListener _listener;
  SocketSelector _selector;
  vector<User*> _users;
  Uint32 _protoId;
  bool _stop;
};