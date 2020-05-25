#pragma once
#include "WindowTTT.hpp"

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
private:
  string _winName;
  Vector2f _size;
  Uint32 _style;
  VisualComponent *_button;
  VisualComponent *_field;
  vector<VisualComponent*> _itextb;
  vector<VisualComponent*> _otextb;
  vector<VisualComponent*> _chb;
  friend class WindowTTT;
};