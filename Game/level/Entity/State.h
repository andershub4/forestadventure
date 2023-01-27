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
#include "Entity/Shape.h"
#include "Entity/StateType.h"

namespace FA {

namespace Entity {

struct BasicEvent;
class BasicAbility;
struct Body;

class State
{
public:
    State(StateType stateType, Body& body);
    virtual ~State();

    State(const State&) = delete;
    State& operator=(const State&) = delete;
    State(State&&) = delete;
    State& operator=(State&&) = delete;

    void Enter(std::shared_ptr<BasicEvent> event);
    void Exit();
    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget& renderTarget);
    void HandleEvent(std::shared_ptr<BasicEvent> event);
    StateType GetStateType() const { return stateType_; }
    void RegisterAbility(std::shared_ptr<BasicAbility> ability);
    void RegisterSprite(std::shared_ptr<BasicSprite> sprite);
    void RegisterEventCB(EventType eventType, std::function<void(std::shared_ptr<BasicEvent>)>);
    void RegisterIgnoreEvents(const std::vector<EventType>& eventTypes);
    void IgnoreAllEvents();

private:
    StateType stateType_ = StateType::Uninitialized;
    std::vector<std::shared_ptr<BasicAbility>> abilities_;
    std::unordered_map<EventType, std::function<void(std::shared_ptr<BasicEvent>)>> eventCBs_;
    bool ignoreAllEvents_ = false;
    Shape shape_;
};

}  // namespace Entity

}  // namespace FA
