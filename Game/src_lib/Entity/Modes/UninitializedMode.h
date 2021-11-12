/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicMode.h"

namespace FA {

namespace Entity {

class UninitializedMode : public BasicMode
{
public:
    UninitializedMode(EntityService *owner);

    virtual void Update(float deltaTime) override {}
    virtual FrameType GetFrameType() const override { return FrameType::Undefined; }
    virtual ModeType GetModeType() const override { return ModeType::Uninitialized; }
    virtual std::unique_ptr<BasicState> CreateState(StateController &stateController,
                                                    std::shared_ptr<BasicEvent> event) const override;
};

}  // namespace Entity

}  // namespace FA
