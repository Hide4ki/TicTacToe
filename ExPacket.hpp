#pragma once
#include <SFML/Network.hpp>
#include "MessageType.hpp"
#include "Error.hpp"

using namespace sf;

Packet &operator<<(Packet&, const MessageType&);
Packet &operator>>(Packet&, MessageType&);

Packet &operator<<(Packet&, const Error&);
Packet &operator>>(Packet&, Error&);