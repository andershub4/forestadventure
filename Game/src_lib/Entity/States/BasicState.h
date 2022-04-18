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

class Animation;
class Image;

namespace Entity {

struct BasicEvent;
class Shape;
class EntityService;
class StateMachine;

class BasicState
{
public:
    BasicState(EntityService& entityService, StateMachine& stateMachine);
    virtual ~BasicState();

    BasicState(const BasicState&) = delete;
    BasicState& operator=(const BasicState&) = delete;
    BasicState(BasicState&&) = delete;
    BasicState& operator=(BasicState&&) = delete;

    virtual void Enter(std::shared_ptr<BasicEvent> event) {}
    virtual void Exit() {}
    virtual void Update(float deltaTime) {}
    virtual void DrawTo(sf::RenderTarget& renderTarget);
    virtual void HandleEvent(std::shared_ptr<BasicEvent> event);
    virtual void Register() {}

    virtual StateType GetStateType() const = 0;

    void BindAction(const Action& action, EventType eventType);
    void BindActionDuringUpdate(const Action& action, std::function<bool(std::shared_ptr<Shape>)> condition);
    void SetAnimationFn(std::function<Animation(const EntityService&)> fn) { animationFn_ = fn; }
    void SetImageFn(std::function<Image(const EntityService&)> fn) { imageFn_ = fn; }

protected:
    EntityService& Service() const { return entityService_; }
    Animation GetAnimation() const;
    Image GetImage() const;
    void BasicUpdate();

private:
    EntityService& entityService_;
    StateMachine& stateMachine_;
    std::unordered_map<EventType, Action> eventMap_;
    std::function<bool(std::shared_ptr<Shape>)> actionCondition_ = [](std::shared_ptr<Shape>) { return false; };
    Action nextAction_{};
    std::function<Animation(const EntityService&)> animationFn_;
    std::function<Image(const EntityService&)> imageFn_;

private:
    Action GetAction(EventType eventType) const;
    Action PollAction() const;
    void DoAction(const Action& action, std::shared_ptr<BasicEvent> event = nullptr);
};

}  // namespace Entity

}  // namespace FA
