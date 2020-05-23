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