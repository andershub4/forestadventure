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

BasicState::BasicState(StateType stateType, BasicEntity& entity, Shape& shape, StateMachine& stateMachine)
    : stateMachine_(stateMachine)
    , stateType_(stateType)
    , entity_(entity)
    , shape_(shape)
{}

BasicState::~BasicState() = default;

void BasicState::Enter(std::shared_ptr<BasicEvent> event)
{
    for (auto ability : abilities_) {
        entity_.OnEnterAbility(ability, event);
    }

    for (auto sprite : animations_) {
        shape_.OnEnterAnimation(stateType_, sprite.name_);
    }

    for (auto sprite : images_) {
        shape_.OnEnterImage(stateType_, sprite.name_);
    }
}

void BasicState::Exit()
{
    for (auto ability : abilities_) {
        entity_.OnExitAbility(ability);
    }

    for (auto sprite : animations_) {
        shape_.OnExitAnimation(stateType_, sprite.name_);
    }

    for (auto sprite : images_) {
        shape_.OnExitImage(stateType_, sprite.name_);
    }
}

void BasicState::Update(float deltaTime)
{
    for (auto a : abilities_) {
        entity_.OnUpdateAbility(a, deltaTime);
    }

    for (auto sprite : animations_) {
        shape_.OnUpdateAnimation(sprite.name_, deltaTime, sprite.stateFn_);
    }

    for (auto sprite : images_) {
        shape_.OnUpdateImage(sprite.name_, deltaTime, sprite.stateFn_);
    }
}

void BasicState::DrawTo(sf::RenderTarget& renderTarget)
{
    for (auto sprite : animations_) {
        shape_.OnDrawAnimation(sprite.name_, renderTarget);
    }

    for (auto sprite : images_) {
        shape_.OnDrawImage(sprite.name_, renderTarget);
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

void BasicState::AddAbility(const std::string& name)
{
    abilities_.push_back(name);
}

void BasicState::AddAnimation(const std::string& name, std::function<void(std::shared_ptr<AnimationSprite>)> stateFn)
{
    animations_.push_back({name, stateFn});
}

void BasicState::AddImage(const std::string& name, std::function<void(std::shared_ptr<ImageSprite>)> stateFn)
{
    images_.push_back({name, stateFn});
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
