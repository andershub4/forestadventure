/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/IsKeyReleasedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/MessageBus.h"
#include "Resource/TextureManager.h"

namespace FA {

namespace Entity {

BasicEntity::BasicEntity(EntityId id, MessageBus& messageBus, const TextureManager& textureManager)
    : id_(id)
    , messageBus_(messageBus)
    , textureManager_(textureManager)
    , stateMachine_(stateData_)
{}

BasicEntity::~BasicEntity() = default;

void BasicEntity::Update(float deltaTime)
{
    stateMachine_.Update(deltaTime);
}

void BasicEntity::LateUpdate()
{
    stateMachine_.LateUpdate();
}

void BasicEntity::DrawTo(sf::RenderTarget& renderTarget)
{
    stateMachine_.DrawTo(renderTarget);
}

void BasicEntity::OnMessage(std::shared_ptr<Message> msg)
{
    if (enableInput_) {
        HandleMessage(msg);
    }
}

sf::Vector2f BasicEntity::GetPosition() const
{
    return stateData_.transform_.GetPosition();
}

void BasicEntity::HandleMessage(std::shared_ptr<Message> msg)
{
    if (msg->GetMessageType() == MessageType::IsKeyPressed) {
        auto m = std::dynamic_pointer_cast<IsKeyPressedMessage>(msg);
        auto key = m->GetKey();
        OnIsKeyPressed(key);
    }
    else if (msg->GetMessageType() == MessageType::IsKeyReleased) {
        auto m = std::dynamic_pointer_cast<IsKeyReleasedMessage>(msg);
        auto key = m->GetKey();
        OnIsKeyReleased(key);
    }
    else if (msg->GetMessageType() == MessageType::KeyPressed) {
        auto m = std::dynamic_pointer_cast<KeyPressedMessage>(msg);
        auto key = m->GetKey();
        OnKeyPressed(key);
    }
}

void BasicEntity::InitStateData(const Configuration& configuration, const AnimationComponent& animation)
{
    stateMachine_.OnInitStateData(configuration, animation);
}

void BasicEntity::StartMove(MoveDirection moveDir, FaceDirection faceDir)
{
    stateMachine_.OnStartMove(moveDir, faceDir);
}

void BasicEntity::StopMove()
{
    stateMachine_.OnStopMove();
}

void BasicEntity::Attack()
{
    stateMachine_.OnAttack();
}

void BasicEntity::AttackWeapon()
{
    stateMachine_.OnAttackWeapon();
}

void BasicEntity::Subscribe(const std::vector<MessageType>& messageTypes)
{
    messageBus_.AddSubscriber(Name(), messageTypes, [this](std::shared_ptr<Message> message) { OnMessage(message); });
}

void BasicEntity::Unsubscribe(const std::vector<MessageType>& messageTypes)
{
    messageBus_.RemoveSubscriber(Name(), messageTypes);
}

const sf::Texture* BasicEntity::GetTexture(const std::string& name) const
{
    return textureManager_.Get(name);
}

}  // namespace Entity

}  // namespace FA
