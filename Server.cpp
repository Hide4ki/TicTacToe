#include "Server.hpp"

Server* Server::_instance = 0;
Server* Server::Instance()
{
  if(_instance == 0)
  {
    _instance = new Server;
  }
  return _instance;
}

bool Server::isWasStoped()
{
  return _stop;
}

Server::Server()
{
  if(_listener.listen(7777) != Socket::Done)
    throw MyException("Error 7: port 7777 is not available!!");
  _selector.add(_listener);
  _protoId = 1;
  _stop = false;
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
  delete this;
}

Server::~Server()
{
  _instance = 0;
  _listener.close();
  _selector.clear();
  for(auto it : _users)
    delete it;
}

User *Server::Registration()
{
  User *newUser = new User();
  newUser->_id = _protoId++;
  _users.push_back(newUser);
  return newUser;
}

void Server::ConnectUser()
{
  TcpSocket *socket = new TcpSocket;
  User *conUser;
  Packet packet;

  conUser = Registration(); 

  SafeConnect(conUser, socket);
  if(_listener.accept(*socket) != Socket::Done)
    throw MyException("Error 8: new user connection failure!!");
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
        string tmp;
        MessageType typePack;
        if(!(packet >> typePack))
          throw MyException("Error 10: failed to read type of packet from receive packet");

        switch(typePack)
        {
          case MessageType::Config:
            Matchmaking(packet, it);
            break;
          case MessageType::Move:
            {
              if(it->_opponentID != 0)
              {
                for(auto other : _users)
                  if(other->_id == it->_opponentID)
                  {
                    string tmp;
                    packet >> tmp;

                    Packet sendPack;
                    istringstream ss(tmp);
                    Uint32 x,y;

                    ss >> x >> y;
                    it->_grid[x][y] = it->_tictac?1:2;
                    other->_grid[x][y] = it->_tictac?1:2;

                    Int32 dir;
                    MatchState ms = GetStateMatch(it->_grid,{it->_x,it->_y}, {x,y}, dir);
                    sendPack << ms;

                    ostringstream ss2;

                    ss2 << " " << x << " " << y << " ";
                    if(ms == MatchState::WinO || ms == MatchState::WinX)
                      ss2 << dir;
                    else 
                      ss2 << "-1";

                    tmp = ss2.str();

                    sendPack << tmp;

                    if(ms == MatchState::WinO || ms == MatchState::WinX || ms == MatchState::Tie)
                    {
                      it->_socket->send(sendPack);
                      it->DeleteGrid();
                      other->DeleteGrid();
                      it->_state = UserState::Offline;
                      other->_state = UserState::Offline;
                    }
                    other->_socket->send(sendPack);
                    break; 
                  }
              }
              else
              {
                string tmp;
                packet >> tmp;
                Packet sendPack;
                istringstream ss(tmp);
                Int32 x,y;
                ss >> x >> y;
                it->_grid[x][y] = it->_tictac?1:2;
                Int32 dir;
                MatchState ms = GetStateMatch(it->_grid,{it->_x,it->_y}, {x,y}, dir);
                Vector2i AImove;
                if(ms == MatchState::GO)
                {
                  AImove = GenerateAImove(it->_AIgrid, it->_grid, {it->_x,it->_y}, x, y);
                  it->_grid[AImove.x][AImove.y] = !it->_tictac?1:2;
                  it->_AIgrid[AImove.x][AImove.y] = 0;
                  MatchState ms = GetStateMatch(it->_grid,{it->_x,it->_y},{AImove.x,AImove.y}, dir);
                  sendPack << ms;
                  ostringstream ss2;
                  ss2 << " " << AImove.x << " " << AImove.y << " ";
                  if(ms == MatchState::WinO || ms == MatchState::WinX)
                  {
                    ss2 << dir;
                  }
                  else 
                    ss2 << "-1";
                  tmp = ss2.str();

                  sendPack << tmp;
                  if(ms == MatchState::WinO || ms == MatchState::WinX || ms == MatchState::Tie)
                  {
                    it->_socket->send(sendPack);
                    it->DeleteGrid();
                    it->_state = UserState::Offline;
                  }

                  it->_socket->send(sendPack);
                }
                
                else if(ms == MatchState::WinO || ms == MatchState::WinX || ms == MatchState::Tie)
                {
                  sendPack << ms;

                  ostringstream ss2;

                  ss2 << " " << x << " " << y << " "<< dir;

                  tmp = ss2.str();

                  sendPack << tmp;
                  it->_socket->send(sendPack);
                  it->DeleteGrid();
                  it->_state = UserState::Offline;
                  it->_socket->send(sendPack);
                }    
              }
              
            }
            break;
        }
      }
    }
  }
}

