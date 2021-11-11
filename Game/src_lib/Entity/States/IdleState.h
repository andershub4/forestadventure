/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicState.h"

namespace FA {

namespace Entity {

class IdleState : public BasicState
{
public:
    IdleState(StateController& stateController, StateData& stateData, EntityService& entityService,
              std::shared_ptr<BasicEvent> event);
    virtual ~IdleState();

    virtual void Update(float deltaTime) override;
    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual std::string Name() const override { return "IdleState"; }
    virtual ModeType GetModeType() const override { return ModeType::Idle; }
};

}  // namespace Entity

}  // namespace FA
