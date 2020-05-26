#include "Server.hpp"

using namespace std;
using namespace sf;
#include <sstream>

int main() 
{
  Server *myServer = Server::Instance();

  while (!myServer->isWasStoped()) 
    myServer->Work();

  myServer->Stop();
  return 0;
}

Server* Server::_instance = 0;
Server* Server::Instance()
{
  if(_instance == 0)
  {
    _instance = new Server;
  }
  return _instance;
}

bool Server::isWasStoped()
{
  return _stop;
}

Server::Server()
{
  _listener.listen(1172);
  _selector.add(_listener);
  _protoId = 1;
  _stop = false;
}

void Server::Work()
{
  if (_selector.wait()) 
    if (_selector.isReady(_listener)) 
      ConnectUser();
    else 
      Proccessing();
}

void Server::Stop()
{
  delete this;
}

Server::~Server()
{
  _instance = 0;
  _listener.close();
  _selector.clear();
  for(auto it : _users)
    delete it;
}

User *Server::Registration()
{
  User *newUser = new User();
  newUser->_id = _protoId++;
  _users.push_back(newUser);
  return newUser;
}

void Server::ConnectUser()
{
  TcpSocket *socket = new TcpSocket;
  User *conUser;
  Packet packet;

  conUser = Registration(); 

  SafeConnect(conUser, socket);
  cout << "Connect new User";
  if(_listener.accept(*socket) != Socket::Done)
  { 
    cout << "Fuck";
  }
  _selector.add(*socket);
}

void Server::Proccessing()
{
  for (auto it : _users) 
  {
    if (_selector.isReady(*it->_socket)) 
    {
      Packet packet;
      if (it->_socket->receive(packet) == Socket::Done) 
      {
        string tmp;
        MessageType typePack;
        if(packet >> typePack)
          ;//todo

        switch(typePack)
        {
          case MessageType::Connect://todo
            if (packet >> tmp)
            {
              cout << tmp << endl; 
            } 
            break;
          case MessageType::Config:
            {
              bool sizeFound = false;
              bool selectedAI = false;
              for(int i = 0; i < 4; i++)
                if(packet >> tmp)
                  if(tmp == "Y" && !sizeFound)
                    switch(i)
                    {
                      case 0:
                        selectedAI = true;
                      break;
                      case 1:
                        it->_x = 5;
                        it->_y = 5;
                        sizeFound = true;
                      break;
                      case 2:
                        it->_x = 15;
                        it->_y = 15;
                        sizeFound = true;
                      break;
                      case 3:
                        it->_x = 19;
                        it->_y = 19;
                        sizeFound = true;
                      break;
                    }
              string x, y;
              packet >> x >> y;
              if(!sizeFound)
              {
                istringstream ss(x + " " + y);
                Uint32 a, b;
                ss >> a >> b;
                it->_x = a;
                it->_y = b;
              }
              
              Packet confirm;
              confirm << it->_x << it->_y;
              it->_grid = new Int32*[it->_x];
              for(int i = 0; i<it->_x;i++)
              {
                it->_grid[i] = new Int32[it->_y];
                for(int j = 0; j<it->_y; j++)
                  it->_grid[i][j] = 0;
              }
              it->_tictac = rand()%2;
              if(selectedAI)
              {
                it->_state = UserState::PlayOn;
                it->_opponentID = 0;
                it->_socket->send(confirm);
              }
              else 
              {
                it->_state = UserState::Online;
                for(auto other : _users)
                  if(other != it)
                    if(other->_state == UserState::Online)
                      if(other->_x == it->_x && other->_y == it->_y)
                      {
                        it->_state = UserState::PlayOn;
                        other->_state = UserState::PlayOn;
                        it->_opponentID = other->_id;
                        other->_opponentID = it->_id;
                        it->_tictac = !other->_tictac;
                        Packet confirmOther(confirm);
                        confirm << it->_tictac;
                        confirmOther << other->_tictac;
                        it->_socket->send(confirm);
                        other->_socket->send(confirmOther);
                        break;
                      }
              }
            }
            break;
          case MessageType::Move:
            {
              if(it->_opponentID != 0)
              {
                for(auto other : _users)
                  if(other->_id == it->_opponentID)
                  {
                    string tmp;
                    packet >> tmp;
                    Packet sendPack;
                    istringstream ss(tmp);
                    Uint32 x,y;
                    ss >> x >> y;
                    it->_grid[x][y] = it->_tictac?1:2;
                    other->_grid[x][y] = it->_tictac?1:2;
                    Int32 dir;
                    MatchState ms = GetStateMatch(it->_grid,{it->_x,it->_y}, {x,y}, dir);
                    sendPack << ms;

                    ostringstream ss2;

                    ss2 << " " << x << " " << y << " ";
                    if(ms == MatchState::WinO || ms == MatchState::WinX)
                    {
                      ss2 << dir;
                    }
                    else 
                      ss2 << "-1";
                    tmp = ss2.str();
                    cout << tmp;

                    sendPack << tmp;
                    if(ms == MatchState::WinO || ms == MatchState::WinX)
                    {
                      it->_socket->send(sendPack);
                    }
                    other->_socket->send(sendPack);
                    break; 
                  }
              }
              else
              {
                /* code */
              }
              
            }
            break;
          case MessageType::Disconnect://todo
            break;
        }
      }
    }
  }
}

void Server::SafeConnect(User *reConUser, TcpSocket *socket)
{
  reConUser->_socket = socket;
}

MatchState Server::GetStateMatch(Int32 **grid, Vector2i size, Vector2i turn, Int32 &direct)
{
  Int32 cnt[4] = {1,1,1,1};
  Int32 side = grid[turn.x][turn.y];
  Vector2i offset[4] = {{0, 1},{1, 0},{1,1},{1,-1}};
  for(Int32 i = 0; i < 4; i++)
  {
    for(Vector2i j = (turn + offset[i]); CheckBorder(size, j) && side == grid[j.x][j.y] && cnt[i] < 5; j+=offset[i]) cnt[i]++;
    for(Vector2i j = (turn - offset[i]); CheckBorder(size, j) && side == grid[j.x][j.y] && cnt[i] < 5; j-=offset[i]) cnt[i]++;
    if(cnt[i]==5)
    {
      direct = i;
      return side == 1?MatchState::WinO:MatchState::WinX;
    }
  }
  return MatchState::GO;
}

bool Server::CheckBorder(Vector2i b, Vector2i p)
{
  return p.x < b.x && p.y < b.y && p.x >= 0 && p.y >= 0;
}