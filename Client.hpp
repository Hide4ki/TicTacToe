#include <string>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "GUI.hpp"
#include "NetManager.hpp"

using namespace std;
using namespace sf;

class Client
{
public:
  void Connect();
  void Login();
private:
  GUI _gui;
};