/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <SFML/System/Vector2.hpp>

namespace FA {

namespace Entity {

class ComponentHandler;

class BasicComponent
{
public:
    BasicComponent(ComponentHandler *owner);
    virtual ~BasicComponent();

    virtual void Awake() {}
    virtual void Update(float deltaTime) = 0;

protected:
    ComponentHandler* Owner() const { return owner_; }

private:
    ComponentHandler* owner_ = nullptr;
};

}  // namespace Entity

}  // namespace FA
