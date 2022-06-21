/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <set>
#include <unordered_map>

#include "Entity/Action.h"
#include "Entity/EventType.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Entity {

struct BasicEvent;
class StateMachine;
class BasicAbility;

class BasicState
{
public:
    BasicState(StateType stateType, StateMachine& stateMachine);
    virtual ~BasicState();

    BasicState(const BasicState&) = delete;
    BasicState& operator=(const BasicState&) = delete;
    BasicState(BasicState&&) = delete;
    BasicState& operator=(BasicState&&) = delete;

    void Enter(std::shared_ptr<BasicEvent> event);
    void Exit();
    void Update(float deltaTime);
    void HandleEvent(std::shared_ptr<BasicEvent> event);

    StateType GetStateType() const { return stateType_; }

    void BindAction(const Action& action, EventType eventType);
    void RegisterAbility(std::shared_ptr<BasicAbility> ability);

private:
    StateMachine& stateMachine_;
    std::unordered_map<EventType, Action> eventMap_;
    StateType stateType_ = StateType::Uninitialized;
    std::set<std::shared_ptr<BasicAbility>> abilities_;

private:
    Action GetAction(EventType eventType) const;
    void DoAction(const Action& action, std::shared_ptr<BasicEvent> event = nullptr);
};

}  // namespace Entity

}  // namespace FA
