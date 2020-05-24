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
  if (tmp <= static_cast<int>(MessageType::Error) && tmp >= static_cast<int>(MessageType::Move))
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
  if (tmp < static_cast<int>(Error::LastError) && tmp >= static_cast<int>(Error::None))
    e = static_cast<Error>(tmp);
  else
    ;//todo
  return p;
}