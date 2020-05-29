#include "Field.hpp"

Field::Field(Vector2f st, Int32 w, Int32 h, Texture &f, Texture &x, Texture &o, Texture &xw, Texture &ow, bool side):VisualComponent(st,{0,0})
{
  _h = h;
  _w = w;
  _X = &x;
  _O = &o;
  _Xwin = &xw;
  _Owin = &ow;
  _free = &f;
  _grid = new Uint32*[_w];
  for(Uint32 i = 0; i < _w; i++)
  {
    _grid[i] = new Uint32[_h];
    for (Uint32 j = 0; j < _h; j++)
      _grid[i][j] = 0; 
  }
  _side = side;
  _x = -1;
  _y = -1;
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
        case 3:
          _body.setTexture(*_Owin);
        break;
        case 4:
          _body.setTexture(*_Xwin);
        break;
      }
      _body.setPosition({i*_free->getSize().x + VisualComponent::GetPosition().x,j*_free->getSize().y + VisualComponent::GetPosition().y});
      w.draw(_body);
    }
}

void Field::OnClick()
{
  if(_grid[_x][_y] == 0)
    _grid[_x][_y] = _side?1:2;
  else
  {
    _x = -1;
    _y = -1;
  }
  
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
  Int32 dir;
  sin >> x >> y >> dir;
  dir += 1;
  if(_grid[x][y]==0)
    _grid[x][y] = !_side?1:2;
  if(dir != 0)
  {
    Vector2i offset[4] = {{0, 1},{1, 0},{1,1},{1,-1}};
    Vector2i turn{x,y};
    Int32 side = _grid[x][y];
    for(Vector2i j = (turn + offset[dir - 1]); j.x < _w && j.y < _h && j.x >= 0 && j.y >= 0 && side == _grid[j.x][j.y]; j+=offset[dir - 1]) _grid[j.x][j.y]+=2;
    for(Vector2i j = (turn - offset[dir - 1]); j.x < _w && j.y < _h && j.x >= 0 && j.y >= 0 && side == _grid[j.x][j.y]; j-=offset[dir - 1]) _grid[j.x][j.y]+=2;
    _grid[x][y]+=2;
  }
  
  
  return this;
}

string Field::GetValue()
{
  ostringstream sout;
  sout << _x << " " << _y << " " << _side;
  return sout.str();
}