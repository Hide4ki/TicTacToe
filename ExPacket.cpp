#include "ExPacket.hpp"

using namespace sf;

Packet &operator<<(Packet &p, const MessageType &mt)
{
  p << static_cast<int>(mt);
  return p;
}

Packet &operator>>(Packet &p, MessageType &mt)
{
  int tmp;
  p >> tmp;
  if (tmp >= static_cast<int>(MessageType::Move) && tmp <= static_cast<int>(MessageType::Error))
    mt = static_cast<MessageType>(tmp);
  else
    ;//todo
  return p;
}

Packet &operator<<(Packet &p, const Error &e)
{
  p << static_cast<int>(e);
  return p;
}

Packet &operator>>(Packet &p, Error &e)
{
  int tmp;
  p >> tmp;
  if (tmp >= static_cast<int>(Error::None) && tmp < static_cast<int>(Error::LastError))
    e = static_cast<Error>(tmp);
  else
    ;//todo
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
    ;//todo
  return p;
}