void Server::SafeConnect(User *reConUser, TcpSocket *socket)
{
  reConUser->_socket = socket;
}

MatchState Server::GetStateMatch(Int32 **grid, Vector2i size, Vector2i turn, Int32 &direct)
{
  Int32 cnt[4] = {1,1,1,1};
  Int32 side = grid[turn.x][turn.y];
  Vector2i offset[4] = {{0, 1},{1, 0},{1,1},{1,-1}};
  for(Int32 i = 0; i < 4; i++)
  {
    for(Vector2i j = (turn + offset[i]); CheckBorder(size, j) && side == grid[j.x][j.y] && cnt[i] < 5; j+=offset[i]) cnt[i]++;
    for(Vector2i j = (turn - offset[i]); CheckBorder(size, j) && side == grid[j.x][j.y] && cnt[i] < 5; j-=offset[i]) cnt[i]++;
    if(cnt[i]==5)
    {
      direct = i;
      return side == 1?MatchState::WinO:MatchState::WinX;
    }
  }
  for(Int32 i = 0; i < size.x; i++)
    for(Int32 j = 0; j < size.y; j++)
      if(grid[i][j]==0)
        return MatchState::GO;
  return MatchState::Tie;
}

bool Server::CheckBorder(Vector2i b, Vector2i p)
{
  return p.x < b.x && p.y < b.y && p.x >= 0 && p.y >= 0;
}

void Server::SetAIgrid(Int32 **grid, Int32 x, Int32 y)
{
  Int32 **visit = new Int32*[x];
  for(int i = 0; i < x; i++)
  {
    visit[i] = new Int32[y];
    for(int j = 0; j < y; j++)
      visit[i][j] = 0;
  }
  auto xx = x/2;
  auto yy = y/2;
  Vector2i border{x,y};
  visit[xx][yy] = 1;
  auto vmax = max(xx,yy);
  grid[xx][yy] = 100; 
  queue<Vector2i> pull;
  pull.push({xx,yy});
  Vector2i offset[8] = {{1,1},{1,0},{0,1},{1,-1},{-1,-1},{-1,0},{0,-1},{-1,1}};
  while(!pull.empty())
  {
    Vector2i now = pull.front(); 
    pull.pop();
    for(int i = 0; i < 8; i++)
    {
      Int32 x = (now + offset[i]).x;
      Int32 y = (now + offset[i]).y;
      if(CheckBorder(border, now + offset[i]) && visit[x][y] == 0)
      {
        grid[x][y] = rand()%100 + 1;
        pull.push({x,y});
        visit[x][y] = 1;
      }
    }
    visit[now.x][now.y] = 2;
  }
}

Vector2i Server::GenerateAImove(Int32 **AI, Int32 **grid, Vector2i size, Int32 &x, Int32 &y)
{
  AI[x][y] = 0;
  Int32 xx = x;
  Int32 yy = y;
  Int32 cntValue[4] = {1,1,1,1};
  Int32 cnt1[4] = {1,1,1,1};
  Int32 cnt2[4] = {1,1,1,1};
  Vector2i offset[4] = {{0, 1},{1, 0},{1,1},{1,-1}};
  Int32 maxPotential = 0;
  Vector2i moveAI;
  for(Int32 i = 0; i<size.x; i++)
    for(Int32 j = 0; j<size.y; j++)
    {
      if(AI[i][j] != 0)
      {
        CalcValueCell(grid,size,{i,j}, 1, cnt1);
        CalcValueCell(grid,size,{i,j}, 2, cnt2);
        if(maxPotential < AI[i][j] + GetAIValue(cnt1) + GetUserValue(cnt2))
        {
          maxPotential = AI[i][j] + GetAIValue(cnt1) + GetUserValue(cnt2);
          moveAI = {i,j};
        }
      }
    }
  return moveAI;
}

