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
    MoleEntity(EntityId id, CameraManager& cameraManager, const AnimationDb& animationDb, MessageBus& messageBus);
    virtual ~MoleEntity();

    virtual std::string Name() const override { return "MoleEntity"; }
    virtual void OnAddProperties(EntityService& handler, const PropertyData& data) override;
    virtual void OnAddModes(StateController& stateController) override;
    virtual void OnAddShape(EntityService& entityService, Shape& shape) override;
};

}  // namespace Entity

}  // namespace FA
