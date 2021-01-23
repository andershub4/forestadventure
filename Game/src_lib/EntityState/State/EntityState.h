/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>

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
        MoveDirection moveDir_;
        FaceDirection faceDir_;
    };

    EntityState(EntityStateMachine& stateMachine, Entity& entity, StateData& stateData);
    virtual ~EntityState();

    virtual std::string Name() const = 0;
    virtual void Enter() {}
    virtual void Exit() {}

    virtual void OnStartMove(MoveDirection moveDir, FaceDirection faceDir) {}
    virtual void OnStopMove() {}

    void SwitchState(std::unique_ptr<EntityState> newState);

    template <class StateT, typename... Args>
    void SwitchState(Args&&... args)
    {
        static_assert(std::is_base_of<EntityState, StateT>::value, "StateT must derive from EntityState");

        SwitchState(std::make_unique<StateT>(stateMachine_, entity_, stateData_, std::forward<Args>(args)...));
    }

protected:
    StateData& stateData_;
    Entity& entity_;

private:
    EntityStateMachine& stateMachine_;
};

}  // namespace FA
