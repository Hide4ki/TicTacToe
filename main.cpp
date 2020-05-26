#include <thread>
#include <iostream>
#include "WindowTTT.hpp"

using namespace std;
using namespace sf;

int main() 
{
  Texture free;
  free.loadFromFile("free.png");
  Texture O;
  O.loadFromFile("o.png");
  Texture X;
  X.loadFromFile("x.png");
  Texture Ow;
  Ow.loadFromFile("owin.png");
  Texture Xw;
  Xw.loadFromFile("xwin.png");
  Font font;
  if (!font.loadFromFile("arial.ttf"))
    cout << "Font not found!\n";  
  TcpSocket socket;

  WindowTTT *w1 = new WindowTTT((new WindowTTTBuilder())->\
  SetWinName("Connect")->\
  SetStyle(Style::Close)->\
  AddInputTextBox(new HeaderDecor(new BorderDecor(new BackGroundDecor(new InputBox({30,50}, {190,75}, font, Color::Black, 20, 15),Color::White), 3, Color::Red), "Enter Server IP", font, {0, -30},Color::White, 20, false, false))->\
  AddInputTextBox(new HeaderDecor(new BorderDecor(new BackGroundDecor(new InputBox({230,50}, {390,75}, font, Color::Black, 20, 5),Color::White), 3, Color::Red), "Enter Server Port", font, {0, -30},Color::White, 20, false, false))->\
  AddButton(new HeaderDecor(new BorderDecor(new Button({25,105},{395,135}, Color::White), 3, Color::Red),"send", font, {0,0}, Color::Black, 20, true, true))->\
  SetWinSize({420,150})->\
  SetMessageType(MessageType::Connect)->\
  SetSocket(&socket)->\
  SetTypeWin(WinType::Connect));

  w1->WindowHandler();

  WindowTTT *w5 = new WindowTTT((new WindowTTTBuilder())->\
  SetWinName("Match configuration")->\
  SetStyle(Style::Close)->\
  AddCheckBox((new HeaderDecor(new BorderDecor(new CheckBox({35,46}, X, free), 3, Color::Red), "AI", font, {5, -32},Color::White, 20, false, false))->SetValue("Y"))->\
  AddCheckBox((new HeaderDecor(new BorderDecor(new CheckBox({95,46}, X, free), 3, Color::Red), "5x5", font, {0, -32},Color::White, 20, false, false))->SetValue("N"))->\
  AddCheckBox((new HeaderDecor(new BorderDecor(new CheckBox({155,46}, X, free), 3, Color::Red), "15x15", font, {-12, -32},Color::White, 20, false, false))->SetValue("Y"))->\
  AddCheckBox((new HeaderDecor(new BorderDecor(new CheckBox({215,46}, X, free), 3, Color::Red), "19x19", font, {-13, -32},Color::White, 20, false, false))->SetValue("N"))->\
  AddInputTextBox(new HeaderDecor(new BorderDecor(new BackGroundDecor(new InputBox({280,50}, {305,75}, font, Color::Black, 20, 2),Color::White), 3, Color::Red), "Other", font, {25, -30},Color::White, 20, false, false))->\
  AddInputTextBox(new HeaderDecor(new BorderDecor(new BackGroundDecor(new InputBox({345,50}, {370,75}, font, Color::Black, 20, 2),Color::White), 3, Color::Red), "X", font, {-25, 0},Color::White, 30, false, false))->\
  AddButton(new HeaderDecor(new BorderDecor(new Button({25,105},{385,135}, Color::White), 3, Color::Red),"confirm", font, {0,0}, Color::Black, 20, true, true))->\
  SetWinSize({420,150})->\
  SetMessageType(MessageType::Config)->\
  SetSocket(&socket)->\
  SetTypeWin(WinType::Config));

  while(true)
  {
    w5->WindowHandler();  
    Packet packet;
    Uint32 a , b;
    bool f;
    if(socket.receive(packet) == Socket::Done)
    {
      packet >> a >> b >> f;
    }


    WindowTTT *w4 = new WindowTTT((new WindowTTTBuilder())->\
    SetWinName("Play")->SetStyle(Style::Close)->\
    AddField(new BorderDecor(new Field({30,30},a,b,free,X,O,Xw,Ow,f), 3, Color::Red))->\
    SetWinSize({a*32 + 60,b*32 + 60})->\
    SetMessageType(MessageType::Move)->\
    SetSocket(&socket));

    w4->WindowHandler(); 
  }
    // WindowTTT *w3 = new WindowTTT((new WindowTTTBuilder())->\
    // SetWinName("Error")->SetStyle(Style::Close)->\
    // AddOutputTextBox((new BorderDecor(new BackGroundDecor(new OutputBox({30,25}, {390,50}, font, Color::Black, 20),Color::White), 3, Color::Red))->SetValue("Test Error"))->\
    // AddButton(new HeaderDecor(new BorderDecor(new Button({25,80},{395,115}, Color::White), 3, Color::Red),"Ok", font, {0,0}, Color::Black, 20, true, true))->\
    // SetWinSize({420,125}));

    // w3->WindowHandler();
  socket.disconnect();
  return 0;
}