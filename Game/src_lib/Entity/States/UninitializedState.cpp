/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "UninitializedState.h"

#include "Enum/FrameType.h"
#include "IdleState.h"

namespace FA {

namespace Entity {

UninitializedState::UninitializedState(StateMachine& stateMachine, StateData& stateData)
    : BasicState(stateMachine, stateData)
{}

UninitializedState::~UninitializedState() = default;

void UninitializedState::OnInitStateData(FaceDirection faceDir, float velocity, std::unique_ptr<BasicSprite> sprite)
{
    stateData_.faceDir_ = faceDir;
    stateData_.velocity_ = velocity;
    stateData_.moveDir_ = MoveDirection::None;
    stateData_.sprite_ = std::move(sprite);

    SwitchState<IdleState>();
}

}  // namespace Entity

}  // namespace FA
