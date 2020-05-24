#include <string>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "TextBox.hpp"

using namespace std;
using namespace sf;

int main() {

  IpAddress ip = "192.168.1.233";
  TcpSocket socket;
  Uint32 id;

  cout << "Введите свой id: ";
  cin >> id;

  socket.connect(ip, 1132);

  RenderWindow Window(VideoMode(h*px, w*px, 32), "Client Test", Style::Close);

  vector<RectangleShape> rects;

  {
    Packet packet;
    packet << id;
    socket.send(packet);
    Packet pList;
    socket.receive(pList);
    Uint32 n;
    pList >> n;
    cout << "Player list" << endl;
    for(int i=0; i<n; i++)
    {
      Uint32 tmp;
      pList >> tmp;
      cout << tmp << " ";  
    }
    cout << endl;
  }


  while(Window.isOpen()) {
    Event event;
    Vector2i pos = Mouse::getPosition(Window);
    sf::Uint32 X = pos.x/32;
    sf::Uint32 Y = pos.y/32;

    while (Window.pollEvent(event)) {
        switch (event.type) {
        case Event::Closed:
          Window.close();
          break;
        case Event::KeyPressed:
          if (event.key.code == Keyboard::Escape)
              Window.close();
          break;
        case Event::MouseButtonPressed:
          if(grid[Y][X] == 0)
          {
            grid[Y][X] = myfig; 
            fSend = true;
          }
          break;
        }
    }

            
    if(fSend)
      {
        cout << "send" << endl;
        cout << Y << "\t" << X << endl;
        Packet packet;
        packet << Y << X;
        socket.send(packet);
        Packet sPack;
        socket.receive(sPack);
        Uint32 x,y;
        sPack >> x >> y;
        grid[x][y] = opfig;
        fSend = false;
      }
    //socket.receive(packet);
    Window.clear();
    for(int i=0; i < w; i++)
      for(int j=0; j < h; j++)
      {
        switch(grid[i][j])
        {
          case 0:
            s.setTexture(free);
            break;
          case 1:
            s.setTexture(o);
            break;
          case 2:
            s.setTexture(x);
            break;
        }
        s.setPosition(j*px,i*px);
        Window.draw(s);
      
    Window.display();
  }

  system("pause");
  return 0;
}