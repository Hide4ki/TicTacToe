#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

using namespace sf;

const int w = 20;
const int h = 20;

int size = 32;

int grid[w][h];

int main()
{
  TcpListener listener;

  if(listener.listen(5300) != Socket::Done)
  {
    return -1;
  }

  TcpSocket client;
  if(listener.accept(client) != Socket::Done)
  {
    return -2;
  } 

  char data[5] = "hel2";

  if(client.send(data, 100) != Socket::Done)
  {
    return -3;
  }

  std::size_t received;
  if(client.receive(data, 5, received) != Socket::Done)
  {
    return -4;
  }
  std::cout << data << std::endl;
  RenderWindow  window( VideoMode(size*w,size*h), "Test!", Style::Close);
  
  Texture free;
  free.loadFromFile("free.png");

  Texture o;
  o.loadFromFile("o.png");

  Texture x;
  x.loadFromFile("x.png");
  

  Sprite s;

  for(int i=0; i < w; i++)
    for(int j=0; j < h; j++)
    {
      grid[i][j] = 0;
    }
  
  bool trig = true;

  while (window.isOpen()) 
  {
    Vector2i pos = Mouse::getPosition(window);
    int X = pos.x/32;
    int Y = pos.y/32;

    Event event;

    while(window.pollEvent(event))
    {
      if(event.type == Event::Closed)
        window.close();
      
      if(event.type == Event::MouseButtonPressed && grid[Y][X] == 0)
        if(trig) 
        {
          grid[Y][X] = 1; 
          trig = false;
        }
        else 
        {
          grid[Y][X] = 2; 
          trig = true;
        }
    }

    window.clear();
    
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
        s.setPosition(j*size,i*size);
        window.draw(s);
      }
    window.display();
  }
  return 0;
}