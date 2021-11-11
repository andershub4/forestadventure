/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "IdleState.h"

#include "Entity/Shapes/Shape.h"

namespace FA {

namespace Entity {

IdleState::IdleState(StateController& stateController, StateData& stateData, EntityService& entityService,
                     std::shared_ptr<BasicEvent> event)
    : BasicState(stateController, stateData, entityService)
{
    InternalEnter(event);
}

IdleState::~IdleState() = default;

void IdleState::Update(float deltaTime)
{
    GetShape()->Update(deltaTime);
}

void IdleState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetShape()->DrawTo(renderTarget);
}

}  // namespace Entity

}  // namespace FA
