/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "States/BasicState.h"

namespace FA {

namespace Entity {

class StateMachine
{
public:
    StateMachine(BasicState::StateData& stateData);
    ~StateMachine();

    void Update(float deltaTime);
    void LateUpdate();
    void DrawTo(sf::RenderTarget& renderTarget);
    void SetState(std::unique_ptr<BasicState> newState);

    void OnInitStateData(const ConfigurationData& configurationData, const AnimationComponent& animation);
    void OnStartMove(MoveDirection moveDir, FaceDirection faceDir);
    void OnStopMove();
    void OnAttack();
    void OnAttackWeapon();

private:
    std::unique_ptr<BasicState> currentState_;
};

}  // namespace Entity

}  // namespace FA
