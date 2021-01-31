/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicState.h"

namespace FA {

namespace Entity {

class IdleState : public BasicState
{
public:
    IdleState(StateMachine& stateMachine, const AnimationFactory& animationFactory, StateData& stateData);
    virtual ~IdleState();

    virtual void Update(float deltaTime) override;
    virtual std::string Name() const override { return "IdleState"; }
    virtual void Enter() override;

    virtual void OnStartMove(MoveDirection moveDir, FaceDirection faceDir) override;
    virtual void OnAttack() override;
    virtual void OnAttackWeapon() override;

private:
    std::unique_ptr<Animation> animation_ = nullptr;
};

}  // namespace Entity

}  // namespace FA