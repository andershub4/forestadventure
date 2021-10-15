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
    PlayerEntity(EntityId id, CameraManager& cameraManager, MessageBus& messageBus);
    virtual ~PlayerEntity();

    virtual std::string Name() const override { return "PlayerEntity"; }
    virtual void OnCreate(PropertyHandler& handler, const PropertyData& data) override;
    virtual void OnDestroy() override;
    virtual void OnInit(const AnimationDb& animationDb) override;

protected:
    virtual void OnIsKeyPressed(Keyboard::Key key) override;
    virtual void OnIsKeyReleased(Keyboard::Key key) override;
    virtual void OnKeyPressed(Keyboard::Key key) override;
};

}  // namespace Entity

}  // namespace FA
