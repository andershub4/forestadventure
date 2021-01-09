/*
*	Copyright (C) 2021 Anders Wennmo
*	This file is part of forestadventure which is released under MIT license.
*	See file LICENSE for full license details.
*/

#include "Game.h"

#include <iostream>

#include <SFML/Window/Event.hpp>

namespace FA
{

const sf::Vector2u Game::screen = { 1280, 780 };
const sf::Vector2u Game::centerScreen = { Game::screen.x / 2, Game::screen.y / 2 };

Game::Game()
	: rectShape_(sf::Vector2f(1.0, 1.0))
{
	std::cout << "Create main window" << std::endl;
#ifdef _DEBUG
	window_.create(sf::VideoMode(screen.x, screen.y), "ForestAdventure");
#else
	window_.create(sf::VideoMode::getDesktopMode(), "ForestAdventure", sf::Style::Fullscreen);
	view_.reset(sf::FloatRect(0.0, 0.0, static_cast<float>(screen.x), static_cast<float>(screen.y)));
	window_.setView(view_);
#endif
	window_.setFramerateLimit(120);
	rectShape_.setPosition(sf::Vector2f(static_cast<float>(centerScreen.x), static_cast<float>(centerScreen.y)));

	const sf::Texture& texture = textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/idle/hero-idle-front.png");
	rectShape_.setTexture(&texture);
	constexpr int size = 64;
	rectShape_.setSize({ static_cast<float>(size), static_cast<float>(size) });
}


void Game::GameLoop()
{
	std::cout << "Enter GameLoop" << std::endl;

	while (window_.isOpen()) {
		sf::Event event;
		while (window_.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window_.close();
		}

		window_.draw(rectShape_);
		window_.display();
	}

	std::cout << "Exit GameLoop" << std::endl;
}

} // namespace FA