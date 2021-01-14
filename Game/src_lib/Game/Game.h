/*
*	Copyright (C) 2021 Anders Wennmo
*	This file is part of forestadventure which is released under MIT license.
*	See file LICENSE for full license details.
*/

#pragma once

#include <memory>
#include <iosfwd>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#ifdef _DEBUG
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#endif

#include "Misc/TextureManager.h"
#include "Animation/AnimationHandler.h"

namespace FA {

class Game
{
public:
	Game();
	~Game();
	void GameLoop();

public:
	static const sf::Vector2u screen;
	static const sf::Vector2u centerScreen;

private:
	std::unique_ptr<std::ofstream> sfmlLogStream_;
	sf::RenderWindow window_;
	sf::View view_;
	sf::RectangleShape dotShape_;
	sf::RectangleShape rectShape_;
	TextureManager textureManager_;
	AnimationHandler animationHandler_;
#ifdef _DEBUG
	sf::Font font_;
	sf::Text sceneText_;
#endif

private:
	void RedirectSfmlLogEntries();
};

} // namespace FA