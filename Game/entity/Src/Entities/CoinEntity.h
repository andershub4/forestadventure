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

    CoinEntity(EntityId id, const Shared::EntityData& data, std::unique_ptr<EntityService> service);
    virtual ~CoinEntity();

    virtual EntityType Type() const override { return EntityType::Coin; }
    virtual LayerType GetLayer() const override { return LayerType::Ground; }
    virtual bool IsStatic() const override { return true; }
    virtual bool IsSolid() const override { return false; }

private:
    virtual void RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const Shared::EntityData& data) override;
};

}  // namespace Entity

}  // namespace FA
