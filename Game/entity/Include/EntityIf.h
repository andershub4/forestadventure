/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "EntityType.h"
#include "Id.h"
#include "LayerType.h"
#include "SfmlFwd.h"

namespace FA {

namespace Graphic {

class RenderTargetIf;

}  // namespace Graphic

namespace Entity {

class EntityIf
{
public:
    virtual ~EntityIf() = default;

    virtual EntityType Type() const = 0;
    virtual LayerType GetLayer() const = 0;
    virtual bool IsStatic() const = 0;
    virtual bool IsSolid() const = 0;

    virtual void Destroy() = 0;
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void DrawTo(Graphic::RenderTargetIf& renderTarget) const = 0;
    virtual bool Intersect(const EntityIf& otherEntity) const = 0;
    virtual bool IsOutsideTileMap(const sf::FloatRect& rect) const = 0;
    virtual void HandleCollision(const EntityId id) = 0;
    virtual void HandleOutsideTileMap() = 0;
    virtual EntityId GetId() const = 0;
};

}  // namespace Entity

}  // namespace FA
