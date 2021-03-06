#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include "Key.hpp"

using namespace std;
using namespace sf;

class VisualComponent
{
public:
  VisualComponent(Vector2f, Vector2f);
  VisualComponent(const VisualComponent&) = delete;
  VisualComponent(VisualComponent&&) = delete;
  VisualComponent() = default;
  virtual ~VisualComponent() = default;  
  virtual void DrawTo(RenderWindow&) = 0;
  virtual bool isMouseOver(RenderWindow&);
  virtual void OnClick() = 0;
  virtual Vector2f GetPosition();
  virtual Vector2f GetSize();
  virtual void ReSize(Vector2f);
  virtual string GetValue();
  virtual VisualComponent *SetValue(string);
  virtual void AddCh(Event&);
private:
  Vector2f _st;
  Vector2f _fn;
};