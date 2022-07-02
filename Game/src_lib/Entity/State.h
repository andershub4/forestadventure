/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Entity/EventType.h"
#include "Entity/StateType.h"

namespace FA {

namespace Entity {

struct BasicEvent;
class BasicAbility;

class State
{
public:
    State(StateType stateType);
    virtual ~State();

    State(const State&) = delete;
    State& operator=(const State&) = delete;
    State(State&&) = delete;
    State& operator=(State&&) = delete;

    void Enter(std::shared_ptr<BasicEvent> event);
    void Exit();
    void Update(float deltaTime);
    void HandleEvent(std::shared_ptr<BasicEvent> event);
    StateType GetStateType() const { return stateType_; }
    void RegisterAbility(std::shared_ptr<BasicAbility> ability);
    void RegisterEventCB(EventType eventType, std::function<void(std::shared_ptr<BasicEvent>)>);
    void IgnoreAllEvents();

private:
    StateType stateType_ = StateType::Uninitialized;
    std::vector<std::shared_ptr<BasicAbility>> abilities_;
    std::unordered_map<EventType, std::function<void(std::shared_ptr<BasicEvent>)>> eventCBs_;
    bool ignoreAllEvents_ = false;
};

}  // namespace Entity

}  // namespace FA
