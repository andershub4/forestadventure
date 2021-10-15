/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

namespace Entity {

class PropertyHandler;

class BasicProperty
{
public:
    BasicProperty(PropertyHandler* owner);
    virtual ~BasicProperty();

    BasicProperty(const BasicProperty&) = delete;
    BasicProperty& operator=(const BasicProperty&) = delete;
    BasicProperty(BasicProperty&&) = delete;
    BasicProperty& operator=(BasicProperty&&) = delete;

    virtual void Awake() = 0;
    virtual void Update(float deltaTime) = 0;

protected:
    PropertyHandler* Owner() const { return owner_; }

private:
    PropertyHandler* owner_ = nullptr;
};

}  // namespace Entity

}  // namespace FA
