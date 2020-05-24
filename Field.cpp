#include "Field.hpp"

Field::Field(Vector2f p, Uint32 yCell, Uint32 xCell):PartGUI(p, yCell*px, xCell*px), _yCell(yCell), _xCell(xCell)
{
  _grid = new int*[_xCell];
  for(int i=0; i < _xCell; i++)
  {
    _grid[i] = new int[_yCell];
    for(int j=0; j < _yCell; j++)
      _grid[i][j] = 0;
  }
  _free.loadFromFile("free.png");
  _o.loadFromFile("o.png");
  _x.loadFromFile("x.png");
}

void Field::DrawTo(RenderWindow &w)
{
  Sprite s;
  for(int i=0; i < _xCell; i++)
    for(int j=0; j < _yCell; j++)
    {
      switch(_grid[i][j])
      {
        case 0:
          s.setTexture(_free);
          break;
        case 1:
          s.setTexture(_o);
          break;
        case 2:
          s.setTexture(_x);
          break;
      }
      s.setPosition(_p.y + j*px,_p.x + i*px);
      w.draw(s);
    }
}

Field::~Field()
{
  for(int i=0; i < _xCell; i++)
  {
    delete _grid[i];
  }
  delete _grid;
}