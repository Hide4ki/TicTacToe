#include "Field.hpp"
#include <sstream>

Field::Field(Vector2f st, Uint32 w, Uint32 h, Texture &f, Texture &x, Texture &o, bool side):VisualComponent(st,{0,0})
{
  _h = h;
  _w = w;
  _X = &x;
  _O = &o;
  _free = &f;
  _grid = new Uint32*[_w];
  for(Uint32 i = 0; i < _w; i++)
  {
    _grid[i] = new Uint32[_h];
    for (Uint32 j = 0; j < _h; j++)
      _grid[i][j] = 0; 
  }
  _side = side;
  VisualComponent::ReSize({_free->getSize().x * _w, _free->getSize().y * _h});
} 

Field::~Field()
{
  for(Uint32 i = 0; i < _w; i++)
  {
    delete[] _grid[i];
  }
  delete[] _grid;
}

void Field::DrawTo(RenderWindow &w)
{
  for(Uint32 i = 0; i < _w; i++)
    for (Uint32 j = 0; j < _h; j++)
    {
      switch(_grid[i][j])
      {
        case 0:
          _body.setTexture(*_free);
        break;
        case 1:
          _body.setTexture(*_O);
        break;
        case 2:
          _body.setTexture(*_X);
        break;
      }
      _body.setPosition({i*_free->getSize().x + VisualComponent::GetPosition().x,j*_free->getSize().y + VisualComponent::GetPosition().y});
      w.draw(_body);
    }
}

void Field::OnClick()
{
  _grid[_x][_y] = _side?1:2;
}

bool Field::isMouseOver(RenderWindow &w)
{
  _x = (Mouse::getPosition(w).x - VisualComponent::GetPosition().x)/_free->getSize().x;
  _y = (Mouse::getPosition(w).y - VisualComponent::GetPosition().y)/_free->getSize().y;
  return VisualComponent::isMouseOver(w);
}

VisualComponent *Field::SetValue(string s)
{
  istringstream sin(s);
  Uint32 x,y;
  sin >> x >> y;
  _grid[x][y] = !_side?1:2;
  return this;
}

string Field::GetValue()
{
  ostringstream sout;
  sout << _x << _y;
  return sout.str();
}