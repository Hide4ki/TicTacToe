#include "MyException.hpp"

MyException::MyException(const string err):_error_text(err)
{
  
}

void MyException::what() const
{
  Font font;
  if (!font.loadFromFile("arial.ttf"))
    cout << "Font not found!" << endl << "ERROR: 69!->&" << _error_text << endl;  
  else
  { 
    WindowTTT *werror = new WindowTTT((new WindowTTTBuilder())->\
    SetWinName("Error")->SetStyle(Style::Close)->\
    AddOutputTextBox((new BorderDecor(new BackGroundDecor(new OutputBox({30,25}, {390,50}, font, Color::Black, 20),Color::White), 3, Color::Red))->SetValue(_error_text))->\
    AddButton(new HeaderDecor(new BorderDecor(new Button({25,80},{395,115}, Color::White), 3, Color::Red),"Ok", font, {0,0}, Color::Black, 20, true, true))->\
    SetWinSize({420,125})->SetTypeWin(WinType::Error));

    werror->WindowHandler();
    delete werror;
  }
}