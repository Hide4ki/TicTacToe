#include "WindowTTT.hpp"

int main() 
{
  Texture free;
  Texture O;
  Texture Ow;
  Texture X;
  Texture Xw;
  Font font;
  TcpSocket socket;
  WindowTTT *w1;  
  WindowTTT *w2;  
  WindowTTT *w3;  
  try
  {
    if (!font.loadFromFile("arial.ttf"))
      throw MyException("Error 1:font not found");
    if(!free.loadFromFile("free.png"))
      throw MyException("Error 2:Texrure not found");
    if(!O.loadFromFile("o.png"))
      throw MyException("Error 2:Texrure not found");
    if(!X.loadFromFile("x.png"))
      throw MyException("Error 2:Texrure not found");
    if(!Ow.loadFromFile("owin.png"))
      throw MyException("Error 2:Texrure not found");
    if(!Xw.loadFromFile("xwin.png"))
      throw MyException("Error 2:Texrure not found");

    w1 = new WindowTTT((new WindowTTTBuilder())->\
    SetWinName("Connect")->\
    SetStyle(Style::Close)->\
    AddInputTextBox(new HeaderDecor(new BorderDecor(new BackGroundDecor(new InputBox({30,50}, {190,75}, font, Color::Black, 20, 15),Color::White), 3, Color::Red), "Enter Server IP", font, {0, -30},Color::White, 20, false, false))->\
    AddInputTextBox(new HeaderDecor(new BorderDecor(new BackGroundDecor(new InputBox({230,50}, {390,75}, font, Color::Black, 20, 5),Color::White), 3, Color::Red), "Enter Server Port", font, {0, -30},Color::White, 20, false, false))->\
    AddButton(new HeaderDecor(new BorderDecor(new Button({25,105},{395,135}, Color::White), 3, Color::Red),"Connect", font, {0,0}, Color::Black, 20, true, true))->\
    SetWinSize({420,150})->\
    SetMessageType(MessageType::Connect)->\
    SetSocket(&socket)->\
    SetTypeWin(WinType::Connect));

    w1->WindowHandler();


    w2 = new WindowTTT((new WindowTTTBuilder())->\
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
    w2->WindowHandler();  

    Packet packet;
    Uint32 a , b;
    bool f;
    if(socket.receive(packet) == Socket::Done)
    {
      if(!(packet >> a >> b >> f))
        throw MyException("Error 6: failed to read config from receive packet");
    }
    else
      throw MyException("Error 5: connection failure");
    

    if(a > 25 || a < 5 || b < 5 || b > 25)
      throw MyException("Error 99: Size field out of limit(5-25)");

    w3 = new WindowTTT((new WindowTTTBuilder())->\
    SetWinName("Play")->SetStyle(Style::Close)->\
    AddField(new BorderDecor(new Field({30,30},a,b,free,X,O,Xw,Ow,f), 3, Color::Red))->\
    SetWinSize({a*32 + 60,b*32 + 60})->\
    SetMessageType(MessageType::Move)->\
    SetSocket(&socket));

    w3->WindowHandler(); 
  }
  catch(const MyException &e)
  {
    e.what();
  }
  delete w1;
  delete w2;
  delete w3;
  socket.disconnect();
  return 0;
}