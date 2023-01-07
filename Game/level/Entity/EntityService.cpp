/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityService.h"

#include "Constant/Entity.h"
#include "Resource/Animation.h"
#include "Resource/AnimationData.h"
#include "Resource/Image.h"
#include "Resource/ImageData.h"
#include "Resource/SheetManager.h"

namespace FA {

namespace Entity {

EntityService::EntityService(const Shared::SheetManager& sheetManager)
    : sheetManager_(sheetManager)
{}

EntityService::~EntityService() = default;

Shared::Animation EntityService::MakeAnimation(const Shared::AnimationData& data) const
{
    float t = constant::Entity::stdSwitchTime;
    auto frames = sheetManager_.MakeFrames(data);
    return Shared::Animation(frames, data.locationData_.defaultIndex_, t);
}

Shared::Image EntityService::MakeImage(const Shared::ImageData& data) const
{
    auto frame = sheetManager_.MakeFrame(data);
    return Shared::Image(frame);
}

}  // namespace Entity

}  // namespace FA
