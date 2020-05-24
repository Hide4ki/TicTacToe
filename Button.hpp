#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "PartGUI.hpp"
#include "TextBox.hpp"

using namespace std;
using namespace sf;

class Button : public PartGUI {
public:
	Button(Vector2f, Uint32, Uint32);
	void SetFont(Font &);
  void SetText(string);
	void SetBackColor(Color);
	void SetTextColor(Color);
	void SetPosition(Vector2f);
  void SetTextSize(Uint32);
	void DrawTo(RenderWindow &);
  void AddBox(TextBox*);
private:
	RectangleShape _button;
	Text _text;
  vector<TextBox *> _linkBoxs;
};