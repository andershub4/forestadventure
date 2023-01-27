/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

#include "Enum/FaceDirection.h"

namespace FA {

namespace Entity {

class ArrowEntity : public BasicEntity
{
public:
    ArrowEntity(EntityId id, Level& level, const Shared::SheetManager& sheetManager, Shared::MessageBus& messageBus);
    virtual ~ArrowEntity();

    virtual std::string Name() const override { return "ArrowEntity"; }
    virtual EntityType Type() const override { return EntityType::Arrow; }
    virtual LayerType GetLayer() const override { return LayerType::Ground; }

private:
    virtual void RegisterStates(std::shared_ptr<State> idleState, const PropertyData& data) override;

    void OnBeginMove(FaceDirection faceDirection);
    void OnUpdateMove(const sf::Vector2f& delta);
};

}  // namespace Entity

}  // namespace FA
