/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "Animation/AnimationHandler.h"
#include "Enum/KeyboardKey.h"

namespace FA {

class MessageBus;
class Message;
class TextureManager;

class Entity
{
public:
    Entity(MessageBus& messageBus, TextureManager& textureManager);

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    void OnMessage(std::shared_ptr<Message> msg);

private:
    MessageBus& messageBus_;
    AnimationHandler animationHandler_;
    sf::RectangleShape rectShape_;
    AnimationHandler::FrameType frameType_ = AnimationHandler::FrameType::Move;
    AnimationHandler::FaceDir dir_ = AnimationHandler::FaceDir::Up;

private:
    void InitAnimation(TextureManager& textureManager);
    void SetFrameType(AnimationHandler::FrameType frameType);
    void SetFaceDir(AnimationHandler::FaceDir dir);
    void OnIsKeyPressed(Keyboard::Key key);
};

}  // namespace FA
