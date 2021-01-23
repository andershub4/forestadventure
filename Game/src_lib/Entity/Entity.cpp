/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Entity.h"

#include "Animation/Animation.h"
#include "Constant/Screen.h"
#include "Game/Layer.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/IsKeyReleasedMessage.h"
#include "Message/MessageBus.h"

namespace FA {

Entity::Entity(MessageBus& messageBus, const AnimationFactory& animationFactory)
    : messageBus_(messageBus)
    , animationFactory_(animationFactory)
    , movement_(&rectShape_, 120)
    , stateMachine_(*this, FaceDirection::Down, MoveDirection::Down)
{
    messageBus_.AddSubscriber("entity", {MessageType::IsKeyPressed, MessageType::IsKeyReleased},
                              [this](std::shared_ptr<Message> message) { OnMessage(message); });
    rectShape_.setPosition(constant::Screen::centerX_f, constant::Screen::centerY_f);
    constexpr int size = 64;
    rectShape_.setSize({static_cast<float>(size), static_cast<float>(size)});
}

Entity::~Entity() = default;

void Entity::Update(float deltaTime)
{
    movement_.Update(deltaTime);
    if (animation_) animation_->Update(deltaTime);
}

void Entity::DrawTo(Layer& layer)
{
    layer.Draw(rectShape_);
}

void Entity::OnMessage(std::shared_ptr<Message> msg)
{
    // TODO: Implement a mechanism to disable handling of IsKeyPressed when game is paused.
    if (msg->GetMessageType() == MessageType::IsKeyPressed) {
        auto m = std::dynamic_pointer_cast<IsKeyPressedMessage>(msg);
        auto key = m->GetKey();
        OnIsKeyPressed(key);
    }
    else if (msg->GetMessageType() == MessageType::IsKeyReleased) {
        stateMachine_.OnStopMove();
    }
}

void Entity::StartMove(MoveDirection moveDir, FaceDirection faceDir, FrameType frameType)
{
    movement_.SetDirection(moveDir);
    animation_ = animationFactory_.Create(frameType, faceDir, rectShape_);
    animation_->Start();
}

void Entity::StopMove(MoveDirection moveDir, FaceDirection faceDir)
{
    movement_.Stop();
}

void Entity::StartIdle(MoveDirection moveDir, FaceDirection faceDir, FrameType frameType)
{
    animation_ = animationFactory_.Create(frameType, faceDir, rectShape_);
}

void Entity::OnIsKeyPressed(Keyboard::Key key)
{
    if (key == Keyboard::Key::Right) {
        stateMachine_.OnStartMove(MoveDirection::Right, FaceDirection::Right);
    }
    else if (key == Keyboard::Key::Left) {
        stateMachine_.OnStartMove(MoveDirection::Left, FaceDirection::Left);
    }
    else if (key == Keyboard::Key::Up) {
        stateMachine_.OnStartMove(MoveDirection::Up, FaceDirection::Up);
    }
    else if (key == Keyboard::Key::Down) {
        stateMachine_.OnStartMove(MoveDirection::Down, FaceDirection::Down);
    }
}

}  // namespace FA
