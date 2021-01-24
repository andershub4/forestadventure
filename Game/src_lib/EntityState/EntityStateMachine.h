/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "State/EntityState.h"

namespace FA {

class EntityStateMachine
{
public:
    EntityStateMachine(sf::RectangleShape* rectShape, FaceDirection faceDir, MoveDirection moveDir,
                       const AnimationFactory& animationFactory, float velocity);
    ~EntityStateMachine();

    void Update(float deltaTime);
    void SetState(std::unique_ptr<EntityState> newState);

    void OnStartMove(MoveDirection moveDir, FaceDirection faceDir);
    void OnStopMove();
    void OnStartAttack();

private:
    std::unique_ptr<EntityState> currentState_;
    EntityState::StateData stateData_;
};

}  // namespace FA
