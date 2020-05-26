#pragma once

#include "VisualComponent.hpp"

class Field : public VisualComponent
{
public: 
  Field(Vector2f, Int32, Int32, Texture&, Texture&, Texture&, Texture&, Texture&, bool);
  void DrawTo(RenderWindow&)override;
  void OnClick() override;
  string GetValue() override;
  VisualComponent *SetValue(string) override;
  bool isMouseOver(RenderWindow &) override;
  virtual ~Field();
private:
  Sprite _body;
  Uint32 **_grid;
  Uint32 _h;
  Uint32 _w;
  Int32 _x;
  Int32 _y;
  Texture *_X;
  Texture *_O;
  Texture *_Xwin;
  Texture *_Owin;
  Texture *_free;
  bool _side;
  void ReSize(Vector2f)override{};
};