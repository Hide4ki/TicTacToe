#pragma once

#include "VisualComponent.hpp"
#include <sstream>

class InputBox : public VisualComponent
{
public:
  InputBox(Vector2f, Vector2f, Font&, Color, Color, Int32);
  void DrawTo(RenderWindow&) override;
  void OnClick() override;
  bool isMouseOver(RenderWindow&) override;
  void Record(Event&);
private:
  Text _body;
  ostringstream _cout;  
  bool _select;
};