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
    PlayerEntity(EntityId id, MessageBus& messageBus, std::unique_ptr<BasicSprite> sprite, FaceDirection faceDir,
                 float velocity);
    virtual ~PlayerEntity();

    virtual std::string Name() const override { return "PlayerEntity"; }
    virtual void OnCreate() override;
    virtual void OnDestroy() override;

protected:
    virtual void OnIsKeyPressed(Keyboard::Key key) override;
    virtual void OnIsKeyReleased(Keyboard::Key key) override;
    virtual void OnKeyPressed(Keyboard::Key key) override;
};

}  // namespace Entity

}  // namespace FA
