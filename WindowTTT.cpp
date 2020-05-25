#include "WindowTTT.hpp"

WindowTTT::WindowTTT(WindowTTTBuilder *iBuilder) : _window(VideoMode(iBuilder->_size.x, iBuilder->_size.y), iBuilder->_winName, iBuilder->_style), _itextb(iBuilder->_itextb), _otextb(iBuilder->_otextb), _chb(iBuilder->_chb)
{
  _button = iBuilder->_button;
  _field = iBuilder->_field;
  
  delete iBuilder;
}

void WindowTTT::WindowHandler()
{
  while(_window.isOpen())
  {
    Event e;
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
              _window.close();
            }
          if(_field != 0)
            if(_field->isMouseOver(_window))
            {
              _field->OnClick();
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
  delete this;
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