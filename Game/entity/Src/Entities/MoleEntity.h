/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

#include "Enum/MoveDirection.h"

namespace FA {

namespace Entity {

class MoleEntity : public BasicEntity
{
public:
    static const std::string str;

    MoleEntity(EntityId id, const PropertyData& data, const EntityService& service);
    virtual ~MoleEntity();

    virtual EntityType Type() const override { return EntityType::Mole; }
    virtual LayerType GetLayer() const override { return LayerType::Ground; }

private:
    virtual void RegisterProperties() override;
    virtual void ReadProperties(const std::unordered_map<std::string, std::string>& properties) override;
    virtual void RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data) override;

    void OnBeginMove(MoveDirection moveDirection);
    void OnUpdateMove(const sf::Vector2f& delta);
};

}  // namespace Entity

}  // namespace FA
