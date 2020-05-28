#include "User.hpp"

using namespace std;

User::User():_socket(0), _state(UserState::InvalidState)
{
  _grid = 0;
  _AIgrid = 0;
}

User::~User()
{
  _socket->disconnect();
  delete _socket;
}

void User::DeleteGrid()
{
  if(_grid != 0)
  {
    for(Uint32 i = 0; i < _x; i++)
      delete[] _grid[i];
    delete[] _grid;
  }
  if(_AIgrid != 0)
  {
    for(Uint32 i = 0; i < _x; i++)
      delete[] _AIgrid[i];
    delete[] _AIgrid;
  }
}