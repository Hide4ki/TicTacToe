#include "WindowTTT.hpp"

WindowTTT::WindowTTT(WindowTTTBuilder *iBuilder) : _window(VideoMode(iBuilder->_size.x, iBuilder->_size.y), iBuilder->_winName, iBuilder->_style), _itextb(iBuilder->_itextb), _otextb(iBuilder->_otextb), _chb(iBuilder->_chb), _socket(iBuilder->_socket), _message(iBuilder->_message), _type(iBuilder->_type)
{
  _button = iBuilder->_button;
  _field = iBuilder->_field;
  
  delete iBuilder;
}

void WindowTTT::WindowHandler()
{
  bool lock = false;
  bool side;
  bool gameEnd = false;
  Event e;
  while(_window.pollEvent(e));
  _window.clear();
  for(auto it : _itextb)
    it->DrawTo(_window);
  for(auto it : _otextb)
    it->DrawTo(_window);
  for(auto it : _chb)
    it->DrawTo(_window);
  if(_button != 0)
    _button->DrawTo(_window);
  if(_field != 0)
    _field->DrawTo(_window);
  _window.display();

  if (_field != 0)
  {
    istringstream ss(_field->GetValue());
    Uint32 tmp;
    ss >> tmp >> tmp >> side;
  }
  
  if (_field != 0 && side)
    lock = true;

  while(_window.isOpen())
  {
    Event e;
    if(lock)
    {
      Packet packet;
      string s;
      MatchState ms;
      Uint32 dir;
      if(_socket->receive(packet) == Socket::Done)
      {
        packet >> ms;
        packet >> s;
      }
      switch(ms)
      {
        case MatchState::GO:
        {
          _field->SetValue(s);
        }
        break;
        case MatchState::WinO:
        case MatchState::WinX:
          {
            _field->SetValue(s);
            gameEnd = true;
          }
        break;
        case MatchState::Tie:
          gameEnd = true;
        break;
      }
      lock = false;
    }
    while(_window.pollEvent(e))
    {
      switch(e.type)
      {
        case Event::Closed:
          _window.close();
        break;
        case Event::TextEntered:
          for(auto it : _itextb)
            it->AddCh(e);
        break;
        case Event::MouseButtonPressed:
          for(auto it : _itextb)
            if(it->isMouseOver(_window))
              it->OnClick();
          for(auto it : _otextb)
            if(it->isMouseOver(_window))
              it->OnClick();
          for(auto it : _chb)
            if(it->isMouseOver(_window))
              it->OnClick();
          if(_button != 0)
            if(_button->isMouseOver(_window))
            {
              switch(_type)
              {
                case WinType::Connect:
                {
                  Uint32 port;
                  istringstream ss(_itextb[1]->GetValue());
                  ss >> port;
                  if(_socket->connect(_itextb[0]->GetValue(), port) != Socket::Done)
                  {
                    
                  }
                  Packet packet;
                  if(packet << _message << "Hello server!!")
                    _socket->send(packet);
                }
                break;
                case WinType::Config:
                {
                  string x = _itextb[0]->GetValue();
                  string y = _itextb[1]->GetValue();
                  string c0 = _chb[0]->GetValue();
                  string c1 = _chb[1]->GetValue();
                  string c2 = _chb[2]->GetValue();
                  string c3 = _chb[3]->GetValue();
                  Packet packet;
                  if(packet << _message << c0 << c1 << c2 << c3 << x << y)
                  {
                    int tmp = packet.getDataSize();
                    _socket->send(packet);
                  }
                }
                break;
              }
              _window.close();
            }
          if(_field != 0 && !gameEnd)
            if(_field->isMouseOver(_window))
            {
              _field->OnClick();
              Packet packet;
              string tmp = _field->GetValue();
              istringstream ss(tmp);
              Int32 x;
              Int32 y; 
              ss >> x >> y;
              if(x != -1 && y != -1)
              {
                packet << _message <<_field->GetValue();
                _socket->send(packet);
                lock = true;
              }
            }
        break;
      }
    }
    _window.clear();
    for(auto it : _itextb)
      it->DrawTo(_window);
    for(auto it : _otextb)
      it->DrawTo(_window);
    for(auto it : _chb)
      it->DrawTo(_window);
    if(_button != 0)
      _button->DrawTo(_window);
    if(_field != 0)
      _field->DrawTo(_window);
    _window.display();
  }
}

WindowTTT::~WindowTTT()
{
  for(auto it : _itextb)
    delete it;
  for(auto it : _otextb)
    delete it;
  for(auto it : _chb)
    delete it;
  if(_button != 0)
    delete _button;
  if(_field != 0)
    delete _field;
}