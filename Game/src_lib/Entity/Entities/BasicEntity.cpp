/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Behaviors/IdleBehavior.h"
#include "Entity/Behaviors/UninitializedBehavior.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/IsKeyReleasedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

BasicEntity::BasicEntity(EntityId id, EntityType entityType, CameraManager& cameraManager, MessageBus& messageBus)
    : id_(id)
    , messageBus_(messageBus)
    , entityService_(entityType, cameraManager)
    , stateMachine_(stateData_, entityService_)
{
    auto u = entityService_.AddBehavior<UninitializedBehavior>();
    u->SetOnCreateCB([this](EntityService& entityService, const PropertyData& propertyData) {
        OnCreate(entityService, propertyData);
    });
    entityService_.AddBehavior<IdleBehavior>();
}

BasicEntity::~BasicEntity() = default;

void BasicEntity::Create(const PropertyData& data)
{
    stateMachine_.Create(data);
}

void BasicEntity::Update(float deltaTime)
{
    stateMachine_.Update(deltaTime);
}

void BasicEntity::Awake()
{
    stateMachine_.Awake();
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

void BasicEntity::InitStateData(const AnimationDb& animationDb)
{
    stateMachine_.OnInitStateData(animationDb);
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

}  // namespace Entity

}  // namespace FA
