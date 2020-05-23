#include <iostream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "User.hpp"

using namespace std;
using namespace sf;


int main() 
{
  TcpListener listener;
  SocketSelector selector;
  vector<User*> clients;

  listener.listen(1132);
  selector.add(listener);

  while (true) 
  {
    if (selector.wait()) 
    {
      if (selector.isReady(listener)) 
      {
        TcpSocket *socket = new TcpSocket;
        User *pl = new User;
        listener.accept(*socket);
        Packet packet;
        Uint32 id;
        if (socket->receive(packet) == Socket::Done)
            packet >> id;
        pl->id = id;
        pl->socket = socket;
        clients.push_back(pl);
        Packet pList;
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
              sendPacket << y << x;
            }
          }
        }
      }
    }
  }

  for(vector<User*>::iterator it = clients.begin(); it != clients.end(); it++)
  {
    delete (*it)->socket;
    delete *it;
  }

  system("pause");
  return 0;
}