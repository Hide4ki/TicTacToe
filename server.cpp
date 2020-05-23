#include "Server.hpp"

using namespace std;
using namespace sf;

int main() 
{
  Server *myServer = Server::Instance();

  while (true) 
  {
    myServer->Work();
  }

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

Server::Server()
{
  _listener.listen(1132);
  _selector.add(_listener);
}

void Server::Work()
{
  if (_selector.wait()) 
  {
    if (_selector.isReady(_listener)) 
    {
      TcpSocket *socket = new TcpSocket;
      User *pl = new User;
      _listener.accept(*socket);
      Packet packet;
      Uint32 id;
      if (socket->receive(packet) == Socket::Done)
          packet >> id;
      pl->id = id;
      pl->socket = socket;
      _clients.push_back(pl);
      Packet pList;
      pList << (Uint32)_clients.size();
      for(auto i : _clients)
        pList << i->id;
      socket->send(pList);
      _selector.add(*socket);
    }
    else 
    {
      Packet packet;
      for (int i = 0; i < _clients.size(); i++) 
      {
        if (_selector.isReady(*(*_clients[i]).socket)) 
        {
          if ((*_clients[i]).socket->receive(packet) == Socket::Done) 
          {
            Uint32 x, y;
            cout << "user id = " <<  (*_clients[i]).id << endl;
            if(packet >> y >> x)
              cout << "Pack true" << endl;
            cout << y << " " << x << endl;
            Packet sendPacket;
            sendPacket << y << x;
          }
        }
      }
    }
  }
}

void Server::Stop()
{
  delete this;
}

Server::~Server()
{
  _instance = 0;
  
  for(auto it : _clients)
  {
    delete it->socket;
    delete it;
  }
}