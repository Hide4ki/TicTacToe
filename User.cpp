#include "User.hpp"

using namespace std;

User::User():_socket(0), _state(UserState::InvalidState)
{
  _grid = 0;
}

User::~User()
{
  _socket->disconnect();
  delete _socket;
}