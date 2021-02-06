/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Screen.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/IsKeyReleasedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

BasicEntity::BasicEntity(MessageBus& messageBus, const AnimationFactory& animationFactory)
    : messageBus_(messageBus)
    , stateMachine_(&rectShape_, FaceDirection::Down, MoveDirection::Down, animationFactory, 120.0)
{
    messageBus_.AddSubscriber("entity",
                              {MessageType::IsKeyPressed, MessageType::IsKeyReleased, MessageType::KeyPressed},
                              [this](std::shared_ptr<Message> message) { OnMessage(message); });
    rectShape_.setPosition(constant::Screen::centerX_f, constant::Screen::centerY_f);
    constexpr int size = 64;
    rectShape_.setSize({static_cast<float>(size), static_cast<float>(size)});
}

BasicEntity::~BasicEntity()
{
    messageBus_.RemoveSubscriber("entity",
                                 {MessageType::IsKeyPressed, MessageType::IsKeyReleased, MessageType::KeyPressed});
}

void BasicEntity::Update(float deltaTime)
{
    stateMachine_.Update(deltaTime);
}

void BasicEntity::DrawTo(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(rectShape_);
}

void BasicEntity::OnMessage(std::shared_ptr<Message> msg)
{
    if (processMessages_) {
        HandleMessage(msg);
    }
}

sf::Vector2f BasicEntity::GetPosition() const
{
    return rectShape_.getPosition();
}

void BasicEntity::HandleMessage(std::shared_ptr<Message> msg)
{
    if (msg->GetMessageType() == MessageType::IsKeyPressed) {
        auto m = std::dynamic_pointer_cast<IsKeyPressedMessage>(msg);
        auto key = m->GetKey();
        OnIsKeyPressed(key);
    }
    else if (msg->GetMessageType() == MessageType::IsKeyReleased) {
        stateMachine_.OnStopMove();
    }
    else if (msg->GetMessageType() == MessageType::KeyPressed) {
        auto m = std::dynamic_pointer_cast<KeyPressedMessage>(msg);
        auto key = m->GetKey();
        if (key == Keyboard::Key::RControl) {
            stateMachine_.OnAttack();
        }
        else if (key == Keyboard::Key::Space) {
            stateMachine_.OnAttackWeapon();
        }
    }
}

void BasicEntity::OnIsKeyPressed(Keyboard::Key key)
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

}  // namespace Entity

}  // namespace FA
