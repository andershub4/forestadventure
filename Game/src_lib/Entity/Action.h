/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>

#include "ModeType.h"

namespace FA {

namespace Entity {

struct BasicEvent;

struct Action
{
    Action() = default;
    Action(ModeType modeType, std::function<void(std::shared_ptr<BasicEvent>)> cb)
        : modeType_(modeType)
        , cb_(cb)
    {}

    ModeType modeType_ = ModeType::None;
    std::function<void(std::shared_ptr<BasicEvent>)> cb_;
};

}  // namespace Entity

}  // namespace FA
