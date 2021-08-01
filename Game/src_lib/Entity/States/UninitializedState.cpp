/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "UninitializedState.h"

#include "Entity/Configuration.h"
#include "Enum/FrameType.h"
#include "IdleState.h"

namespace FA {

namespace Entity {

UninitializedState::UninitializedState(StateMachine& stateMachine, StateData& stateData)
    : BasicState(stateMachine, stateData)
{}

UninitializedState::~UninitializedState() = default;

void UninitializedState::OnInitStateData(const Configuration& configuration, const AnimationDB& animationDB)
{
    stateData_.faceDir_ = configuration.faceDir_;
    stateData_.velocity_ = configuration.velocity_;
    stateData_.moveDir_ = MoveDirection::None;
    stateData_.transform_ = TransformComponent(configuration.position_, configuration.scale_);
    stateData_.sprite_ = SpriteComponent(stateData_.transform_, animationDB);

    SwitchState<IdleState>();
}

}  // namespace Entity

}  // namespace FA
