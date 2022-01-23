/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Events/CreateEvent.h"
#include "Entity/Events/DestroyEvent.h"
#include "Entity/Events/InitEvent.h"
#include "Entity/Shape.h"
#include "Message/BroadcastMessage/IsKeyPressedMessage.h"
#include "Message/BroadcastMessage/IsKeyReleasedMessage.h"
#include "Message/BroadcastMessage/KeyPressedMessage.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

BasicEntity::BasicEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                         EntityManager& entityManager, MessageBus& messageBus)
    : id_(id)
    , messageBus_(messageBus)
    , entityService_(cameraManager, sheetManager, entityManager)
    , modeController_(entityService_)
{
    modeController_.RegisterCreateCB([this](std::shared_ptr<BasicEvent> event) { OnCreate(event); });
    modeController_.RegisterDestroyCB([this](std::shared_ptr<BasicEvent> event) { OnDestroy(event); });
}

BasicEntity::~BasicEntity() = default;

void BasicEntity::Create(const AttributeData& data)
{
    HandleEvent(std::make_shared<CreateEvent>(data));
}

void BasicEntity::Destroy()
{
    HandleEvent(std::make_shared<DestroyEvent>());
}

void BasicEntity::Init()
{
    HandleEvent(std::make_shared<InitEvent>());
    modeController_.HandleQueuedInitEvents();
}

void BasicEntity::Update(float deltaTime)
{
    modeController_.Update(deltaTime);

    PostUpdate(entityService_);
}

void BasicEntity::DrawTo(sf::RenderTarget& renderTarget)
{
    modeController_.DrawTo(renderTarget);
}

void BasicEntity::QueueInitEvents(std::shared_ptr<BasicEvent> event)
{
    modeController_.QueueInitEvents(event);
}

void BasicEntity::HandleEvent(std::shared_ptr<BasicEvent> event)
{
    modeController_.HandleEvent(event);
}

void BasicEntity::OnCreate(std::shared_ptr<BasicEvent> event)
{
    auto c = std::dynamic_pointer_cast<CreateEvent>(event);
    auto data = c->data_;
    for (const auto& data : Animations()) {
        entityService_.AddAnimation(Type(), data);
    }
    for (const auto& data : Images()) {
        entityService_.AddImage(Type(), data);
    }
    AddAttributes(entityService_, data);
    RegisterModes(modeController_, entityService_);

    entityService_.GetShape()->Register();
    Subscribe(Messages());
}

void BasicEntity::OnDestroy(std::shared_ptr<BasicEvent> event)
{
    Unsubscribe(Messages());
}

void BasicEntity::Subscribe(const std::vector<MessageType>& messageTypes)
{
    messageBus_.AddSubscriber(Name(), messageTypes, [this](std::shared_ptr<Message> message) { OnMessage(message); });
}

void BasicEntity::Unsubscribe(const std::vector<MessageType>& messageTypes)
{
    messageBus_.RemoveSubscriber(Name(), messageTypes);
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

}  // namespace Entity

}  // namespace FA
