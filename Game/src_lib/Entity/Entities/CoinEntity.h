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
    CoinEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
               EntityManager& entityManager, MessageBus& messageBus, const sf::Vector2u& mapSize);
    virtual ~CoinEntity();

    virtual std::string Name() const override { return "CoinEntity"; }
    virtual EntityType Type() const override { return EntityType::Coin; }
    virtual LayerType GetLayer() const override { return LayerType::Ground; }

private:
    virtual void RegisterShape() override;
    virtual void RegisterStates(const PropertyData& data) override;

    void OnUpdateAnimation(const Animation& animation);
};

}  // namespace Entity

}  // namespace FA
