/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "MoveState.h"

#include "Entity/Shapes/Shape.h"

namespace FA {

namespace Entity {

MoveState::MoveState(StateController& stateController, StateData& stateData, EntityService& entityService,
                     std::shared_ptr<BasicEvent> event)
    : BasicState(stateController, stateData, entityService)
{
    InternalEnter(event);
}

MoveState::~MoveState()
{
    InternalExit();
}

void MoveState::Update(float deltaTime)
{
    GetShape()->Update(deltaTime);
    InternalUpdate(deltaTime);
}

void MoveState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetShape()->DrawTo(renderTarget);
}

}  // namespace Entity

}  // namespace FA
