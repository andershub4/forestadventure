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

namespace Entity {

class StateMachine;
class BasicEntity;

class BasicState
{
public:
    struct StateData
    {
        MoveDirection moveDir_ = MoveDirection::None;
        FaceDirection faceDir_ = FaceDirection::Down;
        float velocity_ = 0.0;
        sf::RectangleShape* rectShape_ = nullptr;
    };

    BasicState(StateMachine& stateMachine, const AnimationFactory& animationFactory, StateData& stateData);
    virtual ~BasicState();

    virtual void Update(float deltaTime) = 0;
    virtual std::string Name() const = 0;
    virtual void Enter() {}
    virtual void Exit() {}

    virtual void OnStartMove(MoveDirection moveDir, FaceDirection faceDir) {}
    virtual void OnStopMove() {}
    virtual void OnAttack() {}
    virtual void OnAttackWeapon() {}

    void SwitchState(std::unique_ptr<BasicState> newState);

    template <class StateT, typename... Args>
    void SwitchState(Args&&... args)
    {
        static_assert(std::is_base_of<BasicState, StateT>::value, "StateT must derive from BasicState");

        SwitchState(
            std::make_unique<StateT>(stateMachine_, animationFactory_, stateData_, std::forward<Args>(args)...));
    }

protected:
    StateData& stateData_;
    const AnimationFactory& animationFactory_;

private:
    StateMachine& stateMachine_;
};

}  // namespace Entity

}  // namespace FA
