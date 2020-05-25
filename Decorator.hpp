#pragma once

#include <SFML/Graphics.hpp>
#include "VisualComponent.hpp"

using namespace sf;

class Decorator : public VisualComponent
{
public:
  Decorator(VisualComponent*);
  Decorator() = delete;
  Decorator(const Decorator&) = delete;
  Decorator(Decorator&&) = delete;
  virtual ~Decorator(); 
  virtual void DrawTo(RenderWindow&);
  virtual bool isMouseOver(RenderWindow&);
  virtual void OnClick();
  virtual Vector2f GetPosition();
  virtual Vector2f GetSize();
  virtual void ReSize(Vector2f);
  virtual string GetValue();
  virtual void SetValue(string);
  virtual void AddCh(Event&);
private:
  VisualComponent *_component;
};
