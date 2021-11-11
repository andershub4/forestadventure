/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

namespace FA {

namespace Entity {

class EntityService;

class BasicAttribute
{
public:
    BasicAttribute(EntityService* owner);
    virtual ~BasicAttribute();

    BasicAttribute(const BasicAttribute&) = delete;
    BasicAttribute& operator=(const BasicAttribute&) = delete;
    BasicAttribute(BasicAttribute&&) = delete;
    BasicAttribute& operator=(BasicAttribute&&) = delete;

protected:
    EntityService* Owner() const { return owner_; }

private:
    EntityService* owner_ = nullptr;
};

}  // namespace Entity

}  // namespace FA
