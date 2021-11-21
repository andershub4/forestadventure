/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

namespace FA {

namespace Entity {

class PlayerEntity : public BasicEntity
{
public:
    PlayerEntity(EntityId id, CameraManager& cameraManager, const AnimationDb& animationDb, MessageBus& messageBus);
    virtual ~PlayerEntity();

    virtual std::string Name() const override { return "PlayerEntity"; }
    virtual void DefineProperties(EntityService& handler, const PropertyData& data) override;
    virtual void DefineModes(StateController& stateController) override;
    virtual void DefineShape(EntityService& entityService, Shape& shape) override;
    virtual void DefineInputIsKeyPressed(EntityService& entityService) override;
    virtual void DefineInputIsKeyReleased(EntityService& entityService) override;
    virtual void DefineInputKeyPressed(EntityService& entityService) override;
    virtual void OnDestroy() override;
};

}  // namespace Entity

}  // namespace FA
