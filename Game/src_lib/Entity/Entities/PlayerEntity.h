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
    virtual void OnDestroy() override;

protected:
    virtual void HandleIsKeyPressed(Keyboard::Key key) override;
    virtual void HandleIsKeyReleased(Keyboard::Key key) override;
    virtual void HandleKeyPressed(Keyboard::Key key) override;

private:
    virtual void DefineProperties(EntityService& handler, const PropertyData& data) override;
    virtual void DefineModes(ModeController& modeController) override;
    virtual void DefineShape(EntityService& entityService, Shape& shape) override;
};

}  // namespace Entity

}  // namespace FA
