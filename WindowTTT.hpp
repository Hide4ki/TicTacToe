#pragma once

#include <vector>
#include <SFML/Network.hpp>
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
#include "MessageType.hpp"
#include "WinType.hpp"
#include "ExPacket.hpp"
#include "MatchState.hpp"


class WindowTTTBuilder;

class WindowTTT
{
public:
  WindowTTT(WindowTTTBuilder *);
  void WindowHandler();
  string GetValue();
  ~WindowTTT();
private:
  RenderWindow _window;
  VisualComponent *_button;
  VisualComponent *_field;
  vector<VisualComponent*> _itextb;
  vector<VisualComponent*> _otextb;
  vector<VisualComponent*> _chb;
  TcpSocket *_socket;
  MessageType _message;
  WinType _type;
  string _value;
};