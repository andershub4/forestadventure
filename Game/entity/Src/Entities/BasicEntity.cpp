/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicEntity.h"

#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Events/InitEvent.h"
#include "Message/BroadcastMessage/EntityCreatedMessage.h"
#include "Message/BroadcastMessage/EntityDestroyedMessage.h"
#include "State.h"

namespace FA {

namespace Entity {

BasicEntity::BasicEntity(EntityId id, const PropertyData& data, const EntityService& service)
    : id_(id)
    , data_(data)
    , entityService_(service)
{
    RegisterUninitializedState();
}

BasicEntity::~BasicEntity() = default;

void BasicEntity::InitCB()
{
    RegisterProperties();
    body_.position_ = data_.position_;
    ReadProperties(data_.properties_);

    auto idleState = RegisterState(StateType::Idle);
    idleState->RegisterBeginCB([this]() { OnBeginIdle(); });
    auto deadState = RegisterDeadState();
    RegisterStates(idleState, deadState, data_);

    Subscribe(Messages());
    OnInit();  // must do this after setting position
    entityService_.SendMessage(std::make_shared<Shared::EntityInitializedMessage>());
    ChangeStateTo(StateType::Idle, nullptr);
}

void BasicEntity::Init()
{
    HandleEvent(std::make_shared<InitEvent>());
}

void BasicEntity::Destroy()
{
    Unsubscribe(Messages());
    entityService_.SendMessage(std::make_shared<Shared::EntityDestroyedMessage>());
}

void BasicEntity::Update(float deltaTime)
{
    stateMachine_.Update(deltaTime);
}

void BasicEntity::DrawTo(sf::RenderTarget& renderTarget)
{
    stateMachine_.DrawTo(renderTarget);
}

void BasicEntity::HandleEvent(std::shared_ptr<BasicEvent> event)
{
    stateMachine_.HandleEvent(event);
}

void BasicEntity::ChangeStateTo(StateType stateType, std::shared_ptr<BasicEvent> event)
{
    stateMachine_.ChangeStateTo(stateType, event);
}

std::shared_ptr<State> BasicEntity::RegisterState(StateType stateType)
{
    auto state = stateMachine_.RegisterState(stateType, body_);
    state->RegisterEventCB(EventType::Dead,
                           [this](std::shared_ptr<BasicEvent> event) { ChangeStateTo(StateType::Dead, event); });
    return state;
}

void BasicEntity::SendMessage(std::shared_ptr<Shared::Message> message)
{
    entityService_.SendMessage(message);
}

void BasicEntity::Subscribe(const std::vector<Shared::MessageType>& messageTypes)
{
    std::stringstream ss;
    ss << Type();

    entityService_.AddSubscriber(ss.str(), messageTypes,
                                 [this](std::shared_ptr<Shared::Message> message) { OnMessage(message); });
}

void BasicEntity::Unsubscribe(const std::vector<Shared::MessageType>& messageTypes)
{
    std::stringstream ss;
    ss << Type();

    entityService_.RemoveSubscriber(ss.str(), messageTypes);
}

void BasicEntity::RegisterUninitializedState()
{
    auto uninitializedState = RegisterState(StateType::Uninitialized);
    uninitializedState->RegisterEventCB(EventType::Init, [this](std::shared_ptr<BasicEvent> event) { InitCB(); });
    stateMachine_.SetStartState(uninitializedState);
}

std::shared_ptr<State> BasicEntity::RegisterDeadState()
{
    auto deadState = stateMachine_.RegisterState(StateType::Dead, body_);
    deadState->RegisterBeginCB([this]() { OnBeginDie(); });
    deadState->IgnoreAllEvents();
    return deadState;
}

}  // namespace Entity

}  // namespace FA
