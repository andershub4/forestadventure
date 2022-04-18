/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <functional>
#include <memory>

#include "StateType.h"

namespace FA {

namespace Entity {

struct BasicEvent;

struct Action
{
    Action() = default;

    StateType stateType_ = StateType::None;
    std::function<void(std::shared_ptr<BasicEvent>)> cb_;

    static Action Ignore();
    static Action ChangeTo(StateType stateType);
    static Action Call(std::function<void(std::shared_ptr<BasicEvent>)> cb);

private:
    Action(StateType stateType, std::function<void(std::shared_ptr<BasicEvent>)> cb)
        : stateType_(stateType)
        , cb_(cb)
    {}
    Action(StateType stateType)
        : stateType_(stateType)
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

inline Action Action::ChangeTo(StateType stateType)
{
    return Action(stateType);
}

inline Action Action::Call(std::function<void(std::shared_ptr<BasicEvent>)> cb)
{
    return Action(cb);
}

}  // namespace Entity

}  // namespace FA
