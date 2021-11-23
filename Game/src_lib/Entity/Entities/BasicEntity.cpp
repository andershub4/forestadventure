/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Shapes/Shape.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/IsKeyReleasedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

BasicEntity::BasicEntity(EntityId id, EntityType entityType, CameraManager& cameraManager,
                         const AnimationDb& animationDb, MessageBus& messageBus)
    : id_(id)
    , messageBus_(messageBus)
    , entityService_(entityType, cameraManager, animationDb)
    , modeController_(entityService_)
{
    modeController_.SetOnCreateCB([this](EntityService& entityService, const PropertyData& propertyData) {
        DefineProperties(entityService, propertyData);
        DefineModes(modeController_);
        DefineShape(entityService, *entityService.GetShape());
        entityService.GetShape()->Awake();
    });
}

BasicEntity::~BasicEntity() = default;

void BasicEntity::Create(const PropertyData& data)
{
    modeController_.Create(data);
}

void BasicEntity::Init()
{
    modeController_.Init();
}

void BasicEntity::Update(float deltaTime)
{
    modeController_.Update(deltaTime);
}

void BasicEntity::DrawTo(sf::RenderTarget& renderTarget)
{
    modeController_.DrawTo(renderTarget);
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
        HandleIsKeyPressed(key);
    }
    else if (msg->GetMessageType() == MessageType::IsKeyReleased) {
        auto m = std::dynamic_pointer_cast<IsKeyReleasedMessage>(msg);
        auto key = m->GetKey();
        HandleIsKeyReleased(key);
    }
    else if (msg->GetMessageType() == MessageType::KeyPressed) {
        auto m = std::dynamic_pointer_cast<KeyPressedMessage>(msg);
        auto key = m->GetKey();
        HandleKeyPressed(key);
    }
}

void BasicEntity::Subscribe(const std::vector<MessageType>& messageTypes)
{
    messageBus_.AddSubscriber(Name(), messageTypes, [this](std::shared_ptr<Message> message) { OnMessage(message); });
}

void BasicEntity::Unsubscribe(const std::vector<MessageType>& messageTypes)
{
    messageBus_.RemoveSubscriber(Name(), messageTypes);
}

void BasicEntity::HandleEvent(std::shared_ptr<BasicEvent> event)
{
    modeController_.HandleEvent(event);
}

}  // namespace Entity

}  // namespace FA
