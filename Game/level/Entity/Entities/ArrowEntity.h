/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

#include "Enum/MoveDirection.h"

namespace FA {

namespace Entity {

class ArrowEntity : public BasicEntity
{
public:
    static PropertyData CreatePropertyData(const sf::Vector2f& position, MoveDirection dir);

    ArrowEntity(EntityId id, Level& level, const EntityService& service);
    virtual ~ArrowEntity();

    virtual std::string Name() const override { return "ArrowEntity"; }
    virtual EntityType Type() const override { return EntityType::Arrow; }
    virtual LayerType GetLayer() const override { return LayerType::Ground; }

private:
    virtual void RegisterProperties() override;
    virtual void ReadProperties(const std::unordered_map<std::string, std::string>& properties) override;
    virtual void RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data) override;

    virtual void OnBeginIdle() override;
    void OnBeginMove(MoveDirection moveDirection);
    void OnUpdateMove(const sf::Vector2f& delta);
};

}  // namespace Entity

}  // namespace FA
