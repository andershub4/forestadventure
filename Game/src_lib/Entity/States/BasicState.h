/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <unordered_map>

#include "Entity/Action.h"
#include "Entity/EventType.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Entity {

struct BasicEvent;
class BasicEntity;
class Shape;
class StateMachine;
class BasicAbility;

class BasicState
{
public:
    BasicState(StateType stateType, BasicEntity& entity, StateMachine & stateMachine);
    virtual ~BasicState();

    BasicState(const BasicState&) = delete;
    BasicState& operator=(const BasicState&) = delete;
    BasicState(BasicState&&) = delete;
    BasicState& operator=(BasicState&&) = delete;

    void Enter(std::shared_ptr<BasicEvent> event);
    void Exit();
    void Update(float deltaTime);
    void DrawTo(sf::RenderTarget& renderTarget);
    void HandleEvent(std::shared_ptr<BasicEvent> event);

    StateType GetStateType() const { return stateType_; }

    void BindAction(const Action& action, EventType eventType);
    void AddAbility(const std::string& name);
    void AddShape(const std::string& name, std::function<void(std::shared_ptr<Shape>)> stateFn);

private:
    struct ShapeEntry
    {
        std::string name_;
        std::function<void(std::shared_ptr<Shape>)> stateFn_;
    };

    BasicEntity& entity_;
    StateMachine& stateMachine_;
    std::unordered_map<EventType, Action> eventMap_;
    StateType stateType_ = StateType::Uninitialized;
    std::vector<std::string> abilities_;
    std::vector<ShapeEntry> shapes_;

private:
    Action GetAction(EventType eventType) const;
    void DoAction(const Action& action, std::shared_ptr<BasicEvent> event = nullptr);
};

}  // namespace Entity

}  // namespace FA
