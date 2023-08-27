/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "TileEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Constant/Entity.h"
#include "PropertyData.h"
#include "Resource/ImageData.h"
#include "Resource/TextureRect.h"
#include "ShapeParts/AnimationPart.h"
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

    Shared::Animation animation(std::make_shared<sf::Sprite>(), 0, t);
    for (const auto& d : data.graphic_.animation_) {
        auto rect = service_.MakeRect(d);
        const sf::Texture* texture = service_.GetTexture(rect.id_);
        Shared::Frame frame{texture, {rect.position_.x, rect.position_.y, rect.size_.x, rect.size_.y}};
        animation.AddFrame(frame);
    }

    auto part = AnimationPart::Create(animation, false);
    idleState->RegisterShapePart(part);
    idleState->RegisterIgnoreEvents({EventType::Collision});
}

}  // namespace Entity

}  // namespace FA
