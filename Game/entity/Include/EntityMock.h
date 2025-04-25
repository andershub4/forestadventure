/*
 *	Copyright (C) 2025 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <gmock/gmock.h>

#include "EntityIf.h"
#include "RenderTargetIf.h"

namespace FA {

namespace Entity {

class EntityMock : public EntityIf
{
public:
    MOCK_METHOD((EntityType), Type, (), (const override));
    MOCK_METHOD((LayerType), GetLayer, (), (const override));
    MOCK_METHOD((bool), IsStatic, (), (const override));
    MOCK_METHOD((bool), IsSolid, (), (const override));
    MOCK_METHOD((void), Destroy, (), (override));
    MOCK_METHOD((void), Init, (), (override));
    MOCK_METHOD((void), Update, (float), (override));
    MOCK_METHOD((void), DrawTo, (Graphic::RenderTargetIf&), (const override));
    MOCK_METHOD((bool), Intersect, (const EntityIf&), (const override));
    MOCK_METHOD((bool), IsOutsideTileMap, (const sf::FloatRect&), (const override));
    MOCK_METHOD((void), HandleCollision, (const EntityId), (override));
    MOCK_METHOD((void), HandleOutsideTileMap, (), (override));
    MOCK_METHOD((EntityId), GetId, (), (const override));
};

class EntityMockProxy : public EntityIf
{
public:
    EntityMockProxy(EntityMock& mock)
        : mock_(mock)
    {}

    virtual EntityType Type() const override { return mock_.Type(); }
    virtual LayerType GetLayer() const override { return mock_.GetLayer(); }
    virtual bool IsStatic() const override { return mock_.IsStatic(); }
    virtual bool IsSolid() const override { return mock_.IsSolid(); }

    virtual void Destroy() override { mock_.Destroy(); }
    virtual void Init() override { mock_.Init(); }
    virtual void Update(float deltaTime) override { mock_.Update(deltaTime); }
    virtual void DrawTo(Graphic::RenderTargetIf& renderTarget) const override { mock_.DrawTo(renderTarget); }
    virtual bool Intersect(const EntityIf& otherEntity) const override { return mock_.Intersect(otherEntity); }
    virtual bool IsOutsideTileMap(const sf::FloatRect& rect) const override { return mock_.IsOutsideTileMap(rect); }
    virtual void HandleCollision(const EntityId id) override { mock_.HandleCollision(id); }
    virtual void HandleOutsideTileMap() override { mock_.HandleOutsideTileMap(); }
    virtual EntityId GetId() const override { return mock_.GetId(); }

private:
    EntityMock& mock_;
};

}  // namespace Entity

}  // namespace FA
