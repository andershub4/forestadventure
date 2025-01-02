/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "EventType.h"
#include "Shape.h"
#include "StateType.h"

namespace FA {

namespace Graphic {

class RenderTargetIf;

}  // namespace Graphic

namespace Shared {

struct ImageFrame;
struct ColliderFrame;

}  // namespace Shared

namespace Entity {

struct BasicEvent;
class AbilityIf;
struct Body;
template <class T>
class AnimatorIf;

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
    void HandleEvent(std::shared_ptr<BasicEvent> event);
    StateType GetStateType() const { return stateType_; }
    void RegisterEnterCB(std::function<void()> enterCB);
    void RegisterExitCB(std::function<void()> exitCB);
    void RegisterAbility(std::shared_ptr<AbilityIf> ability);
    std::shared_ptr<Graphic::SpriteIf> RegisterSprite();
    std::shared_ptr<Graphic::RectangleShapeIf> RegisterCollider(Shape::ColliderType layer);
    void RegisterImageAnimator(std::shared_ptr<AnimatorIf<Shared::ImageFrame>> animator);
    void RegisterColliderAnimator(std::shared_ptr<AnimatorIf<Shared::ColliderFrame>> animator);
    void RegisterEventCB(EventType eventType, std::function<void(std::shared_ptr<BasicEvent>)>);
    void RegisterIgnoreEvents(const std::vector<EventType>& eventTypes);
    void IgnoreAllEventsExcept(const std::unordered_set<EventType>& notIgnorableEventTypes);
    Shape GetShape() const;

private:
    StateType stateType_ = StateType::Uninitialized;
    std::vector<std::shared_ptr<AbilityIf>> abilities_;
    std::unordered_set<EventType> notIgnorableEventTypes_;
    std::unordered_map<EventType, std::function<void(std::shared_ptr<BasicEvent>)>> eventCBs_;
    bool ignoreAllEvents_ = false;
    Shape shape_;
    std::function<void()> enterCB_;
    std::function<void()> exitCB_;
};

}  // namespace Entity

}  // namespace FA
