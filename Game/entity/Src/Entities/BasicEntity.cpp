/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicEntity.h"

#include <sstream>

#include "Events/CollisionEvent.h"
#include "Events/DestroyEvent.h"
#include "Events/InitEvent.h"
#include "Events/OutsideTileMapEvent.h"
#include "Message/BroadcastMessage/EntityCreatedMessage.h"
#include "Message/BroadcastMessage/EntityDestroyedMessage.h"
#include "State.h"

namespace FA {

namespace Entity {

BasicEntity::BasicEntity(EntityId id, const PropertyData& data, std::unique_ptr<EntityService> service)
    : id_(id)
    , data_(data)
    , service_(std::move(service))
{
    RegisterUninitializedState();
}

BasicEntity::~BasicEntity() = default;

void BasicEntity::InitCB()
{
    RegisterProperties();
    body_.position_ = data_.position_;
    body_.scale_ = 1.0;
    body_.rotation_ = 0.0;
    ReadProperties(data_.properties_);

    auto idleState = RegisterState(StateType::Idle);
    idleState->RegisterEnterCB([this]() { OnBeginIdle(); });
    auto deadState = RegisterDeadState();
    RegisterStates(idleState, deadState, data_);

    Subscribe(Messages());
    OnInit();  // must do this after setting position
    service_->SendMessage(std::make_shared<Shared::EntityInitializedMessage>());
    ChangeStateTo(StateType::Idle, nullptr);
}

void BasicEntity::Init()
{
    HandleEvent(std::make_shared<InitEvent>());
}

void BasicEntity::DestroyCB()
{
    Unsubscribe(Messages());
    service_->SendMessage(std::make_shared<Shared::EntityDestroyedMessage>());
}

void BasicEntity::Destroy()
{
    HandleEvent(std::make_shared<DestroyEvent>());
}

void BasicEntity::Update(float deltaTime)
{
    stateMachine_.Update(deltaTime);
}

void BasicEntity::DrawTo(Graphic::RenderTargetIf& renderTarget) const
{
    stateMachine_.GetShape().DrawTo(renderTarget);
}

bool BasicEntity::Intersect(const BasicEntity& otherEntity) const
{
    return stateMachine_.GetShape().Intersect(otherEntity.stateMachine_.GetShape());
}

bool BasicEntity::IsOutsideTileMap(const sf::FloatRect& rect) const
{
    return !rect.contains(body_.position_);
}

void BasicEntity::HandleCollision(const EntityId id, bool isSolid)
{
    HandleEvent(std::make_shared<CollisionEvent>(id, isSolid));
}

void BasicEntity::HandleOutsideTileMap()
{
    HandleEvent(std::make_shared<OutsideTileMapEvent>());
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
    state->RegisterEventCB(EventType::Destroy, [this](std::shared_ptr<BasicEvent> event) { DestroyCB(); });
    return state;
}

void BasicEntity::SendMessage(std::shared_ptr<Shared::Message> message)
{
    service_->SendMessage(message);
}

void BasicEntity::Subscribe(const std::vector<Shared::MessageType>& messageTypes)
{
    std::stringstream ss;
    ss << Type();

    service_->AddSubscriber(ss.str(), messageTypes,
                            [this](std::shared_ptr<Shared::Message> message) { OnMessage(message); });
}

void BasicEntity::Unsubscribe(const std::vector<Shared::MessageType>& messageTypes)
{
    std::stringstream ss;
    ss << Type();

    service_->RemoveSubscriber(ss.str(), messageTypes);
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
    deadState->RegisterEnterCB([this]() {
        OnBeginDie();
        service_->AddToDeletionQueue(id_);
    });
    deadState->IgnoreAllEventsExcept({EventType::Destroy});
    deadState->RegisterEventCB(EventType::Destroy, [this](std::shared_ptr<BasicEvent> event) { DestroyCB(); });

    return deadState;
}

}  // namespace Entity

}  // namespace FA
