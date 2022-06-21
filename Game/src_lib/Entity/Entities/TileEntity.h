/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

namespace FA {

namespace Entity {

class TileEntity : public BasicEntity
{
public:
    TileEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
               EntityManager& entityManager, MessageBus& messageBus);
    virtual ~TileEntity();

    virtual std::string Name() const override { return "TileEntity"; }
    virtual EntityType Type() const override { return EntityType::Tile; }

private:
    virtual void RegisterProperties() override;
    virtual void RegisterShape() override;
    virtual void RegisterStates(const PropertyData& data) override;

    void UpdateAnimation(const Animation& animation);
};

}  // namespace Entity

}  // namespace FA
