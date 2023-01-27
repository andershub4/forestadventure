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
    TileEntity(EntityId id, Level& level, const Shared::SheetManager& sheetManager, Shared::MessageBus& messageBus);
    virtual ~TileEntity();

    virtual std::string Name() const override { return "TileEntity"; }
    virtual EntityType Type() const override { return EntityType::Tile; }
    virtual LayerType GetLayer() const override { return LayerType::Waterfall; }

private:
    virtual void RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data) override;
};

}  // namespace Entity

}  // namespace FA
