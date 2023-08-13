/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Constant/Entity.h"
#include "PropertyData.h"
#include "Resource/ImageData.h"
#include "Resource/TextureRect.h"
#include "Sprites/AnimationSprite.h"
#include "State.h"

namespace FA {

namespace Entity {

const std::string TileEntity::str = "Tile";

TileEntity::TileEntity(EntityId id, const PropertyData& data, const Shared::MapData& mapData,
                       const EntityService& service)
    : BasicEntity(id, data, mapData, service)
{}

TileEntity::~TileEntity() = default;

void TileEntity::RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data)
{
    float t = Constant::stdSwitchTime;

    Shared::Animation animation(0, t);
    for (const auto& d : data.graphic_.animation_) {
        auto rect = service_.MakeRect(d);
        const sf::Texture* texture = service_.GetTexture(rect.id_);
        Shared::Frame frame{texture, {rect.position_.x, rect.position_.y, rect.size_.x, rect.size_.y}};
        animation.AddFrame(frame);
    }

    auto sprite = AnimationSprite::Create(animation, false);
    idleState->RegisterSprite(sprite);
    idleState->RegisterIgnoreEvents({EventType::Collision});
}

}  // namespace Entity

}  // namespace FA
