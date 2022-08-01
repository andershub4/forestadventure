/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "EntityService.h"

#include "Constant/Entity.h"
#include "EntityManager.h"
#include "Level/CameraManager.h"
#include "Resource/Animation.h"
#include "Resource/AnimationData.h"
#include "Resource/Image.h"
#include "Resource/ImageData.h"
#include "Resource/SheetManager.h"
#include "SpawnManager.h"

namespace FA {

namespace Entity {

EntityService::EntityService(const SheetManager& sheetManager)
    : sheetManager_(sheetManager)
{}

EntityService::~EntityService() = default;

Animation EntityService::MakeAnimation(const AnimationData& data) const
{
    float t = constant::Entity::stdSwitchTime;
    auto frames = sheetManager_.MakeFrames(data);
    return Animation(frames, data.locationData_.defaultIndex_, t);
}

Image EntityService::MakeImage(const ImageData& data) const
{
    auto frame = sheetManager_.MakeFrame(data);
    return Image(frame);
}

}  // namespace Entity

}  // namespace FA
