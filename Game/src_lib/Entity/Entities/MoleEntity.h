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

class MoleEntity : public BasicEntity
{
public:
    MoleEntity(EntityId id, const ComponentHandler& componentHandler, MessageBus& messageBus,
               const TextureManager& textureManager);
    virtual ~MoleEntity();

    virtual std::string Name() const override { return "MoleEntity"; }
    virtual void OnCreate() override;

private:
    AnimationComponent CreateAnimation() const;
};

}  // namespace Entity

}  // namespace FA
