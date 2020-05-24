#include "GUI.hpp"

void GUI::CreateConnectWindow()
{
  Vector2i centerWindow((VideoMode::getDesktopMode().width / 2) - 445, (VideoMode::getDesktopMode().height / 2) - 480);

	_window->create(VideoMode(900, 900), "Connect", Style::Titlebar | Style::Close);
	_window->setPosition(centerWindow);

	_window->setKeyRepeatEnabled(true);
}