/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

namespace Shared {

template <class T>
class SequenceIf
{
public:
    virtual void Update(float deltaTime) = 0;
    virtual T GetCurrent() const = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void Restart() = 0;
    virtual bool IsEmpty() const = 0;
    virtual bool IsCompleted() const = 0;
    virtual void Add(const T &element) = 0;
};

}  // namespace Shared

}  // namespace FA
