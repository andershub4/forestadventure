/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>

#include "BasicMode.h"

namespace FA {

namespace Entity {

class BasicState;
struct PropertyData;

class UninitializedMode : public BasicMode
{
public:
    UninitializedMode(EntityService *owner);

    virtual void Update(float deltaTime) override {}
    virtual FrameType GetFrameType() const override { return FrameType::Undefined; }
    virtual ModeType GetModeType() const override { return ModeType::Uninitialized; }
    virtual std::unique_ptr<BasicState> CreateState(StateController &stateController,
                                                    std::shared_ptr<BasicEvent> event) const override;

    void SetOnCreateCB(std::function<void(EntityService &, const PropertyData &)> onCreate) { onCreate_ = onCreate; }
    void Create(const PropertyData &data);

private:
    std::function<void(EntityService &, const PropertyData &)> onCreate_{};
};

}  // namespace Entity

}  // namespace FA
