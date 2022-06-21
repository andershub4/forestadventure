/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "Fwd/SfmlFwd.h"
#include "StateType.h"

namespace FA {

namespace Entity {

struct BasicEvent;
class BasicState;
struct Action;

class StateMachine
{
public:
    StateMachine();
    ~StateMachine();

    std::shared_ptr<BasicState> RegisterState(StateType stateType, bool startState = false);

    void HandleEvent(std::shared_ptr<BasicEvent> event);
    void Update(float deltaTime);
    void QueueInitEvents(std::shared_ptr<BasicEvent> event);
    void HandleQueuedInitEvents();

    void RegisterCreateCB(std::function<void(std::shared_ptr<BasicEvent> event)> onCreate);
    void RegisterDestroyCB(std::function<void(std::shared_ptr<BasicEvent> event)> onDestroy);

    void ChangeStateTo(StateType nextStateType, std::shared_ptr<BasicEvent> event);

private:
    std::unordered_map<StateType, std::shared_ptr<BasicState>> states_;
    std::shared_ptr<BasicState> currentState_ = nullptr;
    std::function<void(std::shared_ptr<BasicEvent> event)> onDestroy_{};
    std::vector<std::shared_ptr<BasicEvent>> queuedInitEvents_;

private:
    void InitState(std::shared_ptr<BasicState> state, bool startState);
};

}  // namespace Entity

}  // namespace FA
