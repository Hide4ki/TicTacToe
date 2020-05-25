#pragma once 

#include "Decorator.hpp"

class BackGroundDecor : public Decorator 
{
public:
  BackGroundDecor(VisualComponent*, Color);
  void DrawTo(RenderWindow&);
  Vector2f GetPosition() override;
  Vector2f GetSize() override;
private:
  RectangleShape _body;
};