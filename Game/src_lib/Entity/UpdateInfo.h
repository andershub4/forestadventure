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

class Shape;

struct UpdateInfo
{
    UpdateInfo() = default;
    UpdateInfo(ModeType modeType, std::function<bool(std::shared_ptr<Shape>)> cb)
        : modeType_(modeType)
        , cb_(cb)
    {}

    ModeType modeType_ = ModeType::None;
    std::function<bool(std::shared_ptr<Shape>)> cb_;
};

}  // namespace Entity

}  // namespace FA
