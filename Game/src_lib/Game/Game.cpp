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
	: dotShape_(sf::Vector2f(1.0, 1.0)), animationHandler_(0.1f)
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

#ifdef _DEBUG
	if (!font_.loadFromFile("assets/font/cello-sans/hinted-CelloSans-Medium.ttf"))	{
		std::cout << "Could not load hinted-CelloSans-Medium" << std::endl;
	}

	sceneText_.setFont(font_);
	sceneText_.setString("GamePlayScene");
	sceneText_.setCharacterSize(24);
	sceneText_.setFillColor(sf::Color::White);
	sf::Vector2f sceneTextPos(0.0f, 0.0f);
	sceneText_.setPosition(sceneTextPos);
#endif

	dotShape_.setPosition(sf::Vector2f(static_cast<float>(centerScreen.x), static_cast<float>(centerScreen.y)));
	rectShape_.setPosition(sf::Vector2f(static_cast<float>(centerScreen.x), static_cast<float>(centerScreen.y)));
	constexpr int size = 64;
	rectShape_.setSize({ static_cast<float>(size), static_cast<float>(size) });

	auto textureWalkSide = textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/walk/hero-walk-side.png");
	if (textureWalkSide != nullptr) {
		SpriteSheet spriteSheet("heroWalkSide", textureWalkSide, { 6, 1 });
		SpriteSheet::FrameData f = spriteSheet.Scan({ 0, 0 }, 6, 0);
		animationHandler_.RegisterAnimationInfo(AnimationHandler::FrameType::Move, AnimationHandler::FaceDir::Left,
			f.texture_, f.frames_, f.defaultFrame_, true);
		animationHandler_.RegisterAnimationInfo(AnimationHandler::FrameType::Move, AnimationHandler::FaceDir::Right,
			f.texture_, f.frames_, f.defaultFrame_);
	}
	auto textureWalkFront = textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/walk/hero-walk-front.png");
	if (textureWalkFront != nullptr) {
		SpriteSheet spriteSheet("heroWalkFront", textureWalkFront, { 6, 1 });
		SpriteSheet::FrameData f = spriteSheet.Scan({ 0, 0 }, 6, 0);
		animationHandler_.RegisterAnimationInfo(AnimationHandler::FrameType::Move, AnimationHandler::FaceDir::Down,
			f.texture_, f.frames_, f.defaultFrame_);
	}
	auto textureWalkBack = textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/walk/hero-back-walk.png");
	if (textureWalkBack != nullptr) {
		SpriteSheet spriteSheet("heroWalkBack", textureWalkBack, { 6, 1 });
		SpriteSheet::FrameData f = spriteSheet.Scan({ 0, 0 }, 6, 0);
		animationHandler_.RegisterAnimationInfo(AnimationHandler::FrameType::Move, AnimationHandler::FaceDir::Up,
			f.texture_, f.frames_, f.defaultFrame_);
	}

	auto textureAttackSide = textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/attack/hero-attack-side.png");
	if (textureAttackSide != nullptr) {
		SpriteSheet spriteSheet("heroAttackSide", textureAttackSide, { 3, 1 });
		SpriteSheet::FrameData f = spriteSheet.Scan({ 0, 0 }, 3, 0);
		animationHandler_.RegisterAnimationInfo(AnimationHandler::FrameType::Attack, AnimationHandler::FaceDir::Left,
			f.texture_, f.frames_, f.defaultFrame_, true);
		animationHandler_.RegisterAnimationInfo(AnimationHandler::FrameType::Attack, AnimationHandler::FaceDir::Right,
			f.texture_, f.frames_, f.defaultFrame_);
	}
	auto textureAttackFront = textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/attack/hero-attack-front.png");
	if (textureAttackFront != nullptr) {
		SpriteSheet spriteSheet("heroAttackFront", textureAttackFront, { 3, 1 });
		SpriteSheet::FrameData f = spriteSheet.Scan({ 0, 0 }, 3, 0);
		animationHandler_.RegisterAnimationInfo(AnimationHandler::FrameType::Attack, AnimationHandler::FaceDir::Down,
			f.texture_, f.frames_, f.defaultFrame_);
	}
	auto textureAttackBack = textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/attack/hero-attack-back.png");
	if (textureAttackBack != nullptr) {
		SpriteSheet spriteSheet("heroAttackBack", textureAttackBack, { 3, 1 });
		SpriteSheet::FrameData f = spriteSheet.Scan({ 0, 0 }, 3, 0);
		animationHandler_.RegisterAnimationInfo(AnimationHandler::FrameType::Attack, AnimationHandler::FaceDir::Up,
			f.texture_, f.frames_, f.defaultFrame_);
	}

	auto textureIdleSide = textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/idle/hero-idle-side.png");
	if (textureIdleSide != nullptr) {
		SpriteSheet spriteSheet("heroIdleSide", textureIdleSide, { 1, 1 });
		SpriteSheet::FrameData f = spriteSheet.Scan({ 0, 0 }, 1, 0);
		animationHandler_.RegisterAnimationInfo(AnimationHandler::FrameType::Idle, AnimationHandler::FaceDir::Left,
			f.texture_, f.frames_, f.defaultFrame_, true);
		animationHandler_.RegisterAnimationInfo(AnimationHandler::FrameType::Idle, AnimationHandler::FaceDir::Right,
			f.texture_, f.frames_, f.defaultFrame_);
	}
	auto textureIdleFront = textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/idle/hero-idle-front.png");
	if (textureIdleFront != nullptr) {
		SpriteSheet spriteSheet("heroIdleFront", textureIdleFront, { 1, 1 });
		SpriteSheet::FrameData f = spriteSheet.Scan({ 0, 0 }, 1, 0);
		animationHandler_.RegisterAnimationInfo(AnimationHandler::FrameType::Idle, AnimationHandler::FaceDir::Down,
			f.texture_, f.frames_, f.defaultFrame_);
	}
	auto textureIdleBack = textureManager_.GetTexture("assets/tiny-RPG-forest-files/PNG/spritesheets/hero/idle/hero-idle-back.png");
	if (textureIdleBack != nullptr) {
		SpriteSheet spriteSheet("heroIdleBack", textureIdleBack, { 1, 1 });
		SpriteSheet::FrameData f = spriteSheet.Scan({ 0, 0 }, 1, 0);
		animationHandler_.RegisterAnimationInfo(AnimationHandler::FrameType::Idle, AnimationHandler::FaceDir::Up,
			f.texture_, f.frames_, f.defaultFrame_);
	}
}


