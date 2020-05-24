#pragma once


#include "Decorator.hpp"
#include <string>

using namespace std;

class HeaderDecor : public Decorator
{
public:
  HeaderDecor(VisualComponent*, string, Font&, Vector2f, Color, Int32, bool, bool);
  void DrawTo(RenderWindow&) override;
  void ReSize(Vector2f) override;
private:
  Text _body;
  bool _in;
  bool _center;
  void InComponent();
  void Center();
};