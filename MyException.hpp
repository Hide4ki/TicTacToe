#pragma once
#include <string>
#include "WindowTTT.hpp"
#include <iostream>

using namespace std;

class MyException
{
public:
  
  MyException(const string);
  void what() const;
private:
  const string _error_text;
};