/*
*	Copyright (C) 2021 Anders Wennmo
*	This file is part of forestadventure which is released under MIT license.
*	See file LICENSE for full license details.
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace FA {

class Game
{
public:
	Game();
	void GameLoop();

public:
	static const sf::Vector2u screen;
	static const sf::Vector2u centerScreen;

private:
	sf::RenderWindow window_;
	sf::View view_;
	sf::RectangleShape rectShape_;
	sf::Texture texture_;
};

} // namespace FA