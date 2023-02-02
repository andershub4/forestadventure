/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

#include "Enum/FaceDirection.h"
#include "Enum/MoveDirection.h"

namespace FA {

namespace Entity {

class MoleEntity : public BasicEntity
{
public:
    MoleEntity(EntityId id, Level& level, const EntityService& service);
    virtual ~MoleEntity();

    virtual std::string Name() const override { return "MoleEntity"; }
    virtual EntityType Type() const override { return EntityType::Mole; }
    virtual LayerType GetLayer() const override { return LayerType::Ground; }

private:
    virtual void RegisterProperties() override;
    virtual void RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data) override;

    void OnBeginMove(MoveDirection moveDirection);
    void OnUpdateMove(const sf::Vector2f& delta);
    std::string AnimationKey() const;
    std::unordered_map<std::string, Shared::Animation> GetAnimations(
        const std::unordered_map<FaceDirection, Shared::AnimationData>& data) const;
};

}  // namespace Entity

}  // namespace FA
