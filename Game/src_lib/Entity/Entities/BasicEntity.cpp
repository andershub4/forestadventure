/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Entity/Abilities/DieAbility.h"
#include "Entity/Events/CreateEvent.h"
#include "Entity/Events/DestroyEvent.h"
#include "Entity/Events/InitEvent.h"
#include "Entity/Shape.h"
#include "Entity/State.h"
#include "Message/BroadcastMessage/EntityCreatedMessage.h"
#include "Message/BroadcastMessage/EntityDestroyedMessage.h"
#include "Message/MessageBus.h"

namespace FA {

namespace Entity {

BasicEntity::BasicEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                         EntityManager& entityManager, MessageBus& messageBus)
    : id_(id)
    , messageBus_(messageBus)
    , entityService_(cameraManager, sheetManager, entityManager)
{
    stateMachine_.RegisterCreateCB([this](std::shared_ptr<BasicEvent> event) { OnCreate(event); });
    stateMachine_.RegisterDestroyCB([this](std::shared_ptr<BasicEvent> event) { OnDestroy(event); });
}

BasicEntity::~BasicEntity() = default;

void BasicEntity::Create(const PropertyData& data)
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
    stateMachine_.HandleQueuedInitEvents();
}

void BasicEntity::Update(float deltaTime)
{
    stateMachine_.Update(deltaTime);
    shape_.Update();
}

void BasicEntity::DrawTo(sf::RenderTarget& renderTarget)
{
    shape_.Draw(renderTarget);
}

void BasicEntity::QueueInitEvents(std::shared_ptr<BasicEvent> event)
{
    stateMachine_.QueueInitEvents(event);
}

void BasicEntity::HandleEvent(std::shared_ptr<BasicEvent> event)
{
    stateMachine_.HandleEvent(event);
}

void BasicEntity::ChangeState(StateType stateType, std::shared_ptr<BasicEvent> event)
{
    stateMachine_.ChangeStateTo(stateType, event);
}

void BasicEntity::OnUpdateShape()
{
    shape_.SetPosition(position_);
    shape_.SetRotation(rotation_);
}

Shape BasicEntity::CreateShape()
{
    return Shape([this]() { OnUpdateShape(); });
}

std::shared_ptr<State> BasicEntity::RegisterState(StateType stateType, bool startState)
{
    auto state = stateMachine_.RegisterState(stateType, startState);
    state->RegisterEventCB(EventType::Dead,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeState(StateType::Dead, event); });
    return state;
}

void BasicEntity::SendMessage(std::shared_ptr<Message> message)
{
    messageBus_.SendMessage(message);
}

void BasicEntity::OnCreate(std::shared_ptr<BasicEvent> event)
{
    auto c = std::dynamic_pointer_cast<CreateEvent>(event);
    auto data = c->data_;

    RegisterProperties();
    RegisterDeadState();
    RegisterStates(data);

    // ReadObjectData
    position_ = data.position_;

    for (const auto& p : data.properties_) {
        propertyManager_.ReadCustomProperty(p.first, p.second);
    }

    RegisterShape();
    Subscribe(Messages());
    Start();  // must do this after setting position
    messageBus_.SendMessage(std::make_shared<EntityCreatedMessage>());
}

void BasicEntity::OnDestroy(std::shared_ptr<BasicEvent> event)
{
    Unsubscribe(Messages());
    messageBus_.SendMessage(std::make_shared<EntityDestroyedMessage>());
}

void BasicEntity::Subscribe(const std::vector<MessageType>& messageTypes)
{
    messageBus_.AddSubscriber(Name(), messageTypes, [this](std::shared_ptr<Message> message) { OnMessage(message); });
}

void BasicEntity::Unsubscribe(const std::vector<MessageType>& messageTypes)
{
    messageBus_.RemoveSubscriber(Name(), messageTypes);
}

void BasicEntity::RegisterDeadState()
{
    auto deadState = RegisterState(StateType::Dead);
    auto die = std::make_shared<DieAbility>([this]() { OnDying(); });
    deadState->RegisterAbility(die);
    deadState->IgnoreAllEvents();
}

}  // namespace Entity

}  // namespace FA
