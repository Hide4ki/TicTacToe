#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextBox.hpp"
#include "Button.hpp"
#include "BG.hpp"
#include "Field.hpp"
#include "Client.hpp"

using namespace std;
using namespace sf;

int main() 
{
  Client *helper = new Client();
  helper->Connect();
  helper->Login();
  return 0;
}

void Client::Connect()
{ 
  string ip;
  string port;
  _gui.RunConnectWin(port, ip);
  cout << ip << endl;
  cout << port << endl;
}

void Client::Login()
{
  string login;
  string pass;
  _gui.RunLoginWin(login, pass);
  cout << login << endl;
  cout << pass << endl;
}