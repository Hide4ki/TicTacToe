#pragma once

#include <SFML/Network.hpp>
#include "MessageType.hpp"
#include "MatchState.hpp"

using namespace sf;

Packet &operator<<(Packet&, const MessageType&);
Packet &operator>>(Packet&, MessageType&);

Packet &operator<<(Packet&, const MatchState&);
Packet &operator>>(Packet&, MatchState&);