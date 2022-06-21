/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

namespace FA {

namespace Entity {

class MoleEntity : public BasicEntity
{
public:
    MoleEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
               EntityManager& entityManager, MessageBus& messageBus);
    virtual ~MoleEntity();

    virtual std::string Name() const override { return "MoleEntity"; }
    virtual EntityType Type() const override { return EntityType::Mole; }

private:
    virtual void RegisterProperties() override;
    virtual void RegisterShape() override;
    virtual void RegisterStates(const PropertyData& data) override;

    void OnBeginMove(FaceDirection faceDirection);
    void OnUpdateMove(const sf::Vector2f& delta);
    void OnUpdateAnimation(const Animation& animation);
};

}  // namespace Entity

}  // namespace FA
