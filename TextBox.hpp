#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "PartGUI.hpp"

using namespace std;
using namespace sf;


class TextBox : public PartGUI {
public:
	TextBox(Vector2f, Uint32, Uint32);
  TextBox() = delete;
  TextBox(const TextBox&) = delete;
  TextBox(TextBox&&) = delete;
  virtual ~TextBox() = default;

	void SetFont(Font&);
	void SetPosition(Vector2f) override;
  void SetColor(Color);
  void SetSelected(bool);
	string GetText();
	void DrawTo(RenderWindow &) override;
  void Reseive(Event);
  void SetLimit(Uint32);
  bool isMouseOver(RenderWindow &) override;
  void SetHeader(string);
private:
  void DeleteLast();
	void SpecRead(Uint32);
  RectangleShape _border;
  Text _textbox;
  Text _header;
  Uint32 _limit;
  bool _isSelected;
	ostringstream _text;
};