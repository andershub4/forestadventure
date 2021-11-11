/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Modes/UninitializedMode.h"
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
    , stateController_(entityService_)
{
    stateController_.SetOnCreateCB([this](EntityService& entityService, const PropertyData& propertyData) {
        OnAddProperties(entityService, propertyData);
        OnAddModes(stateController_);
        OnAddShape(entityService, *entityService.GetShape());
        entityService.GetShape()->Awake();
    });
}

BasicEntity::~BasicEntity() = default;

void BasicEntity::Create(const PropertyData& data)
{
    stateController_.Create(data);
}

void BasicEntity::Update(float deltaTime)
{
    stateController_.Update(deltaTime);
}

void BasicEntity::LateUpdate()
{
    stateController_.LateUpdate();
}

void BasicEntity::DrawTo(sf::RenderTarget& renderTarget)
{
    stateController_.DrawTo(renderTarget);
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
        stateController_.HandleIsKeyPressed(key);
    }
    else if (msg->GetMessageType() == MessageType::IsKeyReleased) {
        auto m = std::dynamic_pointer_cast<IsKeyReleasedMessage>(msg);
        auto key = m->GetKey();
        stateController_.HandleIsKeyReleased(key);
    }
    else if (msg->GetMessageType() == MessageType::KeyPressed) {
        auto m = std::dynamic_pointer_cast<KeyPressedMessage>(msg);
        auto key = m->GetKey();
        stateController_.HandleKeyPressed(key);
    }
}

void BasicEntity::Init()
{
    stateController_.OnInit();
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
