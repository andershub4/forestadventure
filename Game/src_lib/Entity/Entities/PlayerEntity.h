/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

namespace FA {

namespace Entity {

class AnimationComponent;

class PlayerEntity : public BasicEntity
{
public:
    PlayerEntity(EntityId id, const ComponentHandler& componentHandler, MessageBus& messageBus,
                 const TextureManager& textureManager);
    virtual ~PlayerEntity();

    virtual std::string Name() const override { return "PlayerEntity"; }
    virtual void OnCreate() override;
    virtual void OnDestroy() override;

protected:
    virtual void OnIsKeyPressed(Keyboard::Key key) override;
    virtual void OnIsKeyReleased(Keyboard::Key key) override;
    virtual void OnKeyPressed(Keyboard::Key key) override;

private:
    AnimationComponent CreateAnimation() const;
};

}  // namespace Entity

}  // namespace FA