void Game::GameLoop()
{
	std::cout << "Enter GameLoop" << std::endl;
	sf::Clock clock;

	AnimationHandler::FrameType frameType = AnimationHandler::FrameType::Move;
	AnimationHandler::FaceDir dir = AnimationHandler::FaceDir::Up;
	bool setAnimation = false;
	animationHandler_.SetAnimation(frameType, dir, rectShape_, true);

	while (window_.isOpen()) {
		sf::Time elapsed = clock.restart();
		float deltaTime = elapsed.asSeconds();

		sf::Event event;
		while (window_.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window_.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Right) {
					dir = AnimationHandler::FaceDir::Right;
					setAnimation = true;
				}
				else if (event.key.code == sf::Keyboard::Left) {
					dir = AnimationHandler::FaceDir::Left;
					setAnimation = true;
				}
				else if (event.key.code == sf::Keyboard::Up) {
					dir = AnimationHandler::FaceDir::Up;
					setAnimation = true;
				}
				else if (event.key.code == sf::Keyboard::Down) {
					dir = AnimationHandler::FaceDir::Down;
					setAnimation = true;
				}
				else if (event.key.code == sf::Keyboard::Num1) {
					frameType = AnimationHandler::FrameType::Idle;
					setAnimation = true;
				}
				else if (event.key.code == sf::Keyboard::Num2) {
					frameType = AnimationHandler::FrameType::Move;
					setAnimation = true;
				}
				else if (event.key.code == sf::Keyboard::Num3) {
					frameType = AnimationHandler::FrameType::Attack;
					setAnimation = true;
				}
			}
		}

		if (setAnimation) {
			animationHandler_.SetAnimation(frameType, dir, rectShape_, true);
			setAnimation = false;
		}

		animationHandler_.Update(deltaTime);

		window_.clear();
#ifdef _DEBUG
		window_.draw(sceneText_);
#endif
		window_.draw(rectShape_);
		window_.draw(dotShape_);
		window_.display();
	}

	std::cout << "Exit GameLoop" << std::endl;
}

} // namespace FA