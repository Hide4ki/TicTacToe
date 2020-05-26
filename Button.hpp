#pragma once

#include "VisualComponent.hpp"

class Button : public VisualComponent
{
public:
  Button(Vector2f, Vector2f, Color);
  Button() = delete;
  void DrawTo(RenderWindow&) override;
  void OnClick() override;
  void ReSize(Vector2f) override;
private:
  RectangleShape _body; 

};