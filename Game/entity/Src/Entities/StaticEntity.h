/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

namespace FA {

namespace Entity {

class StaticEntity : public BasicEntity
{
public:
    static const std::string str;

    StaticEntity(EntityId id, const PropertyData& data, const Shared::MapData& mapData, const EntityService& service);
    virtual ~StaticEntity();

    virtual EntityType Type() const override { return EntityType::Static; }
    virtual LayerType GetLayer() const override { return LayerType::Ground; }
};

}  // namespace Entity

}  // namespace FA
