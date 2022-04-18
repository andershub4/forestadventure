/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

#include "BasicState.h"

namespace FA {

namespace Entity {

class IdleState : public BasicState
{
public:
    IdleState(EntityService& entityService, StateMachine& stateMachine);

    virtual void Enter(std::shared_ptr<BasicEvent> event) override;

    virtual void Register() override;
    virtual void Update(float deltaTime) override;
    virtual StateType GetStateType() const override { return StateType::Idle; }

private:
    std::shared_ptr<Shape> shape_ = nullptr;
};

}  // namespace Entity

}  // namespace FA
