/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>

#include "Animation/AnimationFactory.h"
#include "Enum/FaceDirection.h"
#include "Enum/MoveDirection.h"

namespace FA {

class EntityStateMachine;
class Entity;

class EntityState
{
public:
    struct StateData
    {
        MoveDirection moveDir_ = MoveDirection::None;
        FaceDirection faceDir_ = FaceDirection::Down;
        AnimationFactory animationFactory_;
        float velocity_ = 0.0;
        sf::RectangleShape* rectShape_ = nullptr;
    };

    EntityState(EntityStateMachine& stateMachine, StateData& stateData);
    virtual ~EntityState();

    virtual void Update(float deltaTime) = 0;
    virtual std::string Name() const = 0;
    virtual void Enter() {}
    virtual void Exit() {}

    virtual void OnStartMove(MoveDirection moveDir, FaceDirection faceDir) {}
    virtual void OnStopMove() {}
    virtual void OnStartAttack() {}
    virtual void OnStartAttackWeapon() {}

    void SwitchState(std::unique_ptr<EntityState> newState);

    template <class StateT, typename... Args>
    void SwitchState(Args&&... args)
    {
        static_assert(std::is_base_of<EntityState, StateT>::value, "StateT must derive from EntityState");

        SwitchState(std::make_unique<StateT>(stateMachine_, stateData_, std::forward<Args>(args)...));
    }

protected:
    StateData& stateData_;

private:
    EntityStateMachine& stateMachine_;
};

}  // namespace FA