void Server::CalcValueCell(Int32 **grid, Vector2i size, Vector2i turn, Int32 side, Int32 *cnt)
{
  Vector2i offset[4] = {{0, 1},{1, 0},{1,1},{1,-1}};
  cnt[0] = 1;
  cnt[1] = 1;
  cnt[2] = 1;
  cnt[3] = 1;
  for(Int32 i = 0; i < 4; i++)
  {
    for(Vector2i j = (turn + offset[i]); CheckBorder(size, j) && side == grid[j.x][j.y] && cnt[i] < 5; j+=offset[i]) cnt[i]++;
    for(Vector2i j = (turn - offset[i]); CheckBorder(size, j) && side == grid[j.x][j.y] && cnt[i] < 5; j-=offset[i]) cnt[i]++;
  }
}

Int32 Server::GetUserValue(Int32 *cnt)
{
  Int32 place = 0;
  for(Int32 i = 0; i < 4; i++)
  {
    switch(cnt[i])
    {
      case 2:
        place += 50;
      break;
      case 3:
        place += 300;
      break;
      case 4:
        place += 10000;
      break;
      case 5:
        place += 50000;
      break;
    }
  }
  return place;
}


Int32 Server::GetAIValue(Int32 *cnt)
{
  Int32 place = 0;
  for(Int32 i = 0; i < 4; i++)
  {
    switch(cnt[i])
    {
      case 2:
        place += 110;
      break;
      case 3:
        place += 500;
      break;
      case 4:
        place += 5000;
      break;
      case 5:
        place += 100000;
      break;
    }
  }
  return place;
}

void Server::Matchmaking(Packet &packet, User*it)
{
  string value;
  bool sizeFound = false;
  bool selectedAI = false;

  for(int i = 0; i < 4; i++)
    if(packet >> value)
    {
      if(value == "Y" && !sizeFound)
        switch(i)
        {
          case 0:
            selectedAI = true;
          break;
          case 1:
            it->_x = 5;
            it->_y = 5;
            sizeFound = true;
          break;
          case 2:
            it->_x = 15;
            it->_y = 15;
            sizeFound = true;
          break;
          case 3:
            it->_x = 19;
            it->_y = 19;
            sizeFound = true;
          break;
        }
    }
  string x, y;
  if(!(packet >> x >> y))
    throw MyException("Error 11: failed to read config from receive packet");
    
  if(!sizeFound)
  {
    istringstream ss(x + " " + y);
    Uint32 a, b;
    ss >> a >> b;
    it->_x = a;
    it->_y = b;
  }

  Packet confirm;
  confirm << it->_x << it->_y;

  it->_grid = new Int32*[it->_x];
  for(int i = 0; i<it->_x;i++)
  {
    it->_grid[i] = new Int32[it->_y];
    for(int j = 0; j<it->_y; j++)
      it->_grid[i][j] = 0;
  }

  it->_tictac = rand()%2;

  if(selectedAI)
  {

    it->_state = UserState::PlayOn;
    it->_opponentID = 0;

    confirm << it->_tictac;
    if(it->_socket->send(confirm)!=Socket::Done)
      throw MyException("Error 12: failed send confirm");

    it->_AIgrid = new Int32*[it->_x];
    for(int i = 0; i<it->_x;i++)
      it->_AIgrid[i] = new Int32[it->_y];
    
    SetAIgrid(it->_AIgrid, it->_x, it->_y);

    if(it->_tictac)
    {
      Packet pack;
      pack << MatchState::GO;
      ostringstream ss2;
      ss2 << " " << it->_x/2<< " " << it->_y/2<< " " << "-1";
      pack << ss2.str();
      it->_grid[it->_x/2][it->_y/2] = 2;
      it->_AIgrid[it->_x/2][it->_y/2] = 0;

      if(it->_socket->send(pack)!=Socket::Done)
        throw MyException("Error 13: failed send AI move");
    }
  }
  else 
  {
    it->_state = UserState::Online;

    for(auto other : _users)
      if(other != it && other->_state == UserState::Online && other->_x == it->_x && other->_y == it->_y)
      {
        it->_state = UserState::PlayOn;
        other->_state = UserState::PlayOn;

        it->_opponentID = other->_id;
        other->_opponentID = it->_id;

        it->_tictac = !other->_tictac;

        Packet confirmOther(confirm);

        confirm << it->_tictac;
        confirmOther << other->_tictac;

        if(it->_socket->send(confirm) != Socket::Done)
          throw MyException("Error 13: init data don't send player!!!");
        if(other->_socket->send(confirmOther) != Socket::Done)
          throw MyException("Error 13: init data don't send player!!!");
        break;
      }
  }
}