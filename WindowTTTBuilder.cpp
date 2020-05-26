#include "WindowTTTBuilder.hpp"

WindowTTTBuilder::WindowTTTBuilder()
{
  _winName = "TicTacToe";
  _style = Style::Default;
  _size = {640, 480};
  _button = 0;
  _field = 0;
}

WindowTTTBuilder *WindowTTTBuilder::SetWinName(string name)
{
  _winName = name;
  return this;
}

WindowTTTBuilder *WindowTTTBuilder::SetWinSize(Vector2f size)
{
  _size = size;
  return this;
}

WindowTTTBuilder *WindowTTTBuilder::SetStyle(Uint32 style)
{
  _style = style;
  return this;
}

WindowTTTBuilder *WindowTTTBuilder::AddButton(VisualComponent *but)
{
  if(_button == 0)
    _button = but;
  else
  {
    delete _button;
    _button = but;
  }
  return this;
}

WindowTTTBuilder *WindowTTTBuilder::AddField(VisualComponent *field)
{
  if(_field == 0)
    _field = field;
  else
  {
    delete _button;
    _field = field;
  }
  return this;
}

WindowTTTBuilder *WindowTTTBuilder::AddInputTextBox(VisualComponent *vc)
{
  _itextb.push_back(vc);
  return this;
}

WindowTTTBuilder *WindowTTTBuilder::AddOutputTextBox(VisualComponent *vc)
{
  _otextb.push_back(vc);
  return this;
}

WindowTTTBuilder *WindowTTTBuilder::AddCheckBox(VisualComponent *vc)
{
  _chb.push_back(vc);
  return this;
}

WindowTTTBuilder *WindowTTTBuilder::SetSocket(TcpSocket *s)
{
  _socket = s;
  return this;
}

WindowTTTBuilder *WindowTTTBuilder::SetMessageType(MessageType m)
{
  _message = m;
  return this;
}

WindowTTTBuilder *WindowTTTBuilder::SetTypeWin(WinType wt)
{
  _type = wt;
  return this;
}