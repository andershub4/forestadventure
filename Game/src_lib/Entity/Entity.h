/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "Animation/AnimationFactory.h"
#include "EntityState/EntityStateMachine.h"
#include "Enum/KeyboardKey.h"
#include "Movement/Movement.h"

namespace FA {

class MessageBus;
class Message;
class Layer;
class Animation;

class Entity
{
public:
    Entity(MessageBus& messageBus, const AnimationFactory& animationFactory);
    ~Entity();

    void Update(float deltaTime);
    void DrawTo(Layer& layer);
    void OnMessage(std::shared_ptr<Message> msg);

    void StartMove(MoveDirection moveDir, FaceDirection faceDir, FrameType frameType);
    void StopMove(MoveDirection moveDir, FaceDirection faceDir);
    void StartIdle(MoveDirection moveDir, FaceDirection faceDir, FrameType frameType);
    void StopIdle(MoveDirection moveDir, FaceDirection faceDir) {}

private:
    MessageBus& messageBus_;
    AnimationFactory animationFactory_;
    std::unique_ptr<Animation> animation_ = nullptr;
    Movement movement_;
    sf::RectangleShape rectShape_;
    EntityStateMachine stateMachine_;

private:
    void OnIsKeyPressed(Keyboard::Key key);
};

}  // namespace FA
