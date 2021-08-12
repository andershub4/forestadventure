/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicState.h"

namespace FA {

namespace Entity {

class MoveState : public BasicState
{
public:
    MoveState(StateMachine& stateMachine, StateData& stateData);
    virtual ~MoveState();

    virtual void Update(float deltaTime) override;
    virtual void LateUpdate() override;
    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual std::string Name() const override { return "MoveState"; }
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void OnStopMove() override;
};

}  // namespace Entity

}  // namespace FA
