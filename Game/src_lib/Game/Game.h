/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <iosfwd>
#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#ifdef _DEBUG
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#endif

#include "Animation/AnimationHandler.h"
#include "Message/MessageBus.h"
#include "Misc/TextureManager.h"

namespace FA {

class Entity
{
public:
    Entity()
        : animationHandler_(0.1f)
    {}
    AnimationHandler::FrameType frameType_ = AnimationHandler::FrameType::Move;
    AnimationHandler::FaceDir dir_ = AnimationHandler::FaceDir::Up;
    sf::RectangleShape rectShape_;

    void Update(float deltaTime) { animationHandler_.Update(deltaTime); }
    void Draw(sf::RenderWindow& window) { window.draw(rectShape_); }
    void RegisterAnimationInfo(AnimationHandler::FrameType frameType, AnimationHandler::FaceDir dir,
                               const sf::Texture* texture, const std::vector<sf::IntRect>& frames,
                               unsigned int defaultFrame, bool mirrorX = false)
    {
        animationHandler_.RegisterAnimationInfo(frameType, dir, texture, frames, defaultFrame, mirrorX);
    }
    void SetAnimation() { animationHandler_.SetAnimation(frameType_, dir_, rectShape_, true); }

private:
    AnimationHandler animationHandler_;
};

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
    MessageBus messageBus_;
    std::unique_ptr<std::ofstream> sfmlLogStream_;
    sf::RenderWindow window_;
    sf::View view_;
    Entity entity_;
    TextureManager textureManager_;
#ifdef _DEBUG
    sf::RectangleShape dotShape_;
    sf::Font font_;
    sf::Text sceneText_;
#endif

private:
    void RedirectSfmlLogEntries();
    void OnMessage(std::shared_ptr<Message> message);
    void InitWindow();
#ifdef _DEBUG
    void InitDebugSceneGraphics();
#endif
    void InitAnimations();
};

}  // namespace FA
