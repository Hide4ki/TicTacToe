#pragma once

#include "VisualComponent.hpp"
#include <sstream>

class InputBox : public VisualComponent
{
public:
  InputBox(Vector2f, Vector2f, Font&, Color, Color, Int32, Int32);
  void DrawTo(RenderWindow&) override;
  void OnClick() override;
  bool isMouseOver(RenderWindow&) override;
  void Record(Event&);
private:
  Text _body;
  string _cout;  
  Int32 _limit;
  bool _select;
  void Enter(Uint32);
};