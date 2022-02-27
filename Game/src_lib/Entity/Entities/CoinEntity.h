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
    virtual void AddAttributes(EntityService& handler, const AttributeData& data) override;
    virtual void RegisterModes(ModeController& modeController, const EntityService& entityService) override;
};

}  // namespace Entity

}  // namespace FA
