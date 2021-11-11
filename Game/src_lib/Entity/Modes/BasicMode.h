/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_map>
#include <memory>

#include "Enum/FrameType.h"
#include "Entity/Action.h"
#include "Entity/UpdateInfo.h"
#include "Entity/EventType.h"

namespace FA {

namespace Entity {

struct BasicEvent;
class BasicState;
class StateController;
class Shape;
class EntityService;

class BasicMode
{
public:
    BasicMode(EntityService* owner);
    virtual ~BasicMode();

    BasicMode(const BasicMode&) = delete;
    BasicMode& operator=(const BasicMode&) = delete;
    BasicMode(BasicMode&&) = delete;
    BasicMode& operator=(BasicMode&&) = delete;

    virtual void Enter(std::shared_ptr<BasicEvent> event) {}
    virtual void Exit() {}
    virtual void Update(float deltaTime) {}
    virtual void Awake() {}

    virtual FrameType GetFrameType() const = 0;
    virtual ModeType GetModeType() const = 0;
    virtual std::unique_ptr<BasicState> CreateState(StateController& stateController, std::shared_ptr<BasicEvent> event) const = 0;

    void AddEvent(EventType eventType, ModeType modeType, std::function<void(std::shared_ptr<BasicEvent> event)> cb);
    void AddUpdateFn(std::function<bool(std::shared_ptr<Shape>)> updateFn, ModeType modeType);
    Action GetAction(EventType eventType) const;
    UpdateInfo GetUpdateInfo() const;

protected:
    EntityService* Owner() const { return owner_; }

private:
    EntityService* owner_ = nullptr;
    std::unordered_map<EventType, Action> eventMap_;
    UpdateInfo updateInfo_{};
};

}  // namespace Entity

}  // namespace FA
