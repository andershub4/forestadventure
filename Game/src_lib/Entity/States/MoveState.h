/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicState.h"

namespace FA {

namespace Entity {

class MoveState : public BasicState
{
public:
    MoveState(StateController& stateController, StateData& stateData, EntityService& entityService,
              std::shared_ptr<BasicEvent> event);
    virtual ~MoveState();

    virtual void Update(float deltaTime) override;
    virtual void DrawTo(sf::RenderTarget& renderTarget) override;
    virtual std::string Name() const override { return "MoveState"; }
    virtual ModeType GetModeType() const override { return ModeType::Move; }
};

}  // namespace Entity

}  // namespace FA
