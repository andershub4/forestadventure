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
    virtual void RegisterModes(ModeController& modeController) override;
    virtual void RegisterProperties(EntityService& entityService) override;
    virtual void InitModes(const ModeController& modeController, const EntityService& entityService,
                           const PropertyData& data) override;
};

}  // namespace Entity

}  // namespace FA
