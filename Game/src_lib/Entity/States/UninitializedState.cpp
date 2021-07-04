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

void UninitializedState::OnInitStateData(FaceDirection faceDir, float velocity, const sf::Vector2f& position,
                                         float scale, const AnimationDB& animationDB)
{
    stateData_.faceDir_ = faceDir;
    stateData_.velocity_ = velocity;
    stateData_.moveDir_ = MoveDirection::None;
    stateData_.transform_ = Transform(position, scale);
    stateData_.sprite_ = Sprite(stateData_.transform_, animationDB);

    SwitchState<IdleState>();
}

}  // namespace Entity

}  // namespace FA
