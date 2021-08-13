/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "UninitializedState.h"

#include "Entity/ConfigurationData.h"
#include "Enum/FrameType.h"
#include "IdleState.h"

namespace FA {

namespace Entity {

UninitializedState::UninitializedState(StateMachine& stateMachine, StateData& stateData)
    : BasicState(stateMachine, stateData)
{}

UninitializedState::~UninitializedState() = default;

void UninitializedState::OnInitStateData(const ConfigurationData& configurationData, const AnimationComponent& animation)
{
    stateData_.faceDir_ = configurationData.faceDir_;
    stateData_.movement_ = MovementComponent(configurationData.velocity_);
    stateData_.transform_ = TransformComponent(configurationData.position_, configurationData.scale_);
    stateData_.sprite_ = SpriteComponent(stateData_.transform_, animation);

    SwitchState<IdleState>();
}

}  // namespace Entity

}  // namespace FA
