#pragma once

#include <vector>
#include "VisualComponent.hpp"
#include "WindowTTTBuilder.hpp"
#include "BorderDecor.hpp"
#include "Button.hpp"
#include "HeaderDecor.hpp"
#include "InputBox.hpp"
#include "BackGroundDecor.hpp"
#include "OutputBox.hpp"
#include "CheckBox.hpp"
#include "Field.hpp"

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