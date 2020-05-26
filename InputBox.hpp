#pragma once

#include "VisualComponent.hpp"

class InputBox : public VisualComponent
{
public:
  InputBox(Vector2f, Vector2f, Font&, Color, Int32, Int32);
  void DrawTo(RenderWindow&) override;
  void OnClick() override;
  bool isMouseOver(RenderWindow&) override;
  void AddCh(Event&) override;
  string GetValue() override;
  VisualComponent *SetValue(string) override;
private:
  Text _body;
  string _cout;  
  Int32 _limit;
  bool _select;
  Vector2f _fnStatic;
  void Enter(Uint32);
};