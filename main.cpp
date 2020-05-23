#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class Player
{
  public:
  Uint32 id;
  TcpSocket *socket;
};

int main() 
{
  TcpListener listener;
  SocketSelector selector;
  vector<Player*> clients;

  listener.listen(1131);
  selector.add(listener);

  while (true) 
  {
    if (selector.wait()) 
    {
      if (selector.isReady(listener)) 
      {
        TcpSocket *socket = new TcpSocket;
        Player *pl = new Player;
        listener.accept(*socket);
        Packet packet;
        Uint32 id;
        if (socket->receive(packet) == Socket::Done)
            packet >> id;
        cout << id << " присоединился" << endl;
        pl->id = id;
        pl->socket = socket;
        clients.push_back(pl);
        Packet pList;
        cout << "На сервере " << (Uint32)clients.size() << endl;
        pList << (Uint32)clients.size();
        for(auto i : clients)
          pList << i->id;
        socket->send(pList);
        selector.add(*socket);
      }
      else 
      {

        Packet packet;
        for (int i = 0; i < clients.size(); i++) 
        {
          if (selector.isReady(*(*clients[i]).socket)) 
          {
            if ((*clients[i]).socket->receive(packet) == Socket::Done) 
            {
              Uint32 x, y;
              cout << "user id = " <<  (*clients[i]).id << endl;
              if(packet >> y >> x)
                cout << "Pack true" << endl;
              cout << y << " " << x << endl;
              Packet sendPacket;
              sendPacket << y+1 << x+1;
              (*clients[i]).socket->send(sendPacket);
            }
          }
        }
      }
    }
  }

  for(vector<Player*>::iterator it = clients.begin(); it != clients.end(); it++)
  {
    delete (*it)->socket;
    delete *it;
  }

  system("pause");
  return 0;
}