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
               EntityManager& entityManager, MessageBus& messageBus);
    virtual ~CoinEntity();

    virtual std::string Name() const override { return "CoinEntity"; }
    virtual EntityType Type() const override { return EntityType::Coin; }

private:
    virtual void RegisterStates() override;
    virtual void RegisterProperties() override;
    virtual void RegisterShape(const PropertyData& data) override;

    void OnBeginAnimation(StateType stateType, AnimationSprite& sprite);
    void OnUpdateAnimation(AnimationSprite& sprite);
};

}  // namespace Entity

}  // namespace FA
