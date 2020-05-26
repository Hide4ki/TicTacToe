#pragma once

#include "VisualComponent.hpp"

class OutputBox : public VisualComponent
{
public:
  OutputBox(Vector2f, Vector2f, Font&, Color, Int32);
  void DrawTo(RenderWindow&) override;
  void OnClick() override;
  string GetValue() override;
  VisualComponent *SetValue(string) override;
private:
  Text _body;
  Vector2f _fnStatic;
};