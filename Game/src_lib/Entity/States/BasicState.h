/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <string>

#include "Entity/Configuration.h"
#include "Enum/FaceDirection.h"
#include "Enum/MoveDirection.h"
#include "Fwd/SfmlFwd.h"

namespace FA {

namespace Entity {

class StateMachine;
struct ConfigurationData;

class BasicState
{
public:
    struct StateData
    {
        std::unique_ptr<Configuration> configuration_ = nullptr;
    };

    BasicState(StateMachine& stateMachine, StateData& stateData);
    virtual ~BasicState();

    virtual void Update(float deltaTime) = 0;
    virtual void DrawTo(sf::RenderTarget& renderTarget) = 0;
    virtual std::string Name() const = 0;
    virtual void Enter() {}
    virtual void Exit() {}

    virtual void LateUpdate() {}
    virtual void OnInitStateData(std::unique_ptr<Configuration> configuration) {}
    virtual void OnStartMove(MoveDirection moveDir, FaceDirection faceDir) {}
    virtual void OnStopMove() {}
    virtual void OnAttack() {}
    virtual void OnAttackWeapon() {}

    void SwitchState(std::unique_ptr<BasicState> newState);

    template <class StateT, typename... Args>
    void SwitchState(Args&&... args)
    {
        static_assert(std::is_base_of<BasicState, StateT>::value, "StateT must derive from BasicState");

        SwitchState(std::make_unique<StateT>(stateMachine_, stateData_, std::forward<Args>(args)...));
    }

protected:
    StateData& stateData_;

private:
    StateMachine& stateMachine_;
};

}  // namespace Entity

}  // namespace FA
