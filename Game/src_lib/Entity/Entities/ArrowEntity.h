/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

namespace FA {

namespace Entity {

class ArrowEntity : public BasicEntity
{
public:
    ArrowEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                EntityManager& entityManager, MessageBus& messageBus);
    virtual ~ArrowEntity();

    virtual std::string Name() const override { return "ArrowEntity"; }
    virtual EntityType Type() const override { return EntityType::Arrow; }

private:
    virtual void RegisterShape() override;
    virtual void RegisterStates(const PropertyData& data) override;

    void OnBeginMove(FaceDirection faceDirection);
    void OnUpdateMove(const sf::Vector2f& delta);
    void OnUpdateAnimation(const Animation& animation);
};

}  // namespace Entity

}  // namespace FA
