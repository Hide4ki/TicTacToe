#include "Server.hpp"

using namespace std;
using namespace sf;

int main() 
{
  Server *myServer = Server::Instance();

  while (true) 
    myServer->Work();

  myServer->Stop();
  return 0;
}

Server* Server::_instance = 0;
Server* Server::Instance()
{
  if(_instance == 0)
  {
    _instance = new Server;
  }
  return _instance;
}

Server::Server()
{
  _listener.listen(1132);
  _selector.add(_listener);
  ifstream fin(fileUsers);
  fin >> _protoId;

  int numUser;
  fin >> numUser;
  for(int i = 0; i<numUser; i++)
  {
    User *lUser = new User;
    fin >> *lUser;
    _users.push_back(lUser);
  }
}

void Server::Work()
{
  if (_selector.wait()) 
    if (_selector.isReady(_listener)) 
      ConnectUser();
    else 
      Proccessing();
}

void Server::Stop()
{
  ofstream fout(fileUsers);
  fout << _protoId;
  fout << _users.size();
  for(auto it : _users)
    fout << *it;
    
  delete this;
}

Server::~Server()
{
  _instance = 0;

  for(auto it : _users)
  {
    delete it->_socket;
    delete it;
  }
}

bool Server::isRegistered(string &login)
{
  bool result = false;
  for(auto it : _users)
    if(login == it->_login)
    {
      result = true;
      break;
    }
  return result;
}

User *Server::Registration(string &login, Uint32 password)
{
  User *newUser = new User(login, password);
  newUser->_id = _protoId++;
  _users.push_back(newUser);
  return newUser;
}

void Server::ConnectUser()
{
  TcpSocket *socket = new TcpSocket;
  User *conUser;
  Packet packet;
  string login;
  Uint32 pass;
  bool fReg;

  if (socket->receive(packet) == Socket::Done)
    if(packet >> login >> pass >> fReg)
    {
      //todo 
    };

  if(!isRegistered(login))
    conUser = fReg?Registration(login, pass):0; 
  else
    conUser = Login(login, pass);

  if(conUser == 0)
  {
    //todo
  }

  SafeConnect(conUser, socket);
  
  if(_listener.accept(*socket) != Socket::Done)
  { 
    ;//todo;
  }

  Packet ans;
  ans << Error::None;//todo
  socket->send(ans);

  _selector.add(*socket);
}

void Server::Proccessing()
{
  for (auto it : _users) 
  {
    if (_selector.isReady(*it->_socket)) 
    {
      Packet packet;
      if (it->_socket->receive(packet) == Socket::Done) 
      {
        MessageType typePack;
        if(packet >> typePack)
          ;//todo

        switch(typePack)
        {
          case MessageType::Move://todo
            break;
          case MessageType::Invit://todo
            break;
          case MessageType::InvitAns://todo
            break;
          case MessageType::Disconnect://todo
            break;
        }
      }
    }
  }
}

User* Server::Login(string &login, Uint32 pass)
{
  auto result = find_if(_users.begin(), _users.end(),[&login, &pass](const User *u)->bool{return u->CheckLogin(login) && u->CheckPass(pass);});
  return result == _users.end()?0: *result;
}

void Server::SafeConnect(User *reConUser, TcpSocket *socket)
{
  reConUser->_socket = socket;
}