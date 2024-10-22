/*
 *	Copyright (C) 2024 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

namespace FA {

namespace Entity {

class EntranceEntity : public BasicEntity
{
public:
    static const std::string str;

    EntranceEntity(EntityId id, const Shared::EntityData& data, std::unique_ptr<EntityService> service);
    virtual ~EntranceEntity();

    virtual EntityType Type() const override { return EntityType::Entrance; }
    virtual LayerType GetLayer() const override { return LayerType::Ground; }
    virtual bool IsStatic() const override { return true; }
    virtual bool IsSolid() const override { return false; }

private:
    virtual void RegisterProperties() override;
    virtual void ReadProperties(const std::unordered_map<std::string, std::string>& properties) override;
    virtual void RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const Shared::EntityData& data) override;
};

}  // namespace Entity

}  // namespace FA
