#include "ExPacket.hpp"

#include "MyException.hpp"


Packet &operator<<(Packet &p, const MessageType &mt)
{
  p << static_cast<int>(mt);
  return p;
}

Packet &operator>>(Packet &p, MessageType &mt)
{
  int tmp;
  p >> tmp;
  if (tmp >= static_cast<int>(MessageType::Move) && tmp <= static_cast<int>(MessageType::Connect))
    mt = static_cast<MessageType>(tmp);
  else
    throw MyException("Error 3: broken packet with message type!!");
  return p;
}

Packet &operator<<(Packet &p, const MatchState &e)
{
  p << static_cast<int>(e);
  return p;
}

Packet &operator>>(Packet &p, MatchState &e)
{
  int tmp;
  p >> tmp;
  if (tmp >= static_cast<int>(MatchState::GO) && tmp <= static_cast<int>(MatchState::Tie))
    e = static_cast<MatchState>(tmp);
  else
    throw MyException("Error 4: broken packet with macth state!!");
  return p;
}