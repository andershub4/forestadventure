/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicState.h"

namespace FA {

namespace Entity {

class AttackState : public BasicState
{
public:
    AttackState(StateController& stateController, StateData& stateData,
                EntityService& entityService, std::shared_ptr<BasicEvent> event);
    virtual ~AttackState();

    virtual void Update(float deltaTime) override;
    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual std::string Name() const override { return "AttackState"; }
    virtual ModeType GetModeType() const override { return ModeType::Attack; }
};

}  // namespace Entity

}  // namespace FA
