/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "Components/Animation/AnimationComponent.h"
#include "Components/Movement/MovementComponent.h"
#include "Components/Sprite/SpriteComponent.h"
#include "Components/Transform/TransformComponent.h"
#include "Enum/FaceDirection.h"

namespace FA {

namespace Entity {

struct Configuration
{
    FaceDirection faceDir_;
    TransformComponent transform_;
    MovementComponent movement_;
    SpriteComponent sprite_;
};

}  // namespace Entity

}  // namespace FA
