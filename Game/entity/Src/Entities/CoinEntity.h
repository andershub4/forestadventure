/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

namespace FA {

namespace Entity {

class CoinEntity : public BasicEntity
{
public:
    static const std::string str;

    CoinEntity(EntityId id, const PropertyData& data, const Shared::MapData& mapData, const EntityService& service);
    virtual ~CoinEntity();

    virtual EntityType Type() const override { return EntityType::Coin; }
    virtual LayerType GetLayer() const override { return LayerType::Ground; }

private:
    virtual void RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data) override;
};

}  // namespace Entity

}  // namespace FA
