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

class IdleMode : public BasicMode
{
public:
    IdleMode(EntityService& entityService, ModeController& modeController);

    virtual void Enter(std::shared_ptr<BasicEvent> event) override;

    virtual void Register() override;
    virtual void Update(float deltaTime) override;
    virtual ModeType GetModeType() const override { return ModeType::Idle; }

private:
    std::shared_ptr<Shape> shape_ = nullptr;
};

}  // namespace Entity

}  // namespace FA
