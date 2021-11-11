/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

#include "BasicMode.h"

namespace FA {

namespace Entity {

class BasicState;

class IdleMode : public BasicMode
{
public:
    IdleMode(EntityService* owner);

    virtual void Enter(std::shared_ptr<BasicEvent> event) override;

    virtual void Update(float deltaTime) override {}
    virtual FrameType GetFrameType() const override { return FrameType::Idle; }
    virtual ModeType GetModeType() const override { return ModeType::Idle; }
    virtual std::unique_ptr<BasicState> CreateState(StateController& stateController,
                                                    std::shared_ptr<BasicEvent> event) const override;
};

}  // namespace Entity

}  // namespace FA
