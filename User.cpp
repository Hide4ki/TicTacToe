#include "User.hpp"

using namespace std;

User::User(string &login, Uint32 password):_login(login), _password(password), _id(0), _cntWon(0), _cntLost(0), _cntGame(0), _socket(0), _state(UserState::InvalidState)
{
}

User::~User()
{

}

bool User::CheckLogin(string &login) const
{
  return login == _login;
}

bool User::CheckPass(Uint32 pass) const
{
  return pass == _password;
}

ofstream &operator<<(ofstream &stream, const User &u)
{
  stream << u._id << endl;
  stream << u._login << endl;
  stream << u._password << endl;
  stream << u._cntWon << endl;
  stream << u._cntLost << endl;
  stream << u._cntGame << endl;
  return stream;
}

ifstream &operator>>(ifstream &stream, User &u)
{
  stream >> u._id;
  stream >> u._login;
  stream >> u._password;
  stream >> u._cntWon;
  stream >> u._cntLost;
  stream >> u._cntGame;
  return stream;
}