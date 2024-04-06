/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <unordered_map>

#include "StateType.h"

namespace FA {

namespace Graphic {

class RenderTargetIf;

}  // namespace Graphic

namespace Entity {

struct BasicEvent;
class State;
struct Body;
class Shape;

class StateMachine
{
public:
    StateMachine();
    ~StateMachine();

    void SetStartState(std::shared_ptr<State> state);
    std::shared_ptr<State> RegisterState(StateType stateType, Body& body);

    void HandleEvent(std::shared_ptr<BasicEvent> event);
    void Update(float deltaTime);
    void DrawTo(Graphic::RenderTargetIf& renderTarget) const;
    void ChangeStateTo(StateType nextStateType, std::shared_ptr<BasicEvent> event);
    Shape GetShape() const;

private:
    std::unordered_map<StateType, std::shared_ptr<State>> states_;
    std::shared_ptr<State> currentState_ = nullptr;
};

}  // namespace Entity

}  // namespace FA
