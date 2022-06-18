/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "BasicState.h"

#include "Entity/Abilities/BasicAbility.h"
#include "Entity/Entities/BasicEntity.h"
#include "Entity/Events/BasicEvent.h"
#include "Entity/Shape.h"
#include "Entity/StateMachine.h"
#include "Logging.h"

namespace FA {

namespace Entity {

BasicState::BasicState(StateType stateType, BasicEntity& entity, StateMachine& stateMachine)
    : stateMachine_(stateMachine)
    , stateType_(stateType)
    , entity_(entity)
{}

BasicState::~BasicState() = default;

void BasicState::Enter(std::shared_ptr<BasicEvent> event)
{
    for (auto a : abilities_) {
        a->Enter(event);
    }

    for (auto shape : shapes_) {
        entity_.OnEnterShape(stateType_, shape.name_);
    }
}

void BasicState::Exit()
{
    for (auto a : abilities_) {
        a->Exit();
    }

    for (auto shape : shapes_) {
        entity_.OnExitShape(stateType_, shape.name_);
    }
}

void BasicState::Update(float deltaTime)
{
    for (auto a : abilities_) {
        a->Update(deltaTime);
    }

    for (auto shape : shapes_) {
        entity_.OnUpdateShape(shape.name_, deltaTime, shape.stateFn_);
    }
}

void BasicState::DrawTo(sf::RenderTarget& renderTarget)
{
    for (auto shape : shapes_) {
        entity_.OnDrawShape(shape.name_, renderTarget);
    }
}

void BasicState::HandleEvent(std::shared_ptr<BasicEvent> event)
{
    auto action = GetAction(event->GetEventType());
    DoAction(action, event);
}

void BasicState::BindAction(const Action& action, EventType eventType)
{
    eventMap_[eventType] = action;
}

void BasicState::AddShape(const std::string& name, std::function<void(Shape&)> stateFn)
{
    shapes_.push_back({name, stateFn});
}

void BasicState::RegisterAbility(std::shared_ptr<BasicAbility> ability)
{
    abilities_.push_back(ability);
}

Action BasicState::GetAction(EventType eventType) const
{
    auto it = eventMap_.find(eventType);
    if (it != eventMap_.end()) {
        return eventMap_.at(eventType);
    }
    else {
        LOG_ERROR("stateType ", GetStateType(), " can't handle ", eventType);
        return {};
    }
}

void BasicState::DoAction(const Action& action, std::shared_ptr<BasicEvent> event)
{
    if (action.cb_) action.cb_(event);

    auto nextStateType = action.stateType_;
    if (nextStateType != StateType::None) {
        stateMachine_.ChangeStateTo(nextStateType, event);
    }
}

}  // namespace Entity

}  // namespace FA
