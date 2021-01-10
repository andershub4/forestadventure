/*
*	Copyright (C) 2021 Anders Wennmo
*	This file is part of forestadventure which is released under MIT license.
*	See file LICENSE for full license details.
*/

#include "Game.h"

#include <iostream>

#include <SFML/Window/Event.hpp>

#include "Sprite/SpriteSheet.h"

namespace FA
{

const sf::Vector2u Game::screen = { 1280, 780 };
const sf::Vector2u Game::centerScreen = { Game::screen.x / 2, Game::screen.y / 2 };

Game::Game()
	: dotShape_(sf::Vector2f(1.0, 1.0)), animationGroup_(0.1f)
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
	dotShape_.setPosition(sf::Vector2f(static_cast<float>(centerScreen.x), static_cast<float>(centerScreen.y)));
	rectShape_.setPosition(sf::Vector2f(static_cast<float>(centerScreen.x), static_cast<float>(centerScreen.y)));
	constexpr int size = 64;
	rectShape_.setSize({ static_cast<float>(size), static_cast<float>(size) });

	auto texture = textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/walk/hero-walk-front.png");
	if (texture != nullptr) {
		SpriteSheet spriteSheet("heroWalkFront", texture, { 6, 1 });
		SpriteSheet::FrameData f = spriteSheet.Scan({ 0, 0 }, 6, 0);
		animationGroup_.AddAnimation(AnimationGroup::Dir::Down, f.texture_, f.frames_, f.defaultFrame_);
	}
}


void Game::GameLoop()
{
	std::cout << "Enter GameLoop" << std::endl;
	sf::Clock clock;

	auto animation = animationGroup_.GetAnimation(AnimationGroup::Dir::Down);
	if (animation) {
		animation->ApplyTo(rectShape_);
		animation->Start();
	}

	while (window_.isOpen()) {
		sf::Time elapsed = clock.restart();
		float deltaTime = elapsed.asSeconds();

		sf::Event event;
		while (window_.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window_.close();
		}

		if (animation) animation->Update(deltaTime);

		window_.clear();
		window_.draw(rectShape_);
		window_.draw(dotShape_);
		window_.display();
	}

	std::cout << "Exit GameLoop" << std::endl;
}

} // namespace FA