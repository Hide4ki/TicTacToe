#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "VisualComponent.hpp"
#include "WindowTTTBuilder.hpp"

class WindowTTTBuilder;

class WindowTTT
{
public:
  WindowTTT(WindowTTTBuilder *);
  void WindowHandler();
  ~WindowTTT();
private:
  RenderWindow _window;
  VisualComponent *_button;
  VisualComponent *_field;
  vector<VisualComponent*> _itextb;
  vector<VisualComponent*> _otextb;
  vector<VisualComponent*> _chb;
};