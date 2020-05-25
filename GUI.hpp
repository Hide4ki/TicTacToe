#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "PartGUI.hpp"
#include "WindowType.hpp"
#include "BG.hpp"
#include "TextBox.hpp"
#include "Button.hpp"

using namespace std;
using namespace sf;
class PartGUI;

class GUI
{
public:
  void RunConnectWin(string &, string &);
  void RunLoginWin(string &, string &);
  void RunField();
private:
  
};