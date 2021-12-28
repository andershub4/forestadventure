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
    MoleEntity(EntityId id, CameraManager& cameraManager, TextureManager& textureManager, MessageBus& messageBus);
    virtual ~MoleEntity();

    virtual std::string Name() const override { return "MoleEntity"; }
    virtual EntityType Type() const override { return EntityType::Mole; }

protected:
    virtual std::vector<AnimationData> Animations() const override;

private:
    virtual void DefineProperties(EntityService& handler, const PropertyData& data) override;
    virtual void DefineModes(ModeController& modeController) override;
    virtual void DefineShape(EntityService& entityService, Shape& shape) override;
};

}  // namespace Entity

}  // namespace FA
