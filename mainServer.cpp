#include "Server.hpp"

int main() 
{
  Server *myServer;
  try
  {
    myServer = Server::Instance();
  
    srand(time(NULL));

    while (!myServer->isWasStoped()) 
      myServer->Work();
  }
  catch(MyException& e)
  {
    e.what();
  }
  
  myServer->Stop();
  return 0;
}