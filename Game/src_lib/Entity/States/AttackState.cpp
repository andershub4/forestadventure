/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "AttackState.h"

#include "Entity/Shapes/Shape.h"

namespace FA {

namespace Entity {

AttackState::AttackState(StateController& stateController, StateData& stateData, EntityService& entityService,
                         std::shared_ptr<BasicEvent> event)
    : BasicState(stateController, stateData, entityService)
{
    InternalEnter(event);
}

AttackState::~AttackState() = default;

void AttackState::Update(float deltaTime)
{
    GetShape()->Update(deltaTime);
    BasicState::Update();
}

void AttackState::DrawTo(sf::RenderTarget& renderTarget)
{
    GetShape()->DrawTo(renderTarget);
}

}  // namespace Entity

}  // namespace FA
