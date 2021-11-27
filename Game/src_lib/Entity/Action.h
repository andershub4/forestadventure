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

    ModeType modeType_ = ModeType::None;
    std::function<void(std::shared_ptr<BasicEvent>)> cb_;

    static Action Ignore();
    static Action ChangeTo(ModeType modeType);
    static Action Call(std::function<void(std::shared_ptr<BasicEvent>)> cb);

private:
    Action(ModeType modeType, std::function<void(std::shared_ptr<BasicEvent>)> cb)
        : modeType_(modeType)
        , cb_(cb)
    {}
    Action(ModeType modeType)
        : modeType_(modeType)
        , cb_(nullptr)
    {}
    Action(std::function<void(std::shared_ptr<BasicEvent>)> cb)
        : cb_(cb)
    {}
};

inline Action Action::Ignore()
{
    return Action();
}

inline Action Action::ChangeTo(ModeType modeType)
{
    return Action(modeType);
}

inline Action Action::Call(std::function<void(std::shared_ptr<BasicEvent>)> cb)
{
    return Action(cb);
}

}  // namespace Entity

}  // namespace FA
