/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

namespace Entity {

class AnimationPartIf
{
public:
    virtual ~AnimationPartIf() = default;

    virtual void Enter() = 0;
    virtual void Update(float deltaTime) = 0;
};

}  // namespace Entity

}  // namespace FA
