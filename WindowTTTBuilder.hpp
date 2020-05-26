#pragma once
#include "WindowTTT.hpp"
#include "MessageType.hpp"
#include "WinType.hpp"

class WindowTTTBuilder
{
public:
  WindowTTTBuilder();
  WindowTTTBuilder *SetWinName(string);
  WindowTTTBuilder *SetWinSize(Vector2f);
  WindowTTTBuilder *SetStyle(Uint32);
  WindowTTTBuilder *AddButton(VisualComponent*);
  WindowTTTBuilder *AddField(VisualComponent*);
  WindowTTTBuilder *AddInputTextBox(VisualComponent*);
  WindowTTTBuilder *AddOutputTextBox(VisualComponent*);
  WindowTTTBuilder *AddCheckBox(VisualComponent*);
  WindowTTTBuilder *SetMessageType(MessageType);
  WindowTTTBuilder *SetSocket(TcpSocket*);
  WindowTTTBuilder *SetTypeWin(WinType);
private:
  string _winName;
  Vector2f _size;
  Uint32 _style;
  VisualComponent *_button;
  VisualComponent *_field;
  vector<VisualComponent*> _itextb;
  vector<VisualComponent*> _otextb;
  vector<VisualComponent*> _chb;
  TcpSocket *_socket;
  MessageType _message;
  WinType _type;
  friend class WindowTTT;
};