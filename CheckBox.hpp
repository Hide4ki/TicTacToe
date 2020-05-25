#pragma once

#include "VisualComponent.hpp"

class CheckBox : public VisualComponent
{
public:
  CheckBox(Vector2f, Texture&, Texture&);
  void DrawTo(RenderWindow&) override;
  void OnClick() override;
  string GetValue() override;
  void SetValue(string) override;
private:
  Sprite _body;
  Texture *_yes;
  Texture *_no;
  bool _value;
  void ReSize(Vector2f)override{}
